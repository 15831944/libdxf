/*!
 * \file circle.c
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF circle entity (\c CIRCLE).
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


#include "circle.h"


/*!
 * \brief Allocate memory for a DXF \c CIRCLE.
 *
 * Fill the memory contents with zeros.
 */
DxfCircle *
dxf_circle_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfCircle *dxf_circle = NULL;
        size_t size;

        size = sizeof (DxfCircle);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_circle = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () could not allocate memory for a DxfCircle struct.\n")),
                  __FUNCTION__);
                dxf_circle = NULL;
        }
        else
        {
                memset (dxf_circle, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_circle);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c CIRCLE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfCircle *
dxf_circle_init
(
        DxfCircle *dxf_circle
                /*!< DXF circle entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        dxf_circle = dxf_circle_new ();
        if (dxf_circle == NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () could not allocate memory for a DxfCircle struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_circle->id_code = 0;
        dxf_circle->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_circle->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_circle->x0 = 0.0;
        dxf_circle->y0 = 0.0;
        dxf_circle->z0 = 0.0;
        dxf_circle->extr_x0 = 0.0;
        dxf_circle->extr_y0 = 0.0;
        dxf_circle->extr_z0 = 0.0;
        dxf_circle->thickness = 0.0;
        dxf_circle->radius = 0.0;
        dxf_circle->color = DXF_COLOR_BYLAYER;
        dxf_circle->paperspace = DXF_MODELSPACE;
        dxf_circle->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_circle);
}


/*!
 * \brief Read data from a DXF file into a DXF \c CIRCLE entity.
 *
 * The last line read from file contained the string "CIRCLE". \n
 * Now follows some data for the \c CIRCLE, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_circle. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_circle_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfCircle *dxf_circle
                /*!< DXF circle entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

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
                        return (0);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_circle->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_circle->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_circle->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_circle->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_circle->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_circle->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_circle->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_circle->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_circle->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * radius. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_circle->radius);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_circle->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_circle->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && (strcmp (temp_string, "AcDbCircle") != 0))
                        {
                                fprintf (stderr,
                                  (_("Error in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_circle->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_circle->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_circle->extr_z0);
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
                          (_("Warning: in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to file for a DXF \c CIRCLE entity.
 */
int
dxf_circle_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfCircle *dxf_circle
                /*!< DXF circle entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("CIRCLE");

        if (dxf_circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_circle->radius == 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () radius value equals 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_circle->id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_circle->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_circle->id_code);
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0")),
                  dxf_entity_name );
                dxf_circle->layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_circle->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_circle->id_code);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
                fprintf (fp->fp, "100\nAcDbCircle\n");
        }
        if (strcmp (dxf_circle->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_circle->linetype);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_circle->layer);
        fprintf (fp->fp, " 10\n%f\n", dxf_circle->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_circle->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_circle->z0);
        if (dxf_circle->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_circle->thickness);
        }
        fprintf (fp->fp, " 40\n%f\n", dxf_circle->radius);
        if (dxf_circle->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_circle->color);
        }
        if (dxf_circle->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c CIRCLE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_circle_free
(
        DxfCircle *dxf_circle
                /*!< Pointer to the memory occupied by the DXF \c CIRCLE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_circle->next != NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () pointer to next DxfCircle was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_circle->linetype);
        free (dxf_circle->layer);
        free (dxf_circle);
        dxf_circle = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
