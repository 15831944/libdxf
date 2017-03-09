/*!
 * \file leader.c
 *
 * \author Copyright (C) 2015, 2017 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF leader entity (\c LEADER).
 *
 * \since The \c LEADER entity was introduced in DXF R13.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
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


#include "leader.h"


/*!
 * \brief Allocate memory for a DXF \c LEADER.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfLeader *
dxf_leader_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLeader *leader = NULL;
        size_t size;

        size = sizeof (DxfLeader);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((leader = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfArc struct.\n")),
                  __FUNCTION__);
                leader = NULL;
        }
        else
        {
                memset (leader, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c LEADER
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfLeader *
dxf_leader_init
(
        DxfLeader *leader
                /*!< pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                leader = dxf_leader_new ();
        }
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfLeader struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->id_code = 0;
        leader->linetype = strdup (DXF_DEFAULT_LINETYPE);
        leader->layer = strdup (DXF_DEFAULT_LAYER);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                leader->x0[i] = 0.0;
                leader->y0[i] = 0.0;
                leader->z0[i] = 0.0;
        }
        leader->extr_x0 = 0.0;
        leader->extr_y0 = 0.0;
        leader->extr_z0 = 0.0;
        leader->elevation = 0.0;
        leader->thickness = 0.0;
        leader->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        leader->visibility = DXF_DEFAULT_VISIBILITY;
        leader->color = DXF_COLOR_BYLAYER;
        leader->paperspace = DXF_MODELSPACE;
        leader->dictionary_owner_soft = strdup ("");
        leader->dictionary_owner_hard = strdup ("");
        leader->dimension_style_name = strdup ("");
        leader->text_annotation_height = 0.0;
        leader->text_annotation_width = 0.0;
        leader->arrow_head_flag = 0;
        leader->path_type = 0;
        leader->creation_flag = 0;
        leader->hookline_direction_flag = 0;
        leader->hookline_flag = 0;
        leader->number_vertices = 0;
        leader->leader_color = 0;
        leader->x1 = 0.0;
        leader->y1 = 0.0;
        leader->z1 = 0.0;
        leader->x2 = 0.0;
        leader->y2 = 0.0;
        leader->z2 = 0.0;
        leader->x3 = 0.0;
        leader->y3 = 0.0;
        leader->z3 = 0.0;
        leader->annotation_reference_hard = strdup ("");
        leader->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Read data from a DXF file into a DXF \c LEADER entity.
 *
 * The last line read from file contained the string "LEADER". \n
 * Now follows some data for the \c LEADER, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c leader. \n
 *
 * \return \c a pointer to \c leader.
 */
DxfLeader *
dxf_leader_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfLeader *leader
                /*!< Pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;

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
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                leader = dxf_leader_new ();
                leader = dxf_leader_init (leader);
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
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                else if (strcmp (temp_string, "  3") == 0)
                {
                        /* Now follows a string containing additional
                         * proprietary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", leader->dimension_style_name);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &leader->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", leader->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", leader->layer);
                }
                else if ((strcmp (temp_string, "10") == 0)
                  || (strcmp (temp_string, "20") == 0)
                  || (strcmp (temp_string, "30") == 0))
                {
                        if (strcmp (temp_string, "10") == 0)
                        {
                                /* Now follows a string containing the X-value
                                 * of the Vertex coordinates (one entry for each
                                 * vertex). */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%lf\n", &leader->x0[i]);
                        }
                        else if (strcmp (temp_string, "20") == 0)
                        {
                                /* Now follows a string containing the Y-value
                                 * of the Vertex coordinates (one entry for each
                                 * vertex). */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%lf\n", &leader->y0[i]);
                        }
                        else if (strcmp (temp_string, "30") == 0)
                        {
                                /* Now follows a string containing the Z-value
                                 * of the Vertex coordinates (one entry for each
                                 * vertex). */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%lf\n", &leader->z0[i]);
                                i++;
                        }
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                  && DXF_FLATLAND
                  && (strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the text
                         * annotation height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->text_annotation_height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the text
                         * annotation width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->text_annotation_width);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &leader->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->paperspace);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the arrow
                         * head flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->arrow_head_flag);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the path type. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->path_type);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the creation
                         * flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->creation_flag);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the hookline
                         * direction flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->hookline_direction_flag);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing the hookline
                         * flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->hookline_flag);
                }
                else if (strcmp (temp_string, "76") == 0)
                {
                        /* Now follows a string containing the number of
                         * vertices. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->number_vertices);
                }
                else if (strcmp (temp_string, "77") == 0)
                {
                        /* Now follows a string containing the leader
                         * color. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->leader_color);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "AcDbLeader") != 0)
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
                        fscanf (fp->fp, "%lf\n", &leader->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->extr_z0);
                }
                else if (strcmp (temp_string, "211") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the "Horizontal" direction for
                         * leader. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->x1);
                }
                else if (strcmp (temp_string, "221") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the "Horizontal" direction for
                         * leader. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->y1);
                }
                else if (strcmp (temp_string, "231") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the "Horizontal" direction for
                         * leader. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->z1);
                }
                else if (strcmp (temp_string, "212") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the Block reference insertion
                         * point offset from last leader vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->x2);
                }
                else if (strcmp (temp_string, "222") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the Block reference insertion
                         * point offset from last leader vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->y2);
                }
                else if (strcmp (temp_string, "232") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the Block reference insertion
                         * point offset from last leader vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->z2);
                }
                else if (strcmp (temp_string, "213") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the Annotation placement point
                         * offset from last leader vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->x3);
                }
                else if (strcmp (temp_string, "223") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the Annotation placement point
                         * offset from last leader vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->y3);
                }
                else if (strcmp (temp_string, "233") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the Annotation placement point
                         * offset from last leader vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->z3);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", leader->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "340") == 0)
                {
                        /* Now follows a string containing Hard
                         * reference to associated annotation (mtext,
                         * tolerance, or insert entity). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", leader->annotation_reference_hard);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", leader->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, (_("DXF comment: %s\n")), temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (leader->linetype, "") == 0)
        {
                leader->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (leader->layer, "") == 0)
        {
                leader->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Write DXF output to a file for a DXF \c LEADER entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_leader_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfLeader *leader
                /*!< DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("LEADER");
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
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, leader->id_code);
        }
        if (strcmp (leader->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, leader->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                leader->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (leader->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, leader->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                leader->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (leader->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", leader->id_code);
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
        if ((strcmp (leader->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", leader->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (leader->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", leader->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (leader->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", leader->layer);
        if (strcmp (leader->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", leader->linetype);
        }
        if (leader->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", leader->color);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (leader->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", leader->elevation);
        }
        if (leader->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", leader->thickness);
        }
        if (leader->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", leader->linetype_scale);
        }
        if (leader->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", leader->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbLeader\n");
        }
        fprintf (fp->fp, "  3\n%s\n", leader->dimension_style_name);
        fprintf (fp->fp, " 71\n%d\n", leader->arrow_head_flag);
        fprintf (fp->fp, " 72\n%d\n", leader->path_type);
        fprintf (fp->fp, " 73\n%d\n", leader->creation_flag);
        fprintf (fp->fp, " 74\n%d\n", leader->hookline_direction_flag);
        fprintf (fp->fp, " 75\n%d\n", leader->hookline_flag);
        fprintf (fp->fp, " 40\n%f\n", leader->text_annotation_height);
        fprintf (fp->fp, " 41\n%f\n", leader->text_annotation_width);
        fprintf (fp->fp, " 76\n%d\n", leader->number_vertices);
        for (i = 0; i < leader->number_vertices; i++)
        {
                fprintf (fp->fp, " 10\n%f\n", leader->x0[i]);
                fprintf (fp->fp, " 20\n%f\n", leader->y0[i]);
                fprintf (fp->fp, " 30\n%f\n", leader->z0[i]);
        }
        fprintf (fp->fp, " 77\n%d\n", leader->leader_color);
        fprintf (fp->fp, "340\n%s\n", leader->annotation_reference_hard);
        fprintf (fp->fp, "210\n%f\n", leader->extr_x0);
        fprintf (fp->fp, "220\n%f\n", leader->extr_y0);
        fprintf (fp->fp, "230\n%f\n", leader->extr_z0);
        fprintf (fp->fp, "211\n%f\n", leader->x1);
        fprintf (fp->fp, "221\n%f\n", leader->y1);
        fprintf (fp->fp, "231\n%f\n", leader->z1);
        fprintf (fp->fp, "212\n%f\n", leader->x2);
        fprintf (fp->fp, "222\n%f\n", leader->y2);
        fprintf (fp->fp, "232\n%f\n", leader->z2);
        fprintf (fp->fp, "213\n%f\n", leader->x3);
        fprintf (fp->fp, "223\n%f\n", leader->y3);
        fprintf (fp->fp, "233\n%f\n", leader->z3);
        /*! \todo Xdata belonging to the application ID "ACAD" may
         * follow.\n This describes any dimension overrides that have
         * been applied to this entity. */
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c LEADER and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_leader_free
(
        DxfLeader *leader
                /*!< Pointer to the memory occupied by the DXF
                 * \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfLeader was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (leader->linetype);
        free (leader->layer);
        free (leader->dictionary_owner_soft);
        free (leader->dictionary_owner_hard);
        free (leader->dimension_style_name);
        free (leader->annotation_reference_hard);
        free (leader);
        leader = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c LEADER
 * entities and all their data fields.
 */
void
dxf_leader_free_chain
(
        DxfLeader *leaders
                /*!< pointer to the chain of DXF \c LEADER entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (leaders == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (leaders != NULL)
        {
                struct DxfLeader *iter = leaders->next;
                dxf_leader_free (leaders);
                leaders = (DxfLeader *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c LEADER entity.
 *
 * \return ID code.
 */
int
dxf_leader_get_id_code
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_id_code
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
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
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the linetype from a DXF \c LEADER entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_leader_get_linetype
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (leader->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (leader->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_linetype
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
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
        leader->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the layer from a DXF \c LEADER entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_leader_get_layer
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (leader->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (leader->layer));
}


/*!
 * \brief Set the layer for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_layer
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
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
        leader->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the elevation from a DXF \c LEADER entity.
 *
 * \return elevation.
 */
double
dxf_leader_get_elevation
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->elevation);
}


/*!
 * \brief Set the elevation for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_elevation
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the thickness from a DXF \c LEADER entity.
 *
 * \return thickness.
 */
double
dxf_leader_get_thickness
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->thickness);
}


/*!
 * \brief Set the thickness for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_thickness
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the linetype scale from a DXF \c LEADER entity.
 *
 * \return linetype scale.
 */
double
dxf_leader_get_linetype_scale
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->linetype_scale);
}


/*!
 * \brief Set the linetype scale for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_linetype_scale
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the visibility from a DXF \c LEADER entity.
 *
 * \return visibility.
 */
int16_t
dxf_leader_get_visibility
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->visibility);
}


/*!
 * \brief Set the visibility for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_visibility
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the color from a DXF \c LEADER entity.
 *
 * \return color.
 */
int
dxf_leader_get_color
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->color);
}


/*!
 * \brief Set the color for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_color
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        leader->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c LEADER entity.
 *
 * \return paperspace flag value.
 */
int
dxf_leader_get_paperspace
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (leader->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->paperspace);
}


/*!
 * \brief Set the paperspace flag for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_paperspace
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        int paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c LEADER entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_leader_get_dictionary_owner_soft
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (leader->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (leader->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_dictionary_owner_soft
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
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
        leader->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c LEADER entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_leader_get_dictionary_owner_hard
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (leader->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (leader->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_dictionary_owner_hard
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
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
        leader->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the \c dimenion_style_name from a DXF \c LEADER entity.
 *
 * \return \c dimension_style_name when sucessful, \c NULL when an error
 * occurred.
 */
char *
dxf_leader_get_dimension_style_name
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (leader->dimension_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (leader->dimension_style_name));
}


/*!
 * \brief Set the \c dimension_style_name for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_dimension_style_name
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        char *dimension_style_name
                /*!< a string containing the \c dimension_style_name for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension_style_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->layer = strdup (dimension_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the vertex coordinates \c p0 of a DXF \c LEADER entity.
 *
 * \return the vertex coordinates \c p0.
 */
DxfPoint *
dxf_leader_get_p0
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (leader->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->p0);
}


/*!
 * \brief Set the vertex coordinates \c p0 of a DXF \c LEADER entity.
 *
 * \return a pointer to a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_p0
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c ARC entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the X-value of the vertex coordinates \c x0 of a DXF
 * \c LEADER entity.
 *
 * \return the X-value of the vertex coordinates \c x0.
 */
double
dxf_leader_get_x0
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->p0->x0);
}


/*!
 * \brief Set the X-value of the vertex coordinates \c x0 of a DXF
 * \c LEADER entity.
 *
 * \return a pointer to \c leader when successful, or \c NULL when an
 * error occurred.
 */
DxfLeader *
dxf_leader_set_x0
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        double x0
                /*!< the X-value of the vertex coordinates \c x0 of a
                 * DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (leader->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the Y-value of the vertex coordinates \c y0 of a DXF
 * \c LEADER entity.
 *
 * \return the Y-value of the vertex coordinates \c y0.
 */
double
dxf_leader_get_y0
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->p0->y0);
}


/*!
 * \brief Set the Y-value of the vertex coordinates \c y0 of a DXF
 * \c LEADER entity.
 *
 * \return a pointer to \c leader when successful, or \c NULL when an
 * error occurred.
 */
DxfLeader *
dxf_leader_set_y0
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        double y0
                /*!< the Y-value of the vertex coordinates \c y0 of a
                 * DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (leader->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the Z-value of the vertex coordinates \c z0 of a DXF
 * \c LEADER entity.
 *
 * \return the Z-value of the vertex coordinates \c z0.
 */
double
dxf_leader_get_z0
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->p0->z0);
}


/*!
 * \brief Set the Z-value of the vertex coordinates \c z0 of a DXF
 * \c LEADER entity.
 *
 * \return a pointer to \c leader when successful, or \c NULL when an
 * error occurred.
 */
DxfLeader *
dxf_leader_set_z0
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        double z0
                /*!< the Z-value of the vertex coordinates \c z0 of a
                 * DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (leader->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the \c text_annotation_height of a DXF \c LEADER entity.
 *
 * \return the \c text_annotation_height.
 */
double
dxf_leader_get_text_annotation_height
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->text_annotation_height < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->text_annotation_height);
}


/*!
 * \brief Set the \c text_annotation_height of a DXF \c LEADER entity.
 *
 * \return a pointer to \c leader when successful, or \c NULL when an
 * error occurred.
 */
DxfLeader *
dxf_leader_set_text_annotation_height
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        double text_annotation_height
                /*!< the \c text_annotation_height of a DXF \c LEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text_annotation_height < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        leader->text_annotation_height = text_annotation_height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the \c text_annotation_width of a DXF \c LEADER entity.
 *
 * \return the \c text_annotation_width.
 */
double
dxf_leader_get_text_annotation_width
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->text_annotation_width < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->text_annotation_width);
}


/*!
 * \brief Set the \c text_annotation_width of a DXF \c LEADER entity.
 *
 * \return a pointer to \c leader when successful, or \c NULL when an
 * error occurred.
 */
DxfLeader *
dxf_leader_set_text_annotation_width
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        double text_annotation_width
                /*!< the \c text_annotation_width of a DXF \c LEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text_annotation_width < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        leader->text_annotation_width = text_annotation_width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the \c arrow_head_flag from a DXF \c LEADER entity.
 *
 * \return \c arrow_head_flag.
 */
int
dxf_leader_get_arrow_head_flag
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->arrow_head_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->arrow_head_flag > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->arrow_head_flag);
}


/*!
 * \brief Set the \c arrow_head_flag for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_arrow_head_flag
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        int arrow_head_flag
                /*!< the \c arrow_head_flag to be set. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arrow_head_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arrow_head_flag > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->arrow_head_flag = arrow_head_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the \c path_type from a DXF \c LEADER entity.
 *
 * \return \c path_type.
 */
int
dxf_leader_get_path_type
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->path_type < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->path_type > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->path_type);
}


/*!
 * \brief Set the \c path_type for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_path_type
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        int path_type
                /*!< the \c path_type to be set. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (path_type < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (path_type > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->path_type = path_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the \c creation_flag from a DXF \c LEADER entity.
 *
 * \return \c creation_flag.
 */
int
dxf_leader_get_creation_flag
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->creation_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->creation_flag > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->creation_flag);
}


/*!
 * \brief Set the \c creation_flag for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_creation_flag
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        int creation_flag
                /*!< the \c creation_flag to be set. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (creation_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (creation_flag > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->creation_flag = creation_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the \c hookline_direction_flag from a DXF \c LEADER entity.
 *
 * \return \c hookline_direction_flag.
 */
int
dxf_leader_get_hookline_direction_flag
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->hookline_direction_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->hookline_direction_flag > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->hookline_direction_flag);
}


/*!
 * \brief Set the \c hookline_direction_flag for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_hookline_direction_flag
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        int hookline_direction_flag
                /*!< the \c hookline_direction_flag to be set. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hookline_direction_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hookline_direction_flag > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->hookline_direction_flag = hookline_direction_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the \c hookline_flag from a DXF \c LEADER entity.
 *
 * \return \c hookline_flag.
 */
int
dxf_leader_get_hookline_flag
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->hookline_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->hookline_flag > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->hookline_flag);
}


/*!
 * \brief Set the \c hookline_flag for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_hookline_flag
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        int hookline_flag
                /*!< the \c hookline_flag to be set. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hookline_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hookline_flag > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->hookline_flag = hookline_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the \c number_vertices from a DXF \c LEADER entity.
 *
 * \return \c number_vertices.
 */
int
dxf_leader_get_number_vertices
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->number_vertices < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->number_vertices);
}


/*!
 * \brief Set the \c number_vertices for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_number_vertices
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        int number_vertices
                /*!< the \c number_vertices to be set. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_vertices < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->number_vertices = number_vertices;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the \c leader_color from a DXF \c LEADER entity.
 *
 * \return \c leader_color.
 */
int
dxf_leader_get_leader_color
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->leader_color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->leader_color);
}


/*!
 * \brief Set the \c leader_color for a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_leader_color
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        int leader_color
                /*!< the \c leader_color to be set. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (leader_color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        leader->leader_color = leader_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c LEADER entity.
 *
 * \return the X-value of the extrusion vector \c extr_x0.
 */
double
dxf_leader_get_extr_x0
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c LEADER entity.
 *
 * \return a pointer to \c leader when successful, or \c NULL when an
 * error occurred.
 */
DxfLeader *
dxf_leader_set_extr_x0
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector \c extr_x0 of a
                 * DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c LEADER entity.
 *
 * \return the Y-value of the extrusion vector \c extr_y0.
 */
double
dxf_leader_get_extr_y0
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c LEADER entity.
 *
 * \return a pointer to \c leader when successful, or \c NULL when an
 * error occurred.
 */
DxfLeader *
dxf_leader_set_extr_y0
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector \c extr_y0 of a
                 * DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c LEADER entity.
 *
 * \return the Z-value of the extrusion vector \c extr_z0.
 */
double
dxf_leader_get_extr_z0
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c LEADER entity.
 *
 * \return a pointer to \c leader when successful, or \c NULL when an
 * error occurred.
 */
DxfLeader *
dxf_leader_set_extr_z0
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector \c extr_z0 of a
                 * DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the "Horizontal" direction for leader \c p1 of a DXF
 * \c LEADER entity.
 *
 * \return  \c p1.
 */
DxfPoint *
dxf_leader_get_p1
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (leader->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->p1);
}


/*!
 * \brief Set the "Horizontal" direction for leader \c p1 of a DXF
 * \c LEADER entity.
 *
 * \return a pointer to a DXF \c LEADER entity.
 */
DxfLeader *
dxf_leader_set_p1
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c ARC entity. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the X-value of the "Horizontal" direction for leader
 * \c x1 of a DXF \c LEADER entity.
 *
 * \return the X-value of the "Horizontal" direction for leader \c x1.
 */
double
dxf_leader_get_x1
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->p1->x0);
}


/*!
 * \brief Set the X-value of the "Horizontal" direction for leader
 * \c x1 of a DXF \c LEADER entity.
 *
 * \return a pointer to \c leader when successful, or \c NULL when an
 * error occurred.
 */
DxfLeader *
dxf_leader_set_x1
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        double x1
                /*!< the X-value of the "Horizontal" direction for
                 * leader \c x1 of a DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (leader->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the Y-value of the "Horizontal" direction for leader
 * \c y1 of a DXF \c LEADER entity.
 *
 * \return the Y-value of the "Horizontal" direction for leader \c y1.
 */
double
dxf_leader_get_y1
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->p1->y0);
}


/*!
 * \brief Set the Y-value of the "Horizontal" direction for leader
 * \c y1 of a DXF \c LEADER entity.
 *
 * \return a pointer to \c leader when successful, or \c NULL when an
 * error occurred.
 */
DxfLeader *
dxf_leader_set_y1
(
        DxfLeader *leader,
                /*!< a pointer to a DXF \c LEADER entity. */
        double y1
                /*!< the Y-value of the "Horizontal" direction for
                 * leader \c y1 of a DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (leader->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Get the Z-value of the "Horizontal" direction for leader
 * \c z1 of a DXF \c LEADER entity.
 *
 * \return the Z-value of the "Horizontal" direction for leader \c z1.
 */
double
dxf_leader_get_z1
(
        DxfLeader *leader
                /*!< a pointer to a DXF \c LEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (leader->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader->p1->z0);
}


/* EOF */
