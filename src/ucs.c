/*!
 * \file ucs.c
 *
 * \author Copyright (C) 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF User Coordinate System entity (\c UCS).
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


#include "ucs.h"


/*!
 * \brief Allocate memory for a DXF \c UCS.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfUcs *
dxf_ucs_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfUcs *dxf_ucs = NULL;
        size_t size;

        size = sizeof (DxfUcs);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_ucs = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfUcs struct.\n")),
                  __FUNCTION__);
                dxf_ucs = NULL;
        }
        else
        {
                memset (dxf_ucs, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_ucs);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c UCS
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfUcs *
dxf_ucs_init
(
        DxfUcs *dxf_ucs
                /*!< DXF ucs entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_ucs == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_ucs = dxf_ucs_new ();
        }
        if (dxf_ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfUcs struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_ucs->id_code = 0;
        dxf_ucs->UCS_name = strdup ("");
        dxf_ucs->x_origin = 0.0;
        dxf_ucs->y_origin = 0.0;
        dxf_ucs->z_origin = 0.0;
        dxf_ucs->x_X_dir = 0.0;
        dxf_ucs->y_X_dir = 0.0;
        dxf_ucs->z_X_dir = 0.0;
        dxf_ucs->x_Y_dir = 0.0;
        dxf_ucs->y_Y_dir = 0.0;
        dxf_ucs->z_Y_dir = 0.0;
        dxf_ucs->flag = 0;
        dxf_ucs->dictionary_owner_soft = strdup ("");
        dxf_ucs->dictionary_owner_hard = strdup ("");
        dxf_ucs->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_ucs);
}


/*!
 * \brief Read data from a DXF file into a DXF \c UCS entity.
 *
 * The last line read from file contained the string "UCS". \n
 * Now follows some data for the \c UCS, to be terminated with a "  0"
 * string announcing the following table record, or the end of the
 * \c TABLE section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c dxf_ucs. \n
 *
 * \return a pointer to \c dxf_ucs.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfUcs *
dxf_ucs_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfUcs *dxf_ucs
                /*!< DXF UCS entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

        /* Do some basic checks. */
        if (dxf_ucs == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_ucs = dxf_ucs_new ();
                dxf_ucs = dxf_ucs_init (dxf_ucs);
        }
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
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_ucs->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing an UCS
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ucs->UCS_name);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ucs->x_origin);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ucs->y_origin);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ucs->z_origin);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the reference point for the
                         * X-axis direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ucs->x_X_dir);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the reference point for the
                         * X-axis direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ucs->y_X_dir);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the reference point for the
                         * X-axis direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ucs->z_X_dir);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the reference point for the
                         * Y-axis direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ucs->x_Y_dir);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the reference point for the
                         * Y-axis direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ucs->y_Y_dir);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the reference point for the
                         * Y-axis direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ucs->z_Y_dir);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_ucs->flag);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbSymbolTableRecord") != 0)
                        && ((strcmp (temp_string, "AcDbUCSTableRecord") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ucs->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ucs->dictionary_owner_hard);
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_ucs);
}


/*!
 * \brief Write DXF output to a file for a DXF \c UCS entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_ucs_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfUcs *dxf_ucs
                /*!< DXF UCS entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("UCS");

        /* Do some basic checks. */
        if (dxf_ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if ((dxf_ucs->UCS_name == NULL)
          || (strcmp (dxf_ucs->UCS_name, "") == 0))
        {
                fprintf (stderr,
                  (_("Warning: empty UCS name string for the %s entity with id-code: %x\n")),
                  dxf_entity_name, dxf_ucs->id_code);
                fprintf (stderr,
                  (_("\t%s entity is discarded from output.\n")),
                  dxf_entity_name);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_ucs->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_ucs->id_code);
        }
        /*!
         * \todo for version R14.\n
         * Implementing the start of application-defined group
         * "{application_name", with Group code 102.\n
         * For example: "{ACAD_REACTORS" indicates the start of the
         * AutoCAD persistent reactors group.\n\n
         * application-defined codes: Group codes and values within the
         * 102 groups are application defined (optional).\n\n
         * End of group, "}" (optional), with Group code 102.
         */
        if ((strcmp (dxf_ucs->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_ucs->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_ucs->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_ucs->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp->fp, "100\nAcDbUCSTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dxf_ucs->UCS_name);
        fprintf (fp->fp, " 70\n%d\n", dxf_ucs->flag);
        fprintf (fp->fp, " 10\n%f\n", dxf_ucs->x_origin);
        fprintf (fp->fp, " 20\n%f\n", dxf_ucs->y_origin);
        fprintf (fp->fp, " 30\n%f\n", dxf_ucs->z_origin);
        fprintf (fp->fp, " 11\n%f\n", dxf_ucs->x_X_dir);
        fprintf (fp->fp, " 21\n%f\n", dxf_ucs->y_X_dir);
        fprintf (fp->fp, " 31\n%f\n", dxf_ucs->z_X_dir);
        fprintf (fp->fp, " 12\n%f\n", dxf_ucs->x_Y_dir);
        fprintf (fp->fp, " 22\n%f\n", dxf_ucs->y_Y_dir);
        fprintf (fp->fp, " 32\n%f\n", dxf_ucs->z_Y_dir);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c UCS and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_ucs_free
(
        DxfUcs *dxf_ucs
                /*!< Pointer to the memory occupied by the DXF \c UCS
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_ucs->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfUcs was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_ucs->UCS_name);
        free (dxf_ucs->dictionary_owner_soft);
        free (dxf_ucs->dictionary_owner_hard);
        free (dxf_ucs);
        dxf_ucs = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
