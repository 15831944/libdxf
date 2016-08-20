/*!
 * \file ellipse.c
 *
 * \author Copyright (C) 2008 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF ellipse entity (\c ELLIPSE).
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


#include "ellipse.h"


/*!
 * \brief Allocate memory for a DXF \c ELLIPSE.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfEllipse *
dxf_ellipse_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfEllipse *ellipse = NULL;
        size_t size;

        size = sizeof (DxfEllipse);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((ellipse = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfEllipse struct.\n")),
                  __FUNCTION__);
                ellipse = NULL;
        }
        else
        {
                memset (ellipse, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c ELLIPSE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfEllipse *
dxf_ellipse_init
(
        DxfEllipse *ellipse
                /*!< Pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                ellipse = dxf_ellipse_new ();
        }
        if (ellipse == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfEllipse struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        ellipse->id_code = 0;
        ellipse->linetype = strdup (DXF_DEFAULT_LINETYPE);
        ellipse->layer = strdup (DXF_DEFAULT_LAYER);
        ellipse->elevation = 0.0;
        ellipse->thickness = 0.0;
        ellipse->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        ellipse->visibility = DXF_DEFAULT_VISIBILITY;
        ellipse->color = DXF_COLOR_BYLAYER;
        ellipse->paperspace = DXF_MODELSPACE;
        ellipse->dictionary_owner_soft = strdup ("");
        ellipse->dictionary_owner_hard = strdup ("");
        ellipse->x0 = 0.0;
        ellipse->y0 = 0.0;
        ellipse->z0 = 0.0;
        ellipse->x1 = 0.0;
        ellipse->y1 = 0.0;
        ellipse->z1 = 0.0;
        ellipse->extr_x0 = 0.0;
        ellipse->extr_y0 = 0.0;
        ellipse->extr_z0 = 0.0;
        ellipse->ratio = 0.0;
        ellipse->start_angle = 0.0;
        ellipse->end_angle = 0.0;
        ellipse->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Read data from a DXF file into a DXF \c ELLIPSE entity.
 *
 * The last line read from file contained the string "ELLIPSE". \n
 * Now follows some data for the \c ELLIPSE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c ellipse. \n
 *
 * \return a pointer to \c ellipse.
 */
DxfEllipse *
dxf_ellipse_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfEllipse *ellipse
                /*!< Pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

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
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                ellipse = dxf_ellipse_new ();
                ellipse = dxf_ellipse_init (ellipse);
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
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &ellipse->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", ellipse->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", ellipse->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->z1);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (ellipse->elevation = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * radius. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->ratio);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * start angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->start_angle);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * end angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->end_angle);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &ellipse->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &ellipse->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &ellipse->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_12)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Subclass markers are post AutoCAD R12
                         * variable so additional testing for the
                         * version should probably be added here.
                         * Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbEllipse") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", ellipse->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", ellipse->dictionary_owner_hard);
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
        if (strcmp (ellipse->linetype, "") == 0)
        {
                ellipse->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (ellipse->layer, "") == 0)
        {
                ellipse->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Write DXF output to a file for a DXF \c ELLIPSE entity.
 *
 * The ellipse entity (elliptic arc) requires AutoCAD version R14 or
 * higher.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ellipse_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfEllipse *ellipse
                /*!< Pointer to a DXF \c ELLIPSE entity */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("ELLIPSE");

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
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Error in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (ellipse->ratio == 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () ratio value equals 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, ellipse->id_code);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (ellipse->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, ellipse->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                ellipse->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (ellipse->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, ellipse->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                ellipse->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (ellipse->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", ellipse->id_code);
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
        if ((strcmp (ellipse->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", ellipse->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (ellipse->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", ellipse->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (ellipse->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", ellipse->layer);
        if (strcmp (ellipse->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", ellipse->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (ellipse->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", ellipse->elevation);
        }
        if ((fp->acad_version_number <= AutoCAD_13)
          && (ellipse->thickness != 0.0))
        {
                fprintf (fp->fp, " 39\n%f\n", ellipse->thickness);
        }
        if (ellipse->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", ellipse->color);
        }
        if (ellipse->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", ellipse->linetype_scale);
        }
        if (ellipse->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", ellipse->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEllipse\n");
        }
        fprintf (fp->fp, " 10\n%f\n", ellipse->x0);
        fprintf (fp->fp, " 20\n%f\n", ellipse->y0);
        fprintf (fp->fp, " 30\n%f\n", ellipse->z0);
        fprintf (fp->fp, " 11\n%f\n", ellipse->x1);
        fprintf (fp->fp, " 21\n%f\n", ellipse->y1);
        fprintf (fp->fp, " 31\n%f\n", ellipse->z1);
        fprintf (fp->fp, " 210\n%f\n", ellipse->extr_x0);
        fprintf (fp->fp, " 220\n%f\n", ellipse->extr_y0);
        fprintf (fp->fp, " 230\n%f\n", ellipse->extr_z0);
        fprintf (fp->fp, " 40\n%f\n", ellipse->ratio);
        fprintf (fp->fp, " 41\n%f\n", ellipse->start_angle);
        fprintf (fp->fp, " 42\n%f\n", ellipse->end_angle);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c ELLIPSE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ellipse_free
(
        DxfEllipse *ellipse
                /*!< Pointer to the memory occupied by the DXF
                 * \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (ellipse->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfEllipse was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (ellipse->linetype);
        free (ellipse->layer);
        free (ellipse->dictionary_owner_soft);
        free (ellipse->dictionary_owner_hard);
        free (ellipse);
        ellipse = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c ELLIPSE
 * entities and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
void
dxf_ellipse_free_chain
(
        DxfEllipse *ellipses
                /*!< pointer to the chain of DXF \c ELLIPSE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (ellipses == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (ellipses != NULL)
        {
                struct DxfEllipse *iter = ellipses->next;
                dxf_ellipse_free (ellipses);
                ellipses = (DxfEllipse *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c ELLIPSE entity.
 *
 * \return ID code.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_ellipse_get_id_code
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = ellipse->id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the ID code for a DXF \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_id_code
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        int id_code
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative id-code value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the linetype from a DXF \c ELLIPSE entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_ellipse_get_linetype
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (ellipse->linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the linetype for a DXF \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_linetype
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the layer from a DXF \c ELLIPSE entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_ellipse_get_layer
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (ellipse->layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the layer for a DXF \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_layer
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the elevation from a DXF \c ELLIPSE entity.
 *
 * \return elevation.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_ellipse_get_elevation
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = ellipse->elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the elevation for a DXF \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_elevation
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the thickness from a DXF \c ELLIPSE entity.
 *
 * \return thickness.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_ellipse_get_thickness
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the thickness member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = ellipse->thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the thickness for a DXF \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_thickness
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative thickness value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the linetype scale from a DXF \c ELLIPSE entity.
 *
 * \return linetype scale.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_ellipse_get_linetype_scale
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the linetype scale member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = ellipse->linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the linetype scale for a DXF \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_linetype_scale
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative linetype scale value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the visibility from a DXF \c ELLIPSE entity.
 *
 * \return visibility.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int16_t
dxf_ellipse_get_visibility
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int16_t result;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = ellipse->visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the visibility for a DXF \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_visibility
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the color from a DXF \c ELLIPSE entity.
 *
 * \return color.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_ellipse_get_color
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the color member.\n")),
                  __FUNCTION__);
        }
        result = ellipse->color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the color for a DXF \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_color
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative color value was passed.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("\teffectively turning this entity it's visibility off.\n")));
        }
        ellipse->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c ELLIPSE entity.
 *
 * \return paperspace flag value.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_ellipse_get_paperspace
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        if (ellipse->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        result = ellipse->paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the paperspace flag for a DXF \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_paperspace
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        int paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c ELLIPSE
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_ellipse_get_graphics_data_size
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
        if (ellipse->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c ELLIPSE
 * entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_graphics_data_size
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative graphics_data_size value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero graphics_data_size value was passed.\n")),
                  __FUNCTION__);
        }
        ellipse->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c ELLIPSE entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_ellipse_get_dictionary_owner_soft
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (ellipse->dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_dictionary_owner_soft
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c ELLIPSE entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_ellipse_get_dictionary_owner_hard
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_hard member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (ellipse->dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_dictionary_owner_hard
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_hard == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the center point of a DXF \c ELLIPSE entity.
 *
 * \return the center point.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPoint *
dxf_ellipse_get_center_point
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c ELLIPSE.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        p1 = dxf_point_init (p1);
        if (p1 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () passed id_code is smaller than 0.\n")),
                __FUNCTION__);
        }
        p1->id_code = id_code;
        p1->x0 = ellipse->x0;
        p1->y0 = ellipse->y0;
        p1->z0 = ellipse->z0;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (ellipse->linetype != NULL)
                        {
                                p1->linetype = strdup (ellipse->linetype);
                        }
                        if (ellipse->layer != NULL)
                        {
                                p1->layer = strdup (ellipse->layer);
                        }
                        p1->thickness = ellipse->thickness;
                        p1->linetype_scale = ellipse->linetype_scale;
                        p1->visibility = ellipse->visibility;
                        p1->color = ellipse->color;
                        p1->paperspace = ellipse->paperspace;
                        if (ellipse->dictionary_owner_soft != NULL)
                        {
                                p1->dictionary_owner_soft = strdup (ellipse->dictionary_owner_soft);
                        }
                        if (ellipse->dictionary_owner_hard != NULL)
                        {
                                p1->dictionary_owner_hard = strdup (ellipse->dictionary_owner_hard);
                        }
                        break;
                default:
                        fprintf (stderr,
                          (_("Warning in %s (): unknown inheritance option passed.\n")),
                          __FUNCTION__);
                        fprintf (stderr,
                          (_("\tResolving to default.\n")));
                        break;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (p1);
}


/*!
 * \brief Set the center point of a DXF \c ELLIPSE entity.
 *
 * \return a pointer to a DXF \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_center_point
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->x0 = point->x0;
        ellipse->y0 = point->y0;
        ellipse->z0 = point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the endpoint of the major axis (relative to the center) of
 * a DXF \c ELLIPSE entity.
 *
 * \return the end point.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPoint *
dxf_ellipse_get_end_point
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c ELLIPSE.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        p1 = dxf_point_init (p1);
        if (p1 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () passed id_code is smaller than 0.\n")),
                __FUNCTION__);
        }
        p1->id_code = id_code;
        p1->x0 = ellipse->x1;
        p1->y0 = ellipse->y1;
        p1->z0 = ellipse->z1;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (ellipse->linetype != NULL)
                        {
                                p1->linetype = strdup (ellipse->linetype);
                        }
                        if (ellipse->layer != NULL)
                        {
                                p1->layer = strdup (ellipse->layer);
                        }
                        p1->thickness = ellipse->thickness;
                        p1->linetype_scale = ellipse->linetype_scale;
                        p1->visibility = ellipse->visibility;
                        p1->color = ellipse->color;
                        p1->paperspace = ellipse->paperspace;
                        if (ellipse->dictionary_owner_soft != NULL)
                        {
                                p1->dictionary_owner_soft = strdup (ellipse->dictionary_owner_soft);
                        }
                        if (ellipse->dictionary_owner_hard != NULL)
                        {
                                p1->dictionary_owner_hard = strdup (ellipse->dictionary_owner_hard);
                        }
                        break;
                default:
                        fprintf (stderr,
                          (_("Warning in %s (): unknown inheritance option passed.\n")),
                          __FUNCTION__);
                        fprintf (stderr,
                          (_("\tResolving to default.\n")));
                        break;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (p1);
}


/*!
 * \brief Set the endpoint of the major axis (relative to the center) of
 * a DXF \c ELLIPSE entity.
 *
 * \return a pointer to a DXF \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_end_point
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->x1 = point->x0;
        ellipse->y1 = point->y0;
        ellipse->z1 = point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the ratio of minor axis to major axis from a DXF
 * \c ELLIPSE entity.
 *
 * \return ratio.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_ellipse_get_ratio
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->ratio < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the ratio member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->ratio == 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a value of zero was found in the ratio member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = ellipse->ratio;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the ratio of minor axis to major axis for a DXF \c ELLIPSE
 * entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_radius
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double ratio
                /*!< the ratio to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ratio < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative ratio value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ratio == 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->ratio = ratio;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the start angle from a DXF \c ELLIPSE entity.
 *
 * \return start angle.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_ellipse_get_start_angle
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = ellipse->start_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the start angle for a DXF \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_start_angle
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double start_angle
                /*!< the start angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->start_angle = start_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the end angle from a DXF \c ELLIPSE entity.
 *
 * \return end angle.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_ellipse_get_end_angle
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = ellipse->end_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the end angle for a DXF \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_end_angle
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double end_angle
                /*!< the end angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->end_angle = end_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c ELLIPSE entity.
 *
 * \return a DXF \c POINT containing the extrusion coordinates.
 *
 * \warning No other members are copied into the DXF \c POINT.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPoint *
dxf_ellipse_get_extrusion_vector_as_point
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point = dxf_point_init (point);
        if (point == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        point->x0 = ellipse->extr_x0;
        point->y0 = ellipse->extr_y0;
        point->z0 = ellipse->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Set the extrusion vector for a DXF \c ELLIPSE entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_extrusion_vector
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double extr_x0,
                /*!<  X-value of the extrusion direction. */
        double extr_y0,
                /*!<  Y-value of the extrusion direction. */
        double extr_z0
                /*!<  Z-value of the extrusion direction. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->extr_x0 = extr_x0;
        ellipse->extr_y0 = extr_y0;
        ellipse->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the pointer to the next \c ELLIPSE entity from a DXF 
 * \c ELLIPSE entity.
 *
 * \return pointer to the next \c ELLIPSE entity.
 *
 * \warning No checks are performed on the returned pointer.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_get_next
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfEllipse *result;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfEllipse *) ellipse->next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the next \c ELLIPSE for a DXF \c ELLIPSE
 * entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEllipse *
dxf_ellipse_set_next
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        DxfEllipse *next
                /*!< a pointer to the next \c ELLIPSE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->next = (struct DxfEllipse *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/* EOF */
