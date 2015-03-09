/*!
 * \file thumbnail.c
 *
 * \author Copyright (C) 2009 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF thumbnail (\c THUMBNAIL).
 *
 * <hr>
 * <h1><b>Copyright Notices.</b></h1>\n
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.\n\n
 * This program is distributed in the hope that it will be useful, but
 * <b>WITHOUT ANY WARRANTY</b>; without even the implied warranty of
 * <b>MERCHANTABILITY</b> or <b>FITNESS FOR A PARTICULAR PURPOSE</b>.\n
 * See the GNU General Public License for more details.\n\n
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to:\n
 * Free Software Foundation, Inc.,\n
 * 59 Temple Place,\n
 * Suite 330,\n
 * Boston,\n
 * MA 02111 USA.\n
 * \n
 * Drawing eXchange Format (DXF) is a defacto industry standard for the
 * exchange of drawing files between various Computer Aided Drafting
 * programs.\n
 * DXF is an industry standard designed by Autodesk(TM).\n
 * For more details see http://www.autodesk.com.
 * <hr>
 */


#include "thumbnail.h"


/*!
 * \brief Allocate memory for a DXF \c THUMBNAILIMAGE.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14 (backward compatibility).
 * \version According to DXF R2000.
 * \version According to DXF R2000i.
 * \version According to DXF R2002.
 * \version According to DXF R2004.
 * \version According to DXF R2005.
 * \version According to DXF R2006.
 * \version According to DXF R2008.
 * \version According to DXF R2009.
 * \version According to DXF R2010.
 * \version According to DXF R2011.
 * \version According to DXF R2012.
 * \version According to DXF R2013.
 * \version According to DXF R2014.
 */
DxfThumbnail *
dxf_thumbnail_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfThumbnail *thumbnail = NULL;
        size_t size;

        size = sizeof (DxfThumbnail);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((thumbnail = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfThumbnail struct.\n")),
                  __FUNCTION__);
                thumbnail = NULL;
        }
        else
        {
                memset (thumbnail, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (thumbnail);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * \c THUMBNAILIMAGE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14 (backward compatibility).
 * \version According to DXF R2000.
 * \version According to DXF R2000i.
 * \version According to DXF R2002.
 * \version According to DXF R2004.
 * \version According to DXF R2005.
 * \version According to DXF R2006.
 * \version According to DXF R2008.
 * \version According to DXF R2009.
 * \version According to DXF R2010.
 * \version According to DXF R2011.
 * \version According to DXF R2012.
 * \version According to DXF R2013.
 * \version According to DXF R2014.
 */
DxfThumbnail *
dxf_thumbnail_init
(
        DxfThumbnail *thumbnail
                /*!< DXF thumbnailimage entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (thumbnail == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                thumbnail = dxf_thumbnail_new ();
        }
        if (thumbnail == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfThumbnail struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        thumbnail->number_of_bytes = 0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                thumbnail->preview_image_data[i] = strdup ("");
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (thumbnail);
}


/*!
 * \brief Read data from a DXF file into a DXF \c THUMBNAILIMAGE entity.
 *
 * The last line read from file contained the string "THUMBNAILIMAGE". \n
 * Now follows some data for the \c THUMBNAILIMAGE, to be terminated
 * with a "  0" string announcing the following entity, or the end of
 * the \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c thumbnail. \n
 *
 * \return a pointer to \c thumbnail.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14 (backward compatibility).
 * \version According to DXF R2000.
 * \version According to DXF R2000i.
 * \version According to DXF R2002.
 * \version According to DXF R2004.
 * \version According to DXF R2005.
 * \version According to DXF R2006.
 * \version According to DXF R2008.
 * \version According to DXF R2009.
 * \version According to DXF R2010.
 * \version According to DXF R2011.
 * \version According to DXF R2012.
 * \version According to DXF R2013.
 * \version According to DXF R2014.
 */
DxfThumbnail *
dxf_thumbnail_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfThumbnail *thumbnail
                /*!< DXF thumbnailimage entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;
        int preview_data_length = 0;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (temp_string);
                return (NULL);
        }
        if (thumbnail == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                thumbnail = dxf_thumbnail_new ();
                thumbnail = dxf_thumbnail_init (thumbnail);
        }
        if (fp->acad_version_number < AutoCAD_2000)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        i = 0;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        fclose (fp->fp);
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the
                         * number of bytes value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &thumbnail->number_of_bytes);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing additional
                         * proprietary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", thumbnail->preview_image_data[i]);
                        preview_data_length = preview_data_length + strlen (thumbnail->preview_image_data[i]);
                        i++;
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (preview_data_length != thumbnail->number_of_bytes)
        {
                        fprintf (stderr,
                          (_("Warning in %s () read %d preview data bytes from %s while %d were expected.\n")),
                          __FUNCTION__, preview_data_length,
                          fp->filename, thumbnail->number_of_bytes);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (thumbnail);
}


/*!
 * \brief Write a thumbnail to a DXF file.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14 (backward compatibility).
 * \version According to DXF R2000.
 * \version According to DXF R2000i.
 * \version According to DXF R2002.
 * \version According to DXF R2004.
 * \version According to DXF R2005.
 * \version According to DXF R2006.
 * \version According to DXF R2008.
 * \version According to DXF R2009.
 * \version According to DXF R2010.
 * \version According to DXF R2011.
 * \version According to DXF R2012.
 * \version According to DXF R2013.
 * \version According to DXF R2014.
 */
int
dxf_thumbnail_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfThumbnail *thumbnail
                /*!< the thumbnail to write to the output file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("THUMBNAILIMAGE");
        int i;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (thumbnail == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (thumbnail->number_of_bytes < 1)
        {
                fprintf (stderr,
                  (_("Error in %s () number of bytes was 0 or less.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_2000)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp->fp, " 90\n%d\n", thumbnail->number_of_bytes);
        i = 0;
        while (strlen (thumbnail->preview_image_data[i]) > 0)
        {
                fprintf (fp->fp, "310\n%s\n", thumbnail->preview_image_data[i]);
                i++;
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c THUMBNAILIMAGE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14 (backward compatibility).
 * \version According to DXF R2000.
 * \version According to DXF R2000i.
 * \version According to DXF R2002.
 * \version According to DXF R2004.
 * \version According to DXF R2005.
 * \version According to DXF R2006.
 * \version According to DXF R2008.
 * \version According to DXF R2009.
 * \version According to DXF R2010.
 * \version According to DXF R2011.
 * \version According to DXF R2012.
 * \version According to DXF R2013.
 * \version According to DXF R2014.
 */
int
dxf_thumbnail_free
(
        DxfThumbnail *thumbnail
                /*!< Pointer to the memory occupied by the DXF
                 * \c THUMBNAILIMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (thumbnail->preview_image_data[i]);
        }
        free (thumbnail);
        thumbnail = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
