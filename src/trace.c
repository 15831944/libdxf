/*!
 * \file trace.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief DXF trace entity (\c TRACE).
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
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#include "trace.h"


/*!
 * \brief Allocate memory for a DXF \c TRACE.
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
DxfTrace *
dxf_trace_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfTrace *trace = NULL;
        size_t size;

        size = sizeof (DxfTrace);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((trace = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfTrace struct.\n")),
                  __FUNCTION__);
                trace = NULL;
        }
        else
        {
                memset (trace, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (trace);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c TRACE
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
DxfTrace *
dxf_trace_init
(
        DxfTrace *trace
                /*!< DXF trace entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (trace == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                trace = dxf_trace_new ();
        }
        if (trace == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfTrace struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        trace->id_code = 0;
        trace->linetype = strdup (DXF_DEFAULT_LINETYPE);
        trace->layer = strdup (DXF_DEFAULT_LAYER);
        trace->x0 = 0.0;
        trace->y0 = 0.0;
        trace->z0 = 0.0;
        trace->x1 = 0.0;
        trace->y1 = 0.0;
        trace->z1 = 0.0;
        trace->x2 = 0.0;
        trace->y2 = 0.0;
        trace->z2 = 0.0;
        trace->x3 = 0.0;
        trace->y3 = 0.0;
        trace->z3 = 0.0;
        trace->elevation = 0.0;
        trace->thickness = 0.0;
        trace->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        trace->visibility = DXF_DEFAULT_VISIBILITY;
        trace->color = DXF_COLOR_BYLAYER;
        trace->paperspace = DXF_MODELSPACE;
        trace->extr_x0 = 0.0;
        trace->extr_y0 = 0.0;
        trace->extr_z0 = 0.0;
        trace->dictionary_owner_soft = strdup ("");
        trace->dictionary_owner_hard = strdup ("");
        trace->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (trace);
}


/*!
 * \brief Read data from a DXF file into a DXF \c TRACE entity.
 *
 * The last line read from file contained the string "TRACE". \n
 * Now follows some data for the \c TRACE, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c trace. \n
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfTrace *
dxf_trace_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfTrace *trace
                /*!< DXF \c TRACE entity. */
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
                return (NULL);
        }
        if (trace == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                trace = dxf_trace_new ();
                trace = dxf_trace_init (trace);
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
                        fscanf (fp->fp, "%x\n", &trace->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", trace->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", trace->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->x0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the alignment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->x1);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the alignment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->x2);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the alignment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->x3);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->y0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the alignment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->y1);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the alignment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->y2);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the alignment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->y3);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->z0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the alignment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->z1);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the alignment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->z2);
                }
                else if (strcmp (temp_string, "33") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the alignment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->z3);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (trace->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &trace->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &trace->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &trace->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbTrace") != 0)))
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
                        fscanf (fp->fp, "%lf\n", &trace->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &trace->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", trace->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", trace->dictionary_owner_hard);
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
        if (strcmp (trace->linetype, "") == 0)
        {
                trace->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (trace->layer, "") == 0)
        {
                trace->layer = strdup (DXF_DEFAULT_LAYER);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (trace);
}


/*!
 * \brief Write DXF output to fp for a DCF \c TRACE entity.
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
dxf_trace_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfTrace *trace
                /*!< DXF trace entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("TRACE");

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (trace == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (trace->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, trace->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                trace->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (trace->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, trace->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                trace->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (trace->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", trace->id_code);
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
        if ((strcmp (trace->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", trace->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (trace->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", trace->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (trace->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", trace->layer);
        if (strcmp (trace->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", trace->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (trace->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", trace->elevation);
        }
        if (trace->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", trace->color);
        }
        if (trace->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", trace->linetype_scale);
        }
        if (trace->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", trace->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbTrace\n");
        }
        fprintf (fp->fp, " 10\n%f\n", trace->x0);
        fprintf (fp->fp, " 20\n%f\n", trace->y0);
        fprintf (fp->fp, " 30\n%f\n", trace->z0);
        fprintf (fp->fp, " 11\n%f\n", trace->x1);
        fprintf (fp->fp, " 21\n%f\n", trace->y1);
        fprintf (fp->fp, " 31\n%f\n", trace->z1);
        fprintf (fp->fp, " 12\n%f\n", trace->x2);
        fprintf (fp->fp, " 22\n%f\n", trace->y2);
        fprintf (fp->fp, " 32\n%f\n", trace->z2);
        fprintf (fp->fp, " 13\n%f\n", trace->x3);
        fprintf (fp->fp, " 23\n%f\n", trace->y3);
        fprintf (fp->fp, " 33\n%f\n", trace->z3);
        if (trace->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", trace->thickness);
        }
        if ((fp->acad_version_number >= AutoCAD_12)
                && (trace->extr_x0 != 0.0)
                && (trace->extr_y0 != 0.0)
                && (trace->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", trace->extr_x0);
                fprintf (fp->fp, "220\n%f\n", trace->extr_y0);
                fprintf (fp->fp, "230\n%f\n", trace->extr_z0);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c TRACE and all it's
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
dxf_trace_free
(
        DxfTrace *trace
                /*!< Pointer to the memory occupied by the DXF \c TRACE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (trace->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfTrace was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (trace->linetype);
        free (trace->layer);
        free (trace->dictionary_owner_soft);
        free (trace->dictionary_owner_hard);
        free (trace);
        trace = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
