/*!
 * \file attdef.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF attribute definition entity (\c ATTDEF).
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


#include "attdef.h"


/*!
 * \brief Allocate memory for a \c DxfAttdef.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfAttdef *attdef = NULL;
        size_t size;

        size = sizeof (DxfAttdef);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((attdef = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfAttdef struct.\n")),
                  __FUNCTION__);
                attdef = NULL;
        }
        else
        {
                memset (attdef, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c ATTDEF entity.
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
DxfAttdef *
dxf_attdef_init
(
        DxfAttdef *attdef
                /*!< DXF attdef entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                attdef = dxf_attdef_new ();
        }
        if (attdef == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfAttdef struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        attdef->default_value = strdup ("");
        attdef->tag_value = strdup ("");
        attdef->prompt_value = strdup ("");
        attdef->id_code = 0;
        attdef->linetype = strdup (DXF_DEFAULT_LINETYPE);
        attdef->text_style = strdup (DXF_DEFAULT_TEXTSTYLE);
        attdef->layer = strdup (DXF_DEFAULT_LAYER);
        attdef->x0 = 0.0;
        attdef->y0 = 0.0;
        attdef->z0 = 0.0;
        attdef->x1 = 0.0;
        attdef->y1 = 0.0;
        attdef->z1 = 0.0;
        attdef->height = 0.0;
        attdef->rel_x_scale = 0.0;
        attdef->rot_angle = 0.0;
        attdef->obl_angle = 0.0;
        attdef->thickness = 0.0;
        attdef->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        attdef->visibility = DXF_DEFAULT_VISIBILITY;
        attdef->color = DXF_COLOR_BYLAYER;
        attdef->paperspace = DXF_MODELSPACE;
        attdef->attr_flags = 0;
        attdef->text_flags = 0;
        attdef->hor_align = 0;
        attdef->field_length = 0;
        attdef->vert_align = 0;
        attdef->extr_x0 = 0.0;
        attdef->extr_y0 = 0.0;
        attdef->extr_z0 = 0.0;
        attdef->dictionary_owner_soft = strdup ("");
        attdef->dictionary_owner_hard = strdup ("");
        attdef->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Read data from a DXF file into an \c ATTDEF entity.
 *
 * The last line read from file contained the string "ATTDEF". \n
 * Now follows some data for the \c ATTDEF, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_attdef. \n
 *
 * \return a pointer to \c attdef.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfAttdef *attdef
                /*!< DXF attdef entity. */
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
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                attdef = dxf_attdef_new ();
                attdef = dxf_attdef_init (attdef);
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
                if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing the attribute
                         * default value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", attdef->default_value);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a tag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", attdef->tag_value);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a prompt
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", attdef->prompt_value);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &attdef->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", attdef->linetype);
                }
                else if (strcmp (temp_string, "7") == 0)
                {
                        /* Now follows a string containing a text style. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", attdef->text_style);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", attdef->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->z1);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (attdef->elevation = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * relative X-scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->rel_x_scale);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->rot_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the
                         * end angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->obl_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &attdef->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &attdef->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &attdef->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * attribute flags value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &attdef->attr_flags);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * text flags value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &attdef->text_flags);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the
                         * horizontal alignment value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &attdef->hor_align);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the
                         * field length value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &attdef->field_length);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the
                         * vertical alignment value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &attdef->vert_align);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
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
                        && (strcmp (temp_string, "AcDbText") != 0)
                        && (strcmp (temp_string, "AcDbAttributeDefinition") != 0))
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
                        fscanf (fp->fp, "%lf\n", &attdef->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", attdef->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", attdef->dictionary_owner_hard);
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
        if (strcmp (attdef->linetype, "") == 0)
        {
                attdef->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (attdef->layer, "") == 0)
        {
                attdef->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Write DXF output to fp for a attribute definition entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_attdef_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfAttdef *attdef
                /*!< attribute definition entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("ATTDEF");

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
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (attdef->tag_value, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () default tag value string is empty for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, attdef->id_code);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (attdef->text_style, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () text style string is empty for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, attdef->id_code);
                fprintf (stderr,
                  (_("\tdefault text style STANDARD applied to %s entity.\n")),
                  dxf_entity_name);
                attdef->text_style = strdup (DXF_DEFAULT_TEXTSTYLE);
        }
        if (strcmp (attdef->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, attdef->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                attdef->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (attdef->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, attdef->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                attdef->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (attdef->height == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () height has a value of 0.0 for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, attdef->id_code);
                fprintf (stderr,
                  (_("\tdefault height of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                attdef->height = 1.0;
        }
        if (attdef->rel_x_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, attdef->id_code);
                fprintf (stderr,
                  (_("\tdefault relative X-scale of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                attdef->rel_x_scale = 1.0;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (attdef->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", attdef->id_code);
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
        if ((strcmp (attdef->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", attdef->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (attdef->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", attdef->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (attdef->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", attdef->layer);
        if (strcmp (attdef->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", attdef->linetype);
        }
        if (attdef->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", attdef->color);
        }
        if (attdef->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", attdef->linetype_scale);
        }
        if (attdef->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", attdef->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbText\n");
        }
        if (attdef->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", attdef->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", attdef->x0);
        fprintf (fp->fp, " 20\n%f\n", attdef->y0);
        fprintf (fp->fp, " 30\n%f\n", attdef->z0);
        fprintf (fp->fp, " 40\n%f\n", attdef->height);
        fprintf (fp->fp, "  1\n%s\n", attdef->default_value);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbAttributeDefinition\n");
        }
        fprintf (fp->fp, "  3\n%s\n", attdef->prompt_value);
        fprintf (fp->fp, "  2\n%s\n", attdef->tag_value);
        fprintf (fp->fp, " 70\n%d\n", attdef->attr_flags);
        if (attdef->field_length != 0)
        {
                fprintf (fp->fp, " 73\n%d\n", attdef->field_length);
        }
        if (attdef->rot_angle != 0.0)
        {
                fprintf (fp->fp, " 50\n%f\n", attdef->rot_angle);
        }
        if (attdef->rel_x_scale != 1.0)
        {
                fprintf (fp->fp, " 41\n%f\n", attdef->rel_x_scale);
        }
        if (attdef->obl_angle != 0.0)
        {
                fprintf (fp->fp, " 51\n%f\n", attdef->obl_angle);
        }
        if (strcmp (attdef->text_style, "STANDARD") != 0)
        {
                fprintf (fp->fp, "  7\n%s\n", attdef->text_style);
        }
        if (attdef->text_flags != 0)
        {
                fprintf (fp->fp, " 71\n%d\n", attdef->text_flags);
        }
        if (attdef->hor_align != 0)
        {
                fprintf (fp->fp, " 72\n%d\n", attdef->hor_align);
        }
        if (attdef->vert_align != 0)
        {
                fprintf (fp->fp, " 74\n%d\n", attdef->vert_align);
        }
        if ((attdef->hor_align != 0) || (attdef->vert_align != 0))
        {
                if ((attdef->x0 == attdef->x1)
                        && (attdef->y0 == attdef->y1)
                        && (attdef->z0 == attdef->z1))
                {
                        fprintf (stderr,
                          (_("Warning in %s () insertion point and alignment point are identical for the %s entity with id-code: %x.\n")),
                          __FUNCTION__, dxf_entity_name, attdef->id_code);
                        fprintf (stderr,
                          (_("\tdefault justification applied to %s entity.\n")),
                          dxf_entity_name);
                        attdef->hor_align = 0;
                        attdef->vert_align = 0;
                }
                else
                {
                        fprintf (fp->fp, " 11\n%f\n", attdef->x1);
                        fprintf (fp->fp, " 21\n%f\n", attdef->y1);
                        fprintf (fp->fp, " 31\n%f\n", attdef->z1);
                }
        }
        if (fp->acad_version_number >= AutoCAD_12)
        {
                fprintf (fp->fp, "210\n%f\n", attdef->extr_x0);
                fprintf (fp->fp, "220\n%f\n", attdef->extr_y0);
                fprintf (fp->fp, "230\n%f\n", attdef->extr_z0);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocate memory for a DXF \c ATTDEF and all it's
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
dxf_attdef_free
(
        DxfAttdef *attdef
                /*!< DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (attdef->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfAttdef was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (attdef->linetype);
        free (attdef->layer);
        free (attdef->default_value);
        free (attdef->tag_value);
        free (attdef->prompt_value);
        free (attdef->text_style);
        free (attdef->dictionary_owner_soft);
        free (attdef->dictionary_owner_hard);
        free (attdef);
        attdef = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c ATTDEF
 * entities and all their data fields.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
void
dxf_attdef_free_chain
(
        DxfAttdef *attdefs
                /*!< pointer to the chain of DXF \c ATTDEF entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (attdefs == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (attdefs != NULL)
        {
                struct DxfAttdef *iter = attdefs->next;
                dxf_attdef_free (attdefs);
                attdefs = (DxfAttdef *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c ATTDEF entity.
 *
 * \return ID code.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_attdef_get_id_code
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = attdef->id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the ID code for a DXF \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_id_code
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
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
        if (attdef == NULL)
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
        attdef->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the linetype from a DXF \c ATTDEF entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_attdef_get_linetype
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (attdef->linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the linetype for a DXF \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_linetype
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the layer from a DXF \c ATTDEF entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_attdef_get_layer
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (attdef->layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the layer for a DXF \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_layer
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the elevation from a DXF \c ATTDEF entity.
 *
 * \return elevation.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_attdef_get_elevation
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = attdef->elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the elevation for a DXF \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_elevation
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the thickness from a DXF \c ATTDEF entity.
 *
 * \return thickness.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_attdef_get_thickness
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the thickness member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = attdef->thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the thickness for a DXF \c ATTDF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_thickness
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the linetype scale from a DXF \c ATTDEF entity.
 *
 * \return linetype scale.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_attdef_get_linetype_scale
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the linetype scale member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = attdef->linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the linetype scale for a DXF \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_linetype_scale
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the visibility from a DXF \c ATTDEF entity.
 *
 * \return visibility.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int16_t
dxf_attdef_get_visibility
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int16_t result;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = attdef->visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the visibility for a DXF \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_visibility
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the color from a DXF \c ATTDEF entity.
 *
 * \return color.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_attdef_get_color
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the color member.\n")),
                  __FUNCTION__);
        }
        result = attdef->color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the color for a DXF \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_color
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c ATTDEF entity.
 *
 * \return paperspace flag value.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_attdef_get_paperspace
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        if (attdef->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        result = attdef->paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the paperspace flag for a DXF \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_paperspace
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c ATTDEF entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_attdef_get_dictionary_owner_soft
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (attdef->dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_dictionary_owner_soft
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c ATTDEF entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_attdef_get_dictionary_owner_hard
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_hard member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (attdef->dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_dictionary_owner_hard
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the default value from a DXF \c ATTDEF entity.
 *
 * \return default value.
 *
 * \warning No checks are performed on the returned pointer (string).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_attdef_get_default_value
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->default_value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the default_value member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (attdef->default_value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the default value for a DXF \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_default_value
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *default_value
                /*!< a string containing the default_value for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (default_value == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->default_value = strdup (default_value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the tag value from a DXF \c ATTDEF entity.
 *
 * \return tag value.
 *
 * \warning No checks are performed on the returned pointer (string).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_attdef_get_tag_value
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->tag_value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the tag_value member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (attdef->tag_value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the tag value for a DXF \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_tag_value
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *tag_value
                /*!< a string containing the tag_value for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tag_value == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->tag_value = strdup (tag_value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the promp value from a DXF \c ATTDEF entity.
 *
 * \return prompt value.
 *
 * \warning No checks are performed on the returned pointer (string).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_attdef_get_prompt_value
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->prompt_value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the tag_value member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (attdef->prompt_value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the prompt value for a DXF \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_prompt_value
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *prompt_value
                /*!< a string containing the prompt_value for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (prompt_value == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->prompt_value = strdup (prompt_value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the text style from a DXF \c ATTDEF entity.
 *
 * \return text style.
 *
 * \warning No checks are performed on the returned pointer (string).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_attdef_get_text_style
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->text_style ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the tag_value member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (attdef->text_style);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the text style for a DXF \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_text_style
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *text_style
                /*!< a string containing the text style for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text_style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->text_style = strdup (text_style);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the start point of a DXF \c ATTDEF entity.
 *
 * \return the start point.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPoint *
dxf_attdef_get_start_point
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c ATTDEF.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (attdef == NULL)
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
        p1->x0 = attdef->x0;
        p1->y0 = attdef->y0;
        p1->z0 = attdef->z0;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (attdef->linetype != NULL)
                        {
                                p1->linetype = strdup (attdef->linetype);
                        }
                        if (attdef->layer != NULL)
                        {
                                p1->layer = strdup (attdef->layer);
                        }
                        p1->thickness = attdef->thickness;
                        p1->linetype_scale = attdef->linetype_scale;
                        p1->visibility = attdef->visibility;
                        p1->color = attdef->color;
                        p1->paperspace = attdef->paperspace;
                        if (attdef->dictionary_owner_soft != NULL)
                        {
                                p1->dictionary_owner_soft = strdup (attdef->dictionary_owner_soft);
                        }
                        if (attdef->dictionary_owner_hard != NULL)
                        {
                                p1->dictionary_owner_hard = strdup (attdef->dictionary_owner_hard);
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
 * \brief Set the start point of a DXF \c ATTDEF entity.
 *
 * \return a pointer to a DXF \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_start_point
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->x0 = point->x0;
        attdef->y0 = point->y0;
        attdef->z0 = point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the alignment point of a DXF \c ATTDEF entity.
 *
 * \return the alignment point.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPoint *
dxf_attdef_get_alignment_point
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c ATTDEF.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (attdef == NULL)
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
        p1->x0 = attdef->x1;
        p1->y0 = attdef->y1;
        p1->z0 = attdef->z1;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (attdef->linetype != NULL)
                        {
                                p1->linetype = strdup (attdef->linetype);
                        }
                        if (attdef->layer != NULL)
                        {
                                p1->layer = strdup (attdef->layer);
                        }
                        p1->thickness = attdef->thickness;
                        p1->linetype_scale = attdef->linetype_scale;
                        p1->visibility = attdef->visibility;
                        p1->color = attdef->color;
                        p1->paperspace = attdef->paperspace;
                        if (attdef->dictionary_owner_soft != NULL)
                        {
                                p1->dictionary_owner_soft = strdup (attdef->dictionary_owner_soft);
                        }
                        if (attdef->dictionary_owner_hard != NULL)
                        {
                                p1->dictionary_owner_hard = strdup (attdef->dictionary_owner_hard);
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
 * \brief Set the alignment point of a DXF \c ATTDEF entity.
 *
 * \return a pointer to a DXF \c ATTDEF entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAttdef *
dxf_attdef_set_alignment_point
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->x1 = point->x0;
        attdef->y1 = point->y0;
        attdef->z1 = point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Test if the attribute definition is invisible.
 *
 * \return \c TRUE when the attribute definition is invisible,
 * or \c FALSE when the attribute definition is visible.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_attdef_is_invisible
(
        DxfAttdef *attdef
                /*!< DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (attdef->attr_flags, 0);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if the attribute definition is a constant attribute.
 *
 * \return \c TRUE when the attribute definition is a constant,
 * or \c FALSE when the attribute definition is not a constant.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_attdef_is_constant
(
        DxfAttdef *attdef
                /*!< DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (attdef->attr_flags, 1);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if the attribute definition input needs to be verified.
 *
 * \return \c TRUE when the input needs to be verified,
 * or \c FALSE when the input needs not to be verified.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_attdef_is_verification_required
(
        DxfAttdef *attdef
                /*!< DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (attdef->attr_flags, 2);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if the attribute definition is preset (no prompt during
 * insertion).
 *
 * \return \c TRUE when the attributre definition is preset,
 * or \c FALSE when the attribute definition is not preset.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_attdef_is_preset
(
        DxfAttdef *attdef
                /*!< DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (attdef->attr_flags, 3);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/* EOF */
