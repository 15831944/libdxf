/*!
 * \file vport.c
 *
 * \author Copyright (C) 2015, 2017, 2018 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF Viewport symbol table entry (\c VPORT).
 *
 * The VPORT table is unique: it may contain several entries with the
 * same name (indicating a multiple-viewport configuration).\n
 * The entries corresponding to the active viewport configuration all
 * have the name *ACTIVE.\n
 * The first such entry describes the current viewport.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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


#include "vport.h"


/*!
 * \brief Allocate memory for a DXF \c VPORT entity.
 *
 * Fill the memory contents with zeros.
 */
DxfVPort *
dxf_vport_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfVPort *vport = NULL;
        size_t size;

        size = sizeof (DxfVPort);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((vport = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfVPort struct.\n")),
                  __FUNCTION__);
                vport = NULL;
        }
        else
        {
                memset (vport, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c VPORT
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfVPort *
dxf_vport_init
(
        DxfVPort *vport
                /*!< a pointer to the DXF \c VPORT symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                vport = dxf_vport_new ();
        }
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfVPort struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->id_code = 0;
        vport->viewport_name = strdup ("");
        vport->min = dxf_point_new ();
        vport->min = dxf_point_init (vport->min);
        vport->min->x0 = 0.0;
        vport->min->y0 = 0.0;
        vport->max = dxf_point_new ();
        vport->max = dxf_point_init (vport->max);
        vport->max->x0 = 0.0;
        vport->max->y0 = 0.0;
        vport->center = dxf_point_new ();
        vport->center = dxf_point_init (vport->center);
        vport->center->x0 = 0.0;
        vport->center->y0 = 0.0;
        vport->snap_base = dxf_point_new ();
        vport->snap_base = dxf_point_init (vport->snap_base);
        vport->snap_base->x0 = 0.0;
        vport->snap_base->y0 = 0.0;
        vport->snap_spacing = dxf_point_new ();
        vport->snap_spacing = dxf_point_init (vport->snap_spacing);
        vport->snap_spacing->x0 = 0.0;
        vport->snap_spacing->y0 = 0.0;
        vport->grid_spacing = dxf_point_new ();
        vport->grid_spacing = dxf_point_init (vport->grid_spacing);
        vport->grid_spacing->x0 = 0.0;
        vport->grid_spacing->y0 = 0.0;
        vport->direction = dxf_point_new ();
        vport->direction = dxf_point_init (vport->direction);
        vport->direction->x0 = 0.0;
        vport->direction->y0 = 0.0;
        vport->direction->z0 = 0.0;
        vport->target = dxf_point_new ();
        vport->target = dxf_point_init (vport->target);
        vport->target->x0 = 0.0;
        vport->target->y0 = 0.0;
        vport->target->z0 = 0.0;
        vport->view_height = 0.0;
        vport->viewport_aspect_ratio = 0.0;
        vport->lens_length = 0.0;
        vport->front_plane_offset = 0.0;
        vport->back_plane_offset = 0.0;
        vport->snap_rotation_angle = 0.0;
        vport->view_twist_angle = 0.0;
        vport->status_field = 0;
        vport->id = 0;
        vport->standard_flag = 0;
        vport->view_mode = 0;
        vport->circle_zoom_percent = 0;
        vport->fast_zoom_setting = 0;
        vport->UCSICON_setting = 0;
        vport->snap_on = 0;
        vport->grid_on = 0;
        vport->snap_style = 0;
        vport->snap_isopair = 0;
        vport->dictionary_owner_soft = strdup ("");
        vport->dictionary_owner_hard = strdup ("");
        vport->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Read data from a DXF file into an \c VPORT symbol table entry.
 *
 * The last line read from file contained the string "VPORT". \n
 * Now follows some data for the \c VPORT, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c TABLE section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c vport. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
DxfVPort *
dxf_vport_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfVPort *vport
                /*!< a pointer to the DXF \c VPORT symbol table entry. */
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
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                vport = dxf_vport_new ();
                vport = dxf_vport_init (vport);
        }
        if (vport->min == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                vport->min = dxf_point_new ();
                vport->min = dxf_point_init (vport->min);
        }
        if (vport->max == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                vport->max = dxf_point_new ();
                vport->max = dxf_point_init (vport->max);
        }
        if (vport->center == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                vport->center = dxf_point_new ();
                vport->center = dxf_point_init (vport->center);
        }
        if (vport->snap_base == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                vport->snap_base = dxf_point_new ();
                vport->snap_base = dxf_point_init (vport->snap_base);
        }
        if (vport->snap_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                vport->snap_spacing = dxf_point_new ();
                vport->snap_spacing = dxf_point_init (vport->snap_spacing);
        }
        if (vport->grid_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                vport->grid_spacing = dxf_point_new ();
                vport->grid_spacing = dxf_point_init (vport->grid_spacing);
        }
        if (vport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                vport->direction = dxf_point_new ();
                vport->direction = dxf_point_init (vport->direction);
        }
        if (vport->target == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                vport->target = dxf_point_new ();
                vport->target = dxf_point_init (vport->target);
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
                        fscanf (fp->fp, "%x\n", &vport->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a viewport
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", vport->viewport_name);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the lower-left corner of viewport. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->min->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the lower-left corner of viewport. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->min->y0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the upper-right corner of viewport. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->max->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the upper-right corner of viewport. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->max->y0);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the view center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->center->x0);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the view center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->center->y0);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the snap base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->snap_base->x0);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the snap base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->snap_base->y0);
                }
                else if (strcmp (temp_string, "14") == 0)
                {
                        /* Now follows a string containing the
                         * X value of snap spacing X and Y. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->snap_spacing->x0);
                }
                else if (strcmp (temp_string, "24") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of snap spacing X and Y. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->snap_spacing->y0);
                }
                else if (strcmp (temp_string, "15") == 0)
                {
                        /* Now follows a string containing the
                         * X value of grid spacing X and Y. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->grid_spacing->x0);
                }
                else if (strcmp (temp_string, "25") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of grid spacing X and Y. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->grid_spacing->y0);
                }
                else if (strcmp (temp_string, "16") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the view direction from target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->direction->x0);
                }
                else if (strcmp (temp_string, "26") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the view direction from target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->direction->y0);
                }
                else if (strcmp (temp_string, "36") == 0)
                {
                        /* Now follows a string containing the
                         * Z value of the view direction from target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->direction->z0);
                }
                else if (strcmp (temp_string, "17") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the view target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->target->x0);
                }
                else if (strcmp (temp_string, "27") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the view target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->target->y0);
                }
                else if (strcmp (temp_string, "37") == 0)
                {
                        /* Now follows a string containing the
                         * Z value of the view target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->target->z0);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the view
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->view_height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the viewport
                         * aspect ratio. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->viewport_aspect_ratio);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the lens
                         * length. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->viewport_aspect_ratio);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the front
                         * clipping plane - offset from target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->front_plane_offset);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing the back
                         * clipping plane - offset from target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->back_plane_offset);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the snap
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->snap_rotation_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the view
                         * twist angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vport->view_twist_angle);
                }
                else if (strcmp (temp_string, "68") == 0)
                {
                        /* Now follows a string containing the
                         * status field value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vport->status_field);
                }
                else if (strcmp (temp_string, "69") == 0)
                {
                        /* Now follows a string containing the
                         * ID value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vport->id);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vport->standard_flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * view mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vport->view_mode);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the circle
                         * zoom percent value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vport->circle_zoom_percent);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the fast
                         * zoom setting value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vport->fast_zoom_setting);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the UCSICON
                         * setting value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vport->UCSICON_setting);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing the snap
                         * on/off value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vport->snap_on);
                }
                else if (strcmp (temp_string, "76") == 0)
                {
                        /* Now follows a string containing the grid
                         * on/off value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vport->grid_on);
                }
                else if (strcmp (temp_string, "77") == 0)
                {
                        /* Now follows a string containing the snap
                         * style value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vport->snap_style);
                }
                else if (strcmp (temp_string, "78") == 0)
                {
                        /* Now follows a string containing the snap
                         * isopair value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vport->snap_isopair);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", vport->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", vport->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }

        }
        /* Handle omitted members and/or illegal values. */
        if ((strcmp (vport->viewport_name, "") == 0)
          || (vport->viewport_name == NULL))
        {
                fprintf (stderr,
                  (_("Error in %s () empty string in viewport name found while reading from: %s in line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
                return (NULL);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Write DXF output to a file for a DXF \c VPORT symbol table
 * entry.
 */
int
dxf_vport_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfVPort *vport
                /*!< a pointer to the DXF \c VPORT symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("VPORT");

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
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((vport->viewport_name == NULL)
          || (strcmp (vport->viewport_name, "") == 0))
        {
                fprintf (stderr,
                  (_("Error: empty viewport name string for the %s entity with id-code: %x\n")),
                  dxf_entity_name, vport->id_code);
                fprintf (stderr,
                  (_("\t%s entity is discarded from output.\n")),
                  dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (vport->min == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (vport->max == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (vport->center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (vport->snap_base == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (vport->snap_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (vport->grid_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (vport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (vport->target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (vport->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", vport->id_code);
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
        if ((strcmp (vport->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", vport->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (vport->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", vport->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp->fp, "100\nAcDbViewportTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", vport->viewport_name);
        fprintf (fp->fp, " 70\n%d\n", vport->standard_flag);
        fprintf (fp->fp, " 10\n%f\n", vport->min->x0);
        fprintf (fp->fp, " 20\n%f\n", vport->min->y0);
        fprintf (fp->fp, " 11\n%f\n", vport->max->x0);
        fprintf (fp->fp, " 21\n%f\n", vport->max->y0);
        fprintf (fp->fp, " 12\n%f\n", vport->center->y0);
        fprintf (fp->fp, " 22\n%f\n", vport->center->y0);
        fprintf (fp->fp, " 13\n%f\n", vport->snap_base->x0);
        fprintf (fp->fp, " 23\n%f\n", vport->snap_base->y0);
        fprintf (fp->fp, " 14\n%f\n", vport->snap_spacing->x0);
        fprintf (fp->fp, " 24\n%f\n", vport->snap_spacing->y0);
        fprintf (fp->fp, " 15\n%f\n", vport->grid_spacing->x0);
        fprintf (fp->fp, " 25\n%f\n", vport->grid_spacing->y0);
        fprintf (fp->fp, " 16\n%f\n", vport->direction->x0);
        fprintf (fp->fp, " 26\n%f\n", vport->direction->y0);
        fprintf (fp->fp, " 36\n%f\n", vport->direction->z0);
        fprintf (fp->fp, " 17\n%f\n", vport->target->x0);
        fprintf (fp->fp, " 27\n%f\n", vport->target->y0);
        fprintf (fp->fp, " 37\n%f\n", vport->target->z0);
        fprintf (fp->fp, " 40\n%f\n", vport->view_height);
        fprintf (fp->fp, " 41\n%f\n", vport->viewport_aspect_ratio);
        fprintf (fp->fp, " 42\n%f\n", vport->lens_length);
        fprintf (fp->fp, " 43\n%f\n", vport->front_plane_offset);
        fprintf (fp->fp, " 44\n%f\n", vport->back_plane_offset);
        fprintf (fp->fp, " 50\n%f\n", vport->snap_rotation_angle);
        fprintf (fp->fp, " 51\n%f\n", vport->view_twist_angle);
//        fprintf (fp->fp, " 68\n%d\n", vport->status_field);
//        fprintf (fp->fp, " 69\n%d\n", vport->id);
        fprintf (fp->fp, " 71\n%d\n", vport->view_mode);
        fprintf (fp->fp, " 72\n%d\n", vport->circle_zoom_percent);
        fprintf (fp->fp, " 73\n%d\n", vport->fast_zoom_setting);
        fprintf (fp->fp, " 74\n%d\n", vport->UCSICON_setting);
        fprintf (fp->fp, " 75\n%d\n", vport->snap_on);
        fprintf (fp->fp, " 76\n%d\n", vport->grid_on);
        fprintf (fp->fp, " 77\n%d\n", vport->snap_style);
        fprintf (fp->fp, " 78\n%d\n", vport->snap_isopair);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c VPORT and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_vport_free
(
        DxfVPort *vport
                /*!< a pointer to the memory occupied by the DXF \c VPORT
                 * symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (vport->viewport_name);
        dxf_point_free (vport->min);
        dxf_point_free (vport->max);
        dxf_point_free (vport->center);
        dxf_point_free (vport->snap_base);
        dxf_point_free (vport->snap_spacing);
        dxf_point_free (vport->grid_spacing);
        dxf_point_free (vport->direction);
        dxf_point_free (vport->target);
        free (vport->dictionary_owner_soft);
        free (vport->dictionary_owner_hard);
        free (vport);
        vport = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c VPORT
 * symbol table and all their data fields.
 */
void
dxf_vport_free_chain
(
        DxfVPort *vports
                /*!< a pointer to the chain of DXF \c VPORT symbol table
                 * entries. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (vports == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (vports != NULL)
        {
                struct DxfVPort *iter = vports->next;
                dxf_vport_free (vports);
                vports = (DxfVPort *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c VPORT symbol table entry.
 *
 * \return \c id_code.
 */
int
dxf_vport_get_id_code
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c VPORT symbol table entry.
 */
DxfVPort *
dxf_vport_set_id_code
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        int id_code
                /*!< the \c id_code to be set for the entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        vport->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the \c viewport_name from a DXF \c VPORT symbol table
 * entry.
 *
 * \return \c viewport_name when sucessful, \c NULL when an error
 * occurred.
 */
char *
dxf_vport_get_viewport_name
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->viewport_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (vport->viewport_name));
}


/*!
 * \brief Set the \c viewport_name for a DXF \c VPORT symbol table entry.
 */
DxfVPort *
dxf_vport_set_viewport_name
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        char *viewport_name
                /*!< a pointer to a string containing the
                 * \c viewport_name to be set for the entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->viewport_name = strdup (viewport_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the lower-left corner of viewport \c min of a DXF \c VPORT
 * symbol table entry.
 *
 * \return the lower-left corner of viewport \c min.
 */
DxfPoint *
dxf_vport_get_min
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->min == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->min);
}


/*!
 * \brief Set the lower-left corner \c min of a DXF \c VPORT symbol
 * table entry.
 *
 * \return a pointer to a DXF \c VPORT symbol table entry.
 */
DxfVPort *
dxf_vport_set_min
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        DxfPoint *min
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (min == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->min = min;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the X-value of the lower-left corner \c min_x of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the X-value of the lower-left corner \c min_x.
 */
double
dxf_vport_get_min_x
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->min == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->min->x0);
}


/*!
 * \brief Set the X-value of the lower-left corner \c min_x of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_min_x
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double min_x
                /*!< the X-value of the lower-left corner \c min_x of a
                 * DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->min == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->min->x0 = min_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the Y-value of the lower-left corner \c min_y of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the Y-value of the lower-left corner \c min_y.
 */
double
dxf_vport_get_min_y
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->min == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->min->y0);
}


/*!
 * \brief Set the Y-value of the lower-left corner \c min_y of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_min_y
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double min_y
                /*!< the Y-value of the lower-left corner \c min_y of a
                 * DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->min == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->min->y0 = min_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the upper-right corner of viewport \c max of a DXF \c VPORT
 * symbol table entry.
 *
 * \return the upper-right corner of viewport \c max.
 */
DxfPoint *
dxf_vport_get_max
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->max == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->max);
}


/*!
 * \brief Set the upper-right corner \c max of a DXF \c VPORT symbol
 * table entry.
 *
 * \return a pointer to a DXF \c VPORT symbol table entry.
 */
DxfVPort *
dxf_vport_set_max
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        DxfPoint *max
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (max == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->max = max;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the X-value of the upper-right corner \c max_x of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the X-value of the upper-right corner \c max_x.
 */
double
dxf_vport_get_max_x
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->max == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->max->x0);
}


/*!
 * \brief Set the X-value of the upper-right corner \c max_x of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_max_x
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double max_x
                /*!< the X-value of the upper-right corner \c max_x of a
                 * DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->max == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->max->x0 = max_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the Y-value of the upper-right corner \c max_y of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the Y-value of the upper-right corner \c max_y.
 */
double
dxf_vport_get_max_y
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->max == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->max->y0);
}


/*!
 * \brief Set the Y-value of the upper-right corner \c max_y of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_max_y
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double max_y
                /*!< the Y-value of the upper-right corner \c max_y of a
                 * DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->max == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->max->y0 = max_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the view center point, in World Coordinate System
 * \c center of a DXF \c VPORT symbol table entry.
 *
 * \return the view center point, in World Coordinate System \c center.
 */
DxfPoint *
dxf_vport_get_center
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->center);
}


/*!
 * \brief Set the view center point, in World Coordinate System
 * \c center of a DXF \c VPORT symbol table entry.
 *
 * \return a pointer to a DXF \c VPORT symbol table entry.
 */
DxfVPort *
dxf_vport_set_center
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        DxfPoint *center
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->center = center;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the X-value of the view center point, in World Coordinate
 * System \c center_x of a DXF \c VPORT symbol table entry.
 *
 * \return the X-value of the view center point, in World Coordinate
 * System \c center_x.
 */
double
dxf_vport_get_center_x
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->center->x0);
}


/*!
 * \brief Set the X-value of the view center point, in World Coordinate
 * System \c center_x of a DXF \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_center_x
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double center_x
                /*!< the X-value of the view center point, in World
                 * Coordinate System \c center_x of a DXF \c VPORT
                 * symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->center->x0 = center_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the Y-value of the view center point, in World Coordinate
 * System \c center_y of a DXF \c VPORT symbol table entry.
 *
 * \return the Y-value of the view center point, in World Coordinate
 * System \c center_y.
 */
double
dxf_vport_get_center_y
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->center->y0);
}


/*!
 * \brief Set the Y-value of the view center point, in World Coordinate
 * System \c center_y of a DXF \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_center_y
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double center_y
                /*!< the Y-value of the view center point, in World
                 * Coordinate System \c center_y of a DXF \c VPORT
                 * symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->center->y0 = center_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the snap base point of viewport \c snap_base of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the snap base point of viewport \c snap_base.
 */
DxfPoint *
dxf_vport_get_snap_base
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->snap_base == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->snap_base);
}


/*!
 * \brief Set the snap base point \c snap_base of a DXF \c VPORT symbol
 * table entry.
 *
 * \return a pointer to a DXF \c VPORT symbol table entry.
 */
DxfVPort *
dxf_vport_set_snap_base
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        DxfPoint *snap_base
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (snap_base == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->snap_base = snap_base;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the X-value of the snap base point \c snap_base_x of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the X-value of the snap base point \c snap_base_x.
 */
double
dxf_vport_get_snap_base_x
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->snap_base == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->snap_base->x0);
}


/*!
 * \brief Set the X-value of the snap base point \c snap_base_x of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_snap_base_x
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double snap_base_x
                /*!< the X-value of the snap base point \c snap_base_x
                 * of a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->snap_base == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->snap_base->x0 = snap_base_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the Y-value of the snap base point \c snap_base_y of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the Y-value of the snap base point \c snap_base_y.
 */
double
dxf_vport_get_snap_base_y
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->snap_base == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->snap_base->y0);
}


/*!
 * \brief Set the Y-value of the snap base point \c snap_base_y of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_snap_base_y
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double snap_base_y
                /*!< the Y-value of the snap base point \c snap_base_y
                 * of a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->snap_base == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->snap_base->y0 = snap_base_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the snap spacing of viewport \c snap_spacing of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the snap spacing of viewport \c snap_spacing.
 */
DxfPoint *
dxf_vport_get_snap_spacing
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->snap_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->snap_spacing);
}


/*!
 * \brief Set the snap spacing \c snap_spacing of a DXF \c VPORT symbol
 * table entry.
 *
 * \return a pointer to a DXF \c VPORT symbol table entry.
 */
DxfVPort *
dxf_vport_set_snap_spacing
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        DxfPoint *snap_spacing
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (snap_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->snap_spacing = snap_spacing;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the X-value of the snap spacing \c snap_spacing_x of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the X-value of the snap spacing \c snap_spacing_x.
 */
double
dxf_vport_get_snap_spacing_x
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->snap_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->snap_spacing->x0);
}


/*!
 * \brief Set the X-value of the snap spacing \c snap_spacing_x of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_snap_spacing_x
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double snap_spacing_x
                /*!< the X-value of the snap spacing \c snap_spacing_x
                 * of a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->snap_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->snap_spacing->x0 = snap_spacing_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the Y-value of the snap spacing \c snap_spacing_y of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the Y-value of the snap spacing \c snap_spacing_y.
 */
double
dxf_vport_get_snap_spacing_y
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->snap_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->snap_spacing->y0);
}


/*!
 * \brief Set the Y-value of the snap spacing \c snap_spacing_y of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_snap_spacing_y
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double snap_spacing_y
                /*!< the Y-value of the snap spacing \c snap_spacing_y
                 * of a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->snap_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->snap_spacing->y0 = snap_spacing_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the grid spacing of viewport \c grid_spacing of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the grid spacing of viewport \c grid_spacing.
 */
DxfPoint *
dxf_vport_get_grid_spacing
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->grid_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->grid_spacing);
}


/*!
 * \brief Set the grid spacing \c grid_spacing of a DXF \c VPORT symbol
 * table entry.
 *
 * \return a pointer to a DXF \c VPORT symbol table entry.
 */
DxfVPort *
dxf_vport_set_grid_spacing
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        DxfPoint *grid_spacing
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (grid_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->grid_spacing = grid_spacing;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the X-value of the grid spacing \c grid_spacing_x of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the X-value of the grid spacing \c grid_spacing_x.
 */
double
dxf_vport_get_grid_spacing_x
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->grid_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->grid_spacing->x0);
}


/*!
 * \brief Set the X-value of the grid spacing \c grid_spacing_x of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_grid_spacing_x
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double grid_spacing_x
                /*!< the X-value of the grid spacing \c grid_spacing_x
                 * of a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->grid_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->grid_spacing->x0 = grid_spacing_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the Y-value of the grid spacing \c grid_spacing_y of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the Y-value of the grid spacing \c grid_spacing_y.
 */
double
dxf_vport_get_grid_spacing_y
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->grid_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->grid_spacing->y0);
}


/*!
 * \brief Set the Y-value of the grid spacing \c grid_spacing_y of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_grid_spacing_y
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double grid_spacing_y
                /*!< the Y-value of the grid spacing \c grid_spacing_y
                 * of a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->grid_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->grid_spacing->y0 = grid_spacing_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the view direction from target point \c direction of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the view direction from target point \c direction.
 */
DxfPoint *
dxf_vport_get_direction
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->direction);
}


/*!
 * \brief Set the view direction from target point \c direction of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to a DXF \c VPORT symbol table entry.
 */
DxfVPort *
dxf_vport_set_direction
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        DxfPoint *direction
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->direction = direction;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the X-value of the view direction from target point
 * \c direction_x of a DXF \c VPORT symbol table entry.
 *
 * \return the X-value of the view direction from target point
 * \c direction_x.
 */
double
dxf_vport_get_direction_x
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->direction->x0);
}


/*!
 * \brief Set the X-value of the view direction from target point
 * \c direction_x of a DXF \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_direction_x
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double direction_x
                /*!< the X-value of the view direction from target point
                 * \c direction_x of a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->direction->x0 = direction_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the Y-value of the view direction from target point
 * \c direction_y of a DXF \c VPORT symbol table entry.
 *
 * \return the Y-value of the view direction from target point
 * \c direction_y.
 */
double
dxf_vport_get_direction_y
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->direction->y0);
}


/*!
 * \brief Set the Y-value of the view direction from target point
 * \c direction_y of a DXF \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_direction_y
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double direction_y
                /*!< the Y-value of the view direction from target point
                 * \c direction_y of a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->direction->y0 = direction_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the Z-value of the view direction from target point
 * \c direction_z of a DXF \c VPORT symbol table entry.
 *
 * \return the Z-value of the view direction from target point
 * \c direction_z.
 */
double
dxf_vport_get_direction_z
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->direction->z0);
}


/*!
 * \brief Set the Z-value of the view direction from target point
 * \c direction_z of a DXF \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_direction_z
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double direction_z
                /*!< the Z-value of the view direction from target point
                 * \c direction_z of a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->direction->z0 = direction_z;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the target point \c target of a DXF \c VPORT symbol table
 * entry.
 *
 * \return the target point \c target.
 */
DxfPoint *
dxf_vport_get_target
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->target);
}


/*!
 * \brief Set the target point \c target of a DXF \c VPORT symbol table
 * entry.
 *
 * \return a pointer to a DXF \c VPORT symbol table entry.
 */
DxfVPort *
dxf_vport_set_target
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        DxfPoint *target
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->target = target;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the X-value of the target point \c target_x of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the X-value of the target point \c target_x.
 */
double
dxf_vport_get_target_x
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->target->x0);
}


/*!
 * \brief Set the X-value of the target point \c target_x of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_target_x
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double target_x
                /*!< the X-value of the target point \c target_x of a
                 * DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->target->x0 = target_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the Y-value of the target point \c target_y of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the Y-value of the target point \c target_y.
 */
double
dxf_vport_get_target_y
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->target->y0);
}


/*!
 * \brief Set the Y-value of the target point \c target_y of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_target_y
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double target_y
                /*!< the Y-value of the target point \c target_y of a
                 * DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->target->y0 = target_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the Z-value of the target point \c target_z of a DXF
 * \c VPORT symbol table entry.
 *
 * \return the Z-value of the target point \c target_z.
 */
double
dxf_vport_get_target_z
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vport->target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->target->z0);
}


/*!
 * \brief Set the Z-value of the target point \c target_z of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_target_z
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double target_z
                /*!< the Z-value of the target point \c target_z of a
                 * DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vport->target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->target->z0 = target_z;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the view height \c view_height of a DXF \c VPORT symbol
 * table entry.
 *
 * \return the view height \c view_height.
 */
double
dxf_vport_get_view_height
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->view_height);
}


/*!
 * \brief Set the view height \c view_height of a DXF \c VPORT symbol
 * table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_view_height
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double view_height
                /*!< the view height \c view_height of a DXF \c VPORT
                 * symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->view_height = view_height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the viewport aspect ratio \c viewport_aspect_ratio of a
 * DXF \c VPORT symbol table entry.
 *
 * \return the viewport aspect ratio \c viewport_aspect_ratio.
 */
double
dxf_vport_get_viewport_aspect_ratio
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->viewport_aspect_ratio);
}


/*!
 * \brief Set the viewport aspect ratio \c viewport_aspect_ratio of a
 * DXF \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_viewport_aspect_ratio
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double viewport_aspect_ratio
                /*!< the viewport aspect ratio \c viewport_aspect_ratio
                 * of a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->viewport_aspect_ratio = viewport_aspect_ratio;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the lens length \c lens_length of a
 * DXF \c VPORT symbol table entry.
 *
 * \return the lens length \c lens_length.
 */
double
dxf_vport_get_lens_length
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->lens_length);
}


/*!
 * \brief Set the lens length \c lens_length of a DXF \c VPORT symbol
 * table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_lens_length
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double lens_length
                /*!< the lens length \c lens_length of a DXF \c VPORT
                 * symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->lens_length = lens_length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the front plane offset \c front_plane_offset of a
 * DXF \c VPORT symbol table entry.
 *
 * \return the front plane offset \c front_plane_offset.
 */
double
dxf_vport_get_front_plane_offset
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->front_plane_offset);
}


/*!
 * \brief Set the front plane offset \c front_plane_offset of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_front_plane_offset
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double front_plane_offset
                /*!< the front plane offset \c front_plane_offset of a
                 * DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->front_plane_offset = front_plane_offset;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the back plane offset \c back_plane_offset of a
 * DXF \c VPORT symbol table entry.
 *
 * \return the back plane offset \c back_plane_offset.
 */
double
dxf_vport_get_back_plane_offset
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->back_plane_offset);
}


/*!
 * \brief Set the back plane offset \c back_plane_offset of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_back_plane_offset
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double back_plane_offset
                /*!< the back plane offset \c back_plane_offset of a
                 * DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->back_plane_offset = back_plane_offset;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the snap rotation angle \c snap_rotation_angle of a
 * DXF \c VPORT symbol table entry.
 *
 * \return the snap rotation angle \c snap_rotation_angle.
 */
double
dxf_vport_get_snap_rotation_angle
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->snap_rotation_angle);
}


/*!
 * \brief Set the snap rotation angle \c snap_rotation_angle of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_snap_rotation_angle
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double snap_rotation_angle
                /*!< the snap rotation angle \c snap_rotation_angle of a
                 * DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->snap_rotation_angle = snap_rotation_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the view twist angle \c view_twist_angle of a
 * DXF \c VPORT symbol table entry.
 *
 * \return the view twist angle \c view_twist_angle.
 */
double
dxf_vport_get_view_twist_angle
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->view_twist_angle);
}


/*!
 * \brief Set the view twist angle \c view_twist_angle of a DXF
 * \c VPORT symbol table entry.
 *
 * \return a pointer to \c vport when successful, or \c NULL when an
 * error occurred.
 */
DxfVPort *
dxf_vport_set_view_twist_angle
(
        DxfVPort *vport,
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
        double view_twist_angle
                /*!< the view twist angle \c view_twist_angle of a
                 * DXF \c VPORT symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vport->view_twist_angle = view_twist_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport);
}


/*!
 * \brief Get the \c status_field from a DXF \c VPORT symbol table entry.
 *
 * \return \c status_field.
 */
int
dxf_vport_get_status_field
(
        DxfVPort *vport
                /*!< a pointer to a DXF \c VPORT symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vport->status_field);
}


/* EOF*/
