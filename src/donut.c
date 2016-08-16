/*!
 * \file donut.c
 * 
 * \author Copyright (C) 2008 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * 
 * \brief Functions for a libDXF donut entity.
 *
 * \warning This is not an official AutoCAD entity.
 *
 * \c donut is an AutoCAD command that generates a polyline (\c POLYLINE)
 * consisting of two vertices (\c VERTEX) and an end of sequence marker
 * (\c SEQEND).
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


#include "donut.h"


/*!
 * \brief Allocate memory for a libDXF donut.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfDonut *
dxf_donut_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfDonut *donut = NULL;
        size_t size;

        size = sizeof (DxfDonut);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((donut = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfDonut struct.\n")),
                  __FUNCTION__);
                donut = NULL;
        }
        else
        {
                memset (donut, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Allocate memory and initialize data fields in a libDXF donut
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfDonut *
dxf_donut_init
(
        DxfDonut *donut
                /*!< libDXF donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                donut = dxf_donut_new ();
        }
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfDonut struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Members common for all DXF drawable entities. */
        donut->id_code = 0;
        donut->linetype = strdup (DXF_DEFAULT_LINETYPE);
        donut->layer = strdup (DXF_DEFAULT_LAYER);
        donut->elevation = 0.0;
        donut->thickness = 0.0;
        donut->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        donut->visibility = DXF_DEFAULT_VISIBILITY;
        donut->color = DXF_COLOR_BYLAYER;
        donut->paperspace = DXF_MODELSPACE;
        donut->dictionary_owner_soft = strdup ("");
        donut->dictionary_owner_hard = strdup ("");
        /* Specific members for a libDXF donut. */
        donut->p0->x0 = 0.0;
        donut->p0->y0 = 0.0;
        donut->p0->z0 = 0.0;
        donut->outside_diameter = 0.0;
        donut->inside_diameter = 0.0;
        donut->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Write DXF output to a file for a libDXF donut.
 *
 * A typical convenience function.\n
 * Draw a donut by means of two bulged vertices into a single polyline.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_donut_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfDonut *donut
                /*!< Pointer to a donut struct. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPolyline *polyline = NULL;
        DxfVertex *vertex_1 = NULL;
        DxfVertex *vertex_2 = NULL;
        DxfSeqend *seqend = NULL;
        char *dxf_entity_name = strdup ("POLYLINE");
        double start_width;
        double end_width;
        int id_code = -1;

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
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (donut->outside_diameter > donut->inside_diameter)
        {
                fprintf (stderr,
                  (_("Error in %s () outside diameter is smaller than the inside diameter for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, id_code);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        start_width = 0.5 * (donut->outside_diameter - donut->inside_diameter);
        end_width = 0.5 * (donut->outside_diameter - donut->inside_diameter);
        if (strcmp (donut->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, donut->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                donut->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (donut->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                donut->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Create and write a polyline primitive. */
        dxf_polyline_new (polyline);
        polyline = dxf_polyline_init (polyline);
        id_code = fp->last_id_code;
        id_code++;
        polyline->id_code = id_code;
        polyline->linetype = donut->linetype;
        polyline->layer = donut->layer;
        polyline->x0 = donut->p0->x0;
        polyline->y0 = donut->p0->y0;
        polyline->z0 = donut->p0->z0;
        polyline->thickness = donut->thickness;
        polyline->start_width = 0.5 * start_width;
        polyline->end_width = 0.5 * end_width;
        polyline->color = donut->color;
        polyline->vertices_follow = 1;
        polyline->paperspace = donut->paperspace;
        polyline->flag = 1;
        polyline->polygon_mesh_M_vertex_count = 0;
        polyline->polygon_mesh_N_vertex_count = 0;
        polyline->smooth_M_surface_density = 0;
        polyline->smooth_N_surface_density = 0;
        polyline->surface_type = 0;
        dxf_polyline_write (fp, polyline);
        /*! \todo Hook up this polyline to the list of polylines. */
        /* Create and write the first vertex. */
        vertex_1 = dxf_vertex_new ();
        vertex_1 = dxf_vertex_init (vertex_1);
        id_code = fp->last_id_code;
        id_code++;
        vertex_1->id_code = id_code;
        vertex_1->layer = donut->layer;
        vertex_1->linetype = donut->linetype;
        vertex_1->x0 = donut->p0->x0 - (0.25 * (donut->outside_diameter + donut->inside_diameter));
        vertex_1->y0 = donut->p0->y0;
        vertex_1->z0 = donut->p0->z0;
        vertex_1->thickness = donut->thickness;
        vertex_1->start_width = 0.5 * start_width;
        vertex_1->end_width = 0.5 * end_width;
        vertex_1->bulge = 1;
        vertex_1->curve_fit_tangent_direction = 0.0;
        vertex_1->color = donut->color;
        vertex_1->paperspace = donut->paperspace;
        vertex_1->flag = 0;
        dxf_vertex_write (fp, vertex_1);
        /*! \todo Hook up this vertex to the list of vertices. */
        /* Create and write the second vertex. */
        vertex_2 = dxf_vertex_new ();
        vertex_2 = dxf_vertex_init (vertex_2);
        id_code = fp->last_id_code;
        id_code++;
        vertex_2->id_code = id_code;
        vertex_2->layer = donut->layer;
        vertex_2->linetype = donut->linetype;
        vertex_2->x0 = donut->p0->x0 + (0.25 * (donut->outside_diameter + donut->inside_diameter));
        vertex_2->y0 = donut->p0->y0;
        vertex_2->z0 = donut->p0->z0;
        vertex_2->thickness = donut->thickness;
        vertex_2->start_width = 0.5 * start_width;
        vertex_2->end_width = 0.5 * end_width;
        vertex_2->bulge = 1;
        vertex_2->curve_fit_tangent_direction = 0.0;
        vertex_2->color = donut->color;
        vertex_2->paperspace = donut->paperspace;
        vertex_2->flag = 0;
        dxf_vertex_write (fp, vertex_2);
        /*! \todo Hook up this vertex to the list of vertices. */
        /* Create and write the end of sequence marker. */
        dxf_seqend_new (seqend);
        seqend = dxf_seqend_init (seqend);
        id_code = fp->last_id_code;
        id_code++;
        seqend->id_code = id_code;
        seqend->layer = donut->layer;
        seqend->linetype = donut->linetype;
        dxf_seqend_write (fp, seqend);
        /*! \todo Hook up this seqend to the list of seqends. */
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a libDXF donut and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_donut_free
(
        DxfDonut *donut
                /*!< Pointer to the memory occupied by the libDXF donut
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (donut->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfDonut was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (donut->linetype);
        free (donut->layer);
        free (donut->dictionary_owner_soft);
        free (donut->dictionary_owner_hard);
        free (donut);
        donut = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF donut entities
 * and all their data fields.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
void
dxf_donut_free_chain
(
        DxfDonut *donuts
                /*!< pointer to the chain of DXF donut entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (donuts == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (donuts != NULL)
        {
                struct DxfDonut *iter = donuts->next;
                dxf_donut_free (donuts);
                donuts = (DxfDonut *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a libDXF \c donut entity.
 *
 * \return \c id_code.
 */
int
dxf_donut_get_id_code
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (donut->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut->id_code);
}


/*!
 * \brief Set the \c id_code for a libDXF \c donut entity.
 *
 * \return a pointer to \c donut when sucessful, \c NULL when an error
 * occurred.
 */
DxfDonut *
dxf_donut_set_id_code
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
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
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative id-code value was passed.\n")),
                  __FUNCTION__);
        }
        donut->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the linetype from a libDXF \c donut entity.
 *
 * \return a pointer to \c linetype when sucessful, \c NULL when an
 * error occurred.
 */
char *
dxf_donut_get_linetype
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (donut->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (donut->linetype));
}


/*!
 * \brief Set the \c linetype for a libDXF \c donut entity.
 *
 * \return a pointer to \c donut when sucessful, \c NULL when an error
 * occurred.
 *
 * \warning The passed \c linetype variable is not freed by this
 * function.
 */
DxfDonut *
dxf_donut_set_linetype
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
        char *linetype
                /*!< a string containing the \c linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
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
        donut->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the \c layer from a libDXF \c donut entity.
 *
 * \return a pointer to \c layer when sucessful, \c NULL when an error
 * occurred.
 */
char *
dxf_donut_get_layer
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (donut->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (donut->layer));
}


/*!
 * \brief Set the \c layer for a libDXF \c donut entity.
 *
 * \return a pointer to \c donut when sucessful, \c NULL when an error
 * occurred.
 *
 * \warning The passed \c layer variable is not freed by this function.
 */
DxfDonut *
dxf_donut_set_layer
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
        char *layer
                /*!< a string containing the \c layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
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
        donut->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the \c elevation a this libDXF \c donut entity.
 *
 * \return \c elevation.
 */
double
dxf_donut_get_elevation
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut->elevation);
}


/*!
 * \brief Set the \c elevation for a libDXF \c donut entity.
 *
 * \return a pointer to \c donut when sucessful, \c NULL when an error
 * occurred.
 */
DxfDonut *
dxf_donut_set_elevation
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        donut->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the \c thickness from a libDXF \c donut entity.
 *
 * \return \c thickness.
 */
double
dxf_donut_get_thickness
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (donut->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the thickness member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut->thickness);
}


/*!
 * \brief Set the \c thickness for a libDXF \c donut entity.
 *
 * \return a pointer to \c donut when sucessful, \c NULL when an error
 * occurred.
 */
DxfDonut *
dxf_donut_set_thickness
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative thickness value was passed.\n")),
                  __FUNCTION__);
        }
        donut->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the \c linetype_scale from a libDXF \c donut entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_donut_get_linetype_scale
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (donut->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the linetype_scale member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a libDXF \c donut entity.
 *
 * \return a pointer to \c donut when sucessful, \c NULL when an error
 * occurred.
 */
DxfDonut *
dxf_donut_set_linetype_scale
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative linetype_scale value was passed.\n")),
                  __FUNCTION__);
        }
        donut->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the \c visibility from a libDXF \c donut entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_donut_get_visibility
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (donut->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (donut->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut->visibility);
}


/*!
 * \brief Set the \c visibility for a libDXF \c donut entity.
 *
 * \return a pointer to \c donut when sucessful, \c NULL when an error
 * occurred.
 */
DxfDonut *
dxf_donut_set_visibility
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
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
        donut->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the \c color from a libDXF \c donut entity.
 *
 * \return \c color.
 */
int
dxf_donut_get_color
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (donut->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the color member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut->color);
}


/*!
 * \brief Set the \c color for a libDXF \c donut entity.
 *
 * \return a pointer to \c donut when sucessful, \c NULL when an error
 * occurred.
 */
DxfDonut *
dxf_donut_set_color
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
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
        donut->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the \c paperspace flag value from a libDXF \c donut
 * entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_donut_get_paperspace
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (donut->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        if (donut->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a libDXF \c donut entity.
 *
 * \return a pointer to \c donut when sucessful, \c NULL when an error
 * occurred.
 */
DxfDonut *
dxf_donut_set_paperspace
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
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
        donut->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the \c graphics_data_size value from a libDXF \c donut
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_donut_get_graphics_data_size
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (donut->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
        if (donut->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a libDXF \c donut entity.
 *
 * \return a pointer to \c donut when successful, or \c NULL when an
 * error occurred.
 */
DxfDonut *
dxf_donut_set_graphics_data_size
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
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
        donut->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the \c shadow_mode from a libDXF \c donut entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_donut_get_shadow_mode
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (donut->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the shadow_mode member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (donut->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the shadow_mode member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut->shadow_mode);
}


/*!
 * \brief Get the soft pointer to the \c dictionary_owner_soft from a
 * libDXF \c donut entity.
 *
 * \return a pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_donut_get_dictionary_owner_soft
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (donut->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (donut->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a libDXF
 * \c donut entity.
 */
DxfDonut *
dxf_donut_set_dictionary_owner_soft
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * \c dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
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
        donut->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a libDXF 
 * \c donut entity.
 *
 * \return a pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_donut_get_dictionary_owner_hard
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (donut->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_hard member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (donut->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a libDXF
 * \c donut entity.
 *
 * \return a pointer to \c donut when sucessful, \c NULL when an error
 * occurred.
 */
DxfDonut *
dxf_donut_set_dictionary_owner_hard
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
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
        donut->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the insertion point of a libDXF \c donut entity.
 *
 * \return the insertion point \c p0.
 */
DxfPoint *
dxf_donut_get_p0
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (donut->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut->p0);
}


/*!
 * \brief Set the insertion point \c p0 of a libDXF \c donut entity.
 *
 * \return a pointer to \c donut when successful, or \c NULL when an
 * error occurred.
 */
DxfDonut *
dxf_donut_set_p0
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
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
        donut->p0 = (DxfPoint *) p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the X-value of the insertion point \c x0 of a libDXF
 * \c donut entity.
 *
 * \return the X-value of the insertion point \c x0.
 */
double
dxf_donut_get_x0
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (donut->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut->p0->x0);
}


/*!
 * \brief Set the X-value of the insertion point \c x0 of a libDXF
 * \c donut entity.
 *
 * \return a pointer to \c donut when successful, or \c NULL when an
 * error occurred.
 */
DxfDonut *
dxf_donut_set_x0
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
        double x0
                /*!< the X-value of the insertion point \c x0 of a
                 * libDXF \c donut entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (donut->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        donut->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the Y-value of the insertion point \c y0 of a libDXF
 * \c donut entity.
 *
 * \return the Y-value of the insertion point \c y0.
 */
double
dxf_donut_get_y0
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (donut->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut->p0->y0);
}


/*!
 * \brief Set the Y-value of the insertion point \c y0 of a libDXF
 * \c donut entity.
 *
 * \return a pointer to \c donut when successful, or \c NULL when an
 * error occurred.
 */
DxfDonut *
dxf_donut_set_y0
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
        double y0
                /*!< the Y-value of the insertion point \c y0 of a
                 * libDXF \c donut entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (donut->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        donut->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the Z-value of the insertion point \c z0 of a libDXF
 * \c donut entity.
 *
 * \return the Z-value of the insertion point \c z0.
 */
double
dxf_donut_get_z0
(
        DxfDonut *donut
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (donut->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut->p0->z0);
}


/*!
 * \brief Set the Z-value of the insertion point \c z0 of a libDXF
 * \c donut entity.
 *
 * \return a pointer to \c donut when successful, or \c NULL when an
 * error occurred.
 */
DxfDonut *
dxf_donut_set_z0
(
        DxfDonut *donut,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double z0
                /*!< the Z-value of the insertion point \c z0 of a libDXF
                 * \c donut entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (donut->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        donut->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the \c outside_diameter of a libDXF \c donut entity.
 *
 * \return the \c outside_diameter.
 */
double
dxf_donut_get_outside_diameter
(
        DxfDonut *donut
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut->outside_diameter);
}


/*!
 * \brief Set the \c outside_diameter of a libDXF \c donut entity.
 *
 * \return a pointer to \c donut when successful, or \c NULL when an
 * error occurred.
 */
DxfDonut *
dxf_donut_set_outside_diameter
(
        DxfDonut *donut,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double outside_diameter
                /*!< the \c outside_diameter of a libDXF \c donut
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        donut->outside_diameter = outside_diameter;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the \c inside_diameter of a libDXF \c donut entity.
 *
 * \return the \c inside_diameter.
 */
double
dxf_donut_get_inside_diameter
(
        DxfDonut *donut
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut->inside_diameter);
}


/*!
 * \brief Set the \c inside_diameter of a libDXF \c donut entity.
 *
 * \return a pointer to \c donut when successful, or \c NULL when an
 * error occurred.
 */
DxfDonut *
dxf_donut_set_inside_diameter
(
        DxfDonut *donut,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double inside_diameter
                /*!< the \c inside_diameter of a libDXF \c donut
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        donut->inside_diameter = inside_diameter;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Get the pointer to the next \c donut entity from a libDXF 
 * \c donut entity.
 *
 * \return pointer to the next \c donut entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfDonut *
dxf_donut_get_next
(
        DxfDonut *donut
                /*!< a pointer to a libDXF \c donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (donut->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDonut *) donut->next);
}


/*!
 * \brief Set the pointer to the next \c donut for a libDXF \c donut
 * entity.
 *
 * \return a pointer to \c donut when successful, or \c NULL when an
 * error occurred.
 */
DxfDonut *
dxf_donut_set_next
(
        DxfDonut *donut,
                /*!< a pointer to a libDXF \c donut entity. */
        DxfDonut *next
                /*!< a pointer to the next \c donut for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
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
        donut->next = (struct DxfDonut *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/* EOF */
