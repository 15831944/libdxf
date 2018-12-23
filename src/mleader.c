/*!
 * \file mleader.c
 *
 * \author Copyright (C) 2018 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF mleader entity (\c MLEADER).
 *
 * \since The \c MLEADER entity was introduced in DXF R2007.
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


#include "mleader.h"


/*!
 * \brief Allocate memory for a DXF \c MLEADER entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMLeader *
dxf_mleader_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMLeader *mleader = NULL;
        size_t size;

        size = sizeof (DxfMLeader);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((mleader = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                mleader = NULL;
        }
        else
        {
                memset (mleader, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c MLEADER
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMLeader *
dxf_mleader_init
(
        DxfMLeader *mleader
                /*!< a pointer to the DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mleader = dxf_mleader_new ();
        }
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->id_code = 0;
        mleader->linetype = strdup (DXF_DEFAULT_LINETYPE);
        mleader->layer = strdup (DXF_DEFAULT_LAYER);
        mleader->elevation = 0.0;
        mleader->thickness = 0.0;
        mleader->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        mleader->visibility = DXF_DEFAULT_VISIBILITY;
        mleader->color = DXF_COLOR_BYLAYER;
        mleader->paperspace = DXF_MODELSPACE;
        mleader->graphics_data_size = 0;
        mleader->shadow_mode = 0;
        mleader->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ();
        mleader->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init (mleader->binary_graphics_data);
        mleader->dictionary_owner_soft = strdup ("");
        mleader->object_owner_soft = strdup ("");
        mleader->material = strdup ("");
        mleader->dictionary_owner_hard = strdup ("");
        mleader->lineweight = 0;
        mleader->plot_style_name = strdup ("");
        mleader->color_value = 0;
        mleader->color_name = strdup ("");
        mleader->transparency = 0;
        mleader->block_content_scale = 0.0;
        mleader->dogleg_length = 0.0;
        mleader->arrowhead_size = 0.0;
        mleader->block_content_rotation = 0.0;
        mleader->block_attribute_width = 0.0;
        mleader->property_override_flag = 0;
        mleader->leader_line_color = 0;
        mleader->text_color = 0;
        mleader->block_content_color = 0;
        mleader->arrowhead_index = 0;
        mleader->text_right_attachment_type = 0;
        mleader->leader_linetype_style = 0;
        mleader->leader_line_weight = 0;
        mleader->content_type = 0;
        mleader->text_left_attachment_type = 0;
        mleader->text_angle_type = 0;
        mleader->text_alignment_type = 0;
        mleader->block_content_connection_type = 0;
        mleader->block_attribute_index = 0;
        mleader->text_align_in_IPE = 0;
        mleader->text_attachment_point = 0;
        mleader->text_attachment_direction = 0;
        mleader->bottom_text_attachment_direction = 0;
        mleader->top_text_attachment_direction = 0;
        mleader->enable_landing = 0;
        mleader->enable_dogleg = 0;
        mleader->enable_frame_text = 0;
        mleader->enable_annotation_scale = 0;
        mleader->text_direction_negative = 0;
        mleader->block_attribute_text_string = strdup ("");
        mleader->block_attribute_id = strdup ("");
        mleader->leader_style_id = strdup ("");
        mleader->arrowhead_id = strdup ("");
        mleader->text_style_id = strdup ("");
        mleader->block_content_id = strdup ("");
        mleader->arrow_head_id = strdup ("");
        mleader->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Free the allocated memory for a DXF \c MLEADER entity and all
 * it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_mleader_free
(
        DxfMLeader *mleader
                /*!< a pointer to the memory occupied by the DXF
                 * \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleader->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (mleader->linetype);
        free (mleader->layer);
        dxf_binary_graphics_data_free_list (mleader->binary_graphics_data);
        free (mleader->dictionary_owner_soft);
        free (mleader->object_owner_soft);
        free (mleader->material);
        free (mleader->dictionary_owner_hard);
        free (mleader->plot_style_name);
        free (mleader->color_name);
        free (mleader->block_attribute_text_string);
        free (mleader->block_attribute_id);
        free (mleader->leader_style_id);
        free (mleader->leader_linetype_id);
        free (mleader->arrowhead_id);
        free (mleader->text_style_id);
        free (mleader->block_content_id);
        free (mleader->arrow_head_id);
        free (mleader);
        mleader = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c MLEADER entities and all their data fields.
 */
void
dxf_mleader_free_list
(
        DxfMLeader *mleaders
                /*!< a pointer to the single linked list of DXF
                 * \c MLEADER entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (mleaders == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (mleaders != NULL)
        {
                DxfMLeader *iter = (DxfMLeader *) mleaders->next;
                dxf_mleader_free (mleaders);
                mleaders = (DxfMLeader *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c MLEADER entity.
 *
 * \return \c id_code.
 */
int
dxf_mleader_get_id_code
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleader->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_id_code
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int id_code
                /*!< the \c id_code to be set for the entity.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
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
        mleader->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c linetype from a DXF \c MLEADER entity.
 *
 * \return \c linetype when successful, \c NULL when an error occurred.
 */
char *
dxf_mleader_get_linetype
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleader->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_linetype
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
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
        mleader->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c layer from a DXF \c MLEADER entity.
 *
 * \return \c layer when successful, \c NULL when an error occurred.
 */
char *
dxf_mleader_get_layer
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleader->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_layer
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
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
        mleader->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c elevation from a DXF \c MLEADER entity.
 *
 * \return \c elevation.
 */
double
dxf_mleader_get_elevation
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_elevation
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c thickness from a DXF \c MLEADER entity.
 *
 * \return \c thickness.
 */
double
dxf_mleader_get_thickness
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleader->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_thickness
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mleader->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c MLEADER entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_mleader_get_linetype_scale
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleader->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_linetype_scale
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mleader->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c visibility from a DXF \c MLEADER entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_mleader_get_visibility
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleader->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleader->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_visibility
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mleader->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c color from a DXF \c MLEADER entity.
 *
 * \return color.
 */
int
dxf_mleader_get_color
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleader->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->color);
}


/*!
 * \brief Set the \c color for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_color
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
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
        mleader->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c MLEADER entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_mleader_get_paperspace
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleader->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleader->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_paperspace
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mleader->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c MLEADER
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_mleader_get_graphics_data_size
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleader->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleader->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_graphics_data_size
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        mleader->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c MLEADER entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_mleader_get_shadow_mode
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleader->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleader->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_shadow_mode
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mleader->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c MLEADER entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_mleader_get_binary_graphics_data
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleader->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) mleader->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_binary_graphics_data
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c MLEADER entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mleader_get_dictionary_owner_soft
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleader->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_dictionary_owner_soft
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
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
        mleader->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c MLEADER entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mleader_get_object_owner_soft
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleader->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_object_owner_soft
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_mleader_get_material
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleader->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_material
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (material == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c MLEADER entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mleader_get_dictionary_owner_hard
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleader->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_dictionary_owner_hard
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
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
        mleader->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c lineweight from a DXF \c MLEADER entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_mleader_get_lineweight
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_lineweight
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c MLEADER entity.
 *
 * \return a pointer to \c plot_style_name when successful, or \c NULL
 * when an error occurred.
 */
char *
dxf_mleader_get_plot_style_name
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleader->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_plot_style_name
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (plot_style_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c color_value from a DXF \c MLEADER entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_mleader_get_color_value
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_color_value
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c color_name from a DXF \c MLEADER entity.
 *
 * \return \c color_name when successful, or \c NULL when an error
 * occurred.
 */
char *
dxf_mleader_get_color_name
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleader->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_color_name
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c transparency from a DXF \c MLEADER entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_mleader_get_transparency
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_transparency
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c block_content_scale of a DXF \c MLEADER entity.
 *
 * \return the \c block_content_scale.
 */
double
dxf_mleader_get_block_content_scale
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->block_content_scale);
}


/*!
 * \brief Set the  \c block_content_scale of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_block_content_scale
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double block_content_scale
                /*!< the \c block_content_scale of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->block_content_scale = block_content_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c dogleg_length of a DXF \c MLEADER entity.
 *
 * \return the \c dogleg_length.
 */
double
dxf_mleader_get_dogleg_length
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->dogleg_length);
}


/*!
 * \brief Set the  \c dogleg_length of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_dogleg_length
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double dogleg_length
                /*!< the \c dogleg_length of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->dogleg_length = dogleg_length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c arrowhead_size of a DXF \c MLEADER entity.
 *
 * \return the \c arrowhead_size.
 */
double
dxf_mleader_get_arrowhead_size
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->arrowhead_size);
}


/*!
 * \brief Set the  \c arrowhead_size of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_arrowhead_size
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double arrowhead_size
                /*!< the \c arrowhead_size of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->arrowhead_size = arrowhead_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c block_content_rotation of a DXF \c MLEADER entity.
 *
 * \return the \c block_content_rotation.
 */
double
dxf_mleader_get_block_content_rotation
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->block_content_rotation);
}


/*!
 * \brief Set the  \c block_content_rotation of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_block_content_rotation
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double block_content_rotation
                /*!< the \c block_content_rotation of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->block_content_rotation = block_content_rotation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c block_attribute_width of a DXF \c MLEADER entity.
 *
 * \return the \c block_attribute_width.
 */
double
dxf_mleader_get_block_attribute_width
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->block_attribute_width);
}


/*!
 * \brief Set the  \c block_attribute_width of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_block_attribute_width
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double block_attribute_width
                /*!< the \c block_attribute_width of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->block_attribute_width = block_attribute_width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c property_override_flag from a DXF \c MLEADER entity.
 *
 * \return \c property_override_flag.
 */
int32_t
dxf_mleader_get_property_override_flag
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->property_override_flag);
}


/*!
 * \brief Set the \c property_override_flag for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_property_override_flag
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int32_t property_override_flag
                /*!< the \c property_override_flag to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->property_override_flag = property_override_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c leader_line_color from a DXF \c MLEADER entity.
 *
 * \return \c leader_line_color.
 */
int32_t
dxf_mleader_get_leader_line_color
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->leader_line_color);
}


/*!
 * \brief Set the \c leader_line_color for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_leader_line_color
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int32_t leader_line_color
                /*!< the \c leader_line_color to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->leader_line_color = leader_line_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c text_color from a DXF \c MLEADER entity.
 *
 * \return \c text_color.
 */
int32_t
dxf_mleader_get_text_color
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->text_color);
}


/*!
 * \brief Set the \c text_color for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_text_color
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int32_t text_color
                /*!< the \c text_color to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->text_color = text_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c block_content_color from a DXF \c MLEADER entity.
 *
 * \return \c block_content_color.
 */
int32_t
dxf_mleader_get_block_content_color
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->block_content_color);
}


/*!
 * \brief Set the \c block_content_color for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_block_content_color
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int32_t block_content_color
                /*!< the \c block_content_color to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->block_content_color = block_content_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c arrowhead_index from a DXF \c MLEADER entity.
 *
 * \return \c arrowhead_index.
 */
int32_t
dxf_mleader_get_arrowhead_index
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->arrowhead_index);
}


/*!
 * \brief Set the \c arrowhead_index for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_arrowhead_index
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int32_t arrowhead_index
                /*!< the \c arrowhead_index to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->arrowhead_index = arrowhead_index;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c text_right_attachment_type from a DXF \c MLEADER
 * entity.
 *
 * \return \c text_right_attachment_type.
 */
int32_t
dxf_mleader_get_text_right_attachment_type
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->text_right_attachment_type);
}


/*!
 * \brief Set the \c text_right_attachment_type for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_text_right_attachment_type
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int32_t text_right_attachment_type
                /*!< the \c text_right_attachment_type to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->text_right_attachment_type = text_right_attachment_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c leader_linetype_style from a DXF \c MLEADER entity.
 *
 * \return \c leader_linetype_style.
 */
int16_t
dxf_mleader_get_leader_linetype_style
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->leader_linetype_style);
}


/*!
 * \brief Set the \c leader_linetype_style for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_leader_linetype_style
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t leader_linetype_style
                /*!< the \c leader_linetype_style to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->leader_linetype_style = leader_linetype_style;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c leader_line_weight from a DXF \c MLEADER entity.
 *
 * \return \c leader_line_weight.
 */
int16_t
dxf_mleader_get_leader_line_weight
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->leader_line_weight);
}


/*!
 * \brief Set the \c leader_line_weight for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_leader_line_weight
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t leader_line_weight
                /*!< the \c leader_line_weight to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->leader_line_weight = leader_line_weight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c content_type from a DXF \c MLEADER entity.
 *
 * \return \c content_type.
 */
int16_t
dxf_mleader_get_content_type
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->content_type);
}


/*!
 * \brief Set the \c content_type for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_content_type
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t content_type
                /*!< the \c content_type to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->content_type = content_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c text_left_attachment_type from a DXF \c MLEADER
 * entity.
 *
 * \return \c text_left_attachment_type.
 */
int16_t
dxf_mleader_get_text_left_attachment_type
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->text_left_attachment_type);
}


/*!
 * \brief Set the \c text_left_attachment_type for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_text_left_attachment_type
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t text_left_attachment_type
                /*!< the \c text_left_attachment_type to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->text_left_attachment_type = text_left_attachment_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/* EOF*/
