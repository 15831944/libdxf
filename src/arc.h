/*!
 * \file arc.h
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF arc entity (\c ARC).
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


#ifndef LIBDXF_SRC_ARC_H
#define LIBDXF_SRC_ARC_H


#include "global.h"
#include "point.h"


/*!
 * \brief DXF definition of an AutoCAD arc entity (\c ARC).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_arc
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *linetype;
                /*!< The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Group code = 6. */
        char *layer;
                /*!< Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given.\n
                 * Group code = 8. */
        double elevation;
                /*!< Elevation of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default).\n
                 * Group code = 38. */
        double thickness;
                /*!< Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double linetype_scale;
                /*!< Linetype scale (optional).\n
                 * Group code = 48. */
        int16_t visibility;
                /*!< Object visibility (optional):\n
                 * <ol>
                 * <li value = "0"> Visible</li>
                 * <li value = "1"> Invisible</li>
                 * </ol>
                 * Group code = 60. */
        int color;
                /*!< Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity.\n
                 * Group code = 62. */
        int paperspace;
                /*!< Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0).\n
                 * Group code = 67. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        /* Specific members for a DXF arc. */
        double x0;
                /*!< X-value of the starting point coordinate.\n
                 * Group code = 10. */
        double y0;
                /*!< Y-value of the starting point coordinate.\n
                 * Group code = 20. */
        double z0;
                /*!< Z-value of the starting point coordinate.\n
                 * Group code = 30. */
        double radius;
                /*!< Radius of the arc.\n
                 * Group code = 40. */
        double start_angle;
                /*!< Start angle of the arc.\n
                 * Group code = 50. */
        double end_angle;
                /*!< End angle of the arc.\n
                 * Group code = 51. */
        double extr_x0;
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if omitted in the DXF file.\n
                 * Group code = 230. */
        struct DxfArc *next;
                /*!< Pointer to the next DxfArc.\n
                 * \c NULL in the last DxfArc. */
} DxfArc;


DxfArc *
dxf_arc_new ();
DxfArc *
dxf_arc_init
(
        DxfArc *arc
);
DxfArc *
dxf_arc_read
(
        DxfFile *fp,
        DxfArc *arc
);
int dxf_arc_write
(
        DxfFile *fp,
        DxfArc *arc
);
int dxf_arc_free
(
        DxfArc *arc
);
void
dxf_arc_free_chain
(
        DxfArc *arcs
);
int
dxf_arc_get_id_code
(
        DxfArc *arc
);
DxfArc *
dxf_arc_set_id_code
(
        DxfArc *arc,
        int id_code
);
char *
dxf_arc_get_linetype
(
        DxfArc *arc
);
DxfArc *
dxf_arc_set_linetype
(
        DxfArc *arc,
        char *linetype
);
char *
dxf_arc_get_layer
(
        DxfArc *arc
);
DxfArc *
dxf_arc_set_layer
(
        DxfArc *arc,
        char *layer
);
double
dxf_arc_get_elevation
(
        DxfArc *arc
);
DxfArc *
dxf_arc_set_elevation
(
        DxfArc *arc,
        double elevation
);
double
dxf_arc_get_thickness
(
        DxfArc *arc
);
DxfArc *
dxf_arc_set_thickness
(
        DxfArc *arc,
        double thickness
);
double
dxf_arc_get_linetype_scale
(
        DxfArc *arc
);
DxfArc *
dxf_arc_set_linetype_scale
(
        DxfArc *arc,
        double linetype_scale
);
int16_t
dxf_arc_get_visibility
(
        DxfArc *arc
);
DxfArc *
dxf_arc_set_visibility
(
        DxfArc *arc,
        int16_t visibility
);
int
dxf_arc_get_color
(
        DxfArc *arc
);
DxfArc *
dxf_arc_set_color
(
        DxfArc *arc,
        int color
);
int
dxf_arc_get_paperspace
(
        DxfArc *arc
);
DxfArc *
dxf_arc_set_paperspace
(
        DxfArc *arc,
        int paperspace
);
char *
dxf_arc_get_dictionary_owner_soft
(
        DxfArc *arc
);
DxfArc *
dxf_arc_set_dictionary_owner_soft
(
        DxfArc *arc,
        char *dictionary_owner_soft
);
char *
dxf_arc_get_dictionary_owner_hard
(
        DxfArc *arc
);
DxfArc *
dxf_arc_set_dictionary_owner_hard
(
        DxfArc *arc,
        char *dictionary_owner_hard
);
DxfPoint *
dxf_arc_get_start_point
(
        DxfArc *arc,
        int id_code,
        int inheritance
);
DxfArc *
dxf_arc_set_start_point
(
        DxfArc *arc,
        DxfPoint *point
);
DxfPoint *
dxf_arc_get_extrusion_vector_as_point
(
        DxfArc *arc
);
DxfArc *
dxf_arc_set_extrusion_vector
(
        DxfArc *arc,
        double extr_x0,
        double extr_y0,
        double extr_z0
);
double
dxf_arc_get_radius
(
        DxfArc *arc
);
DxfArc *
dxf_arc_set_radius
(
        DxfArc *arc,
        double radius
);
double
dxf_arc_get_start_angle
(
        DxfArc *arc
);
DxfArc *
dxf_arc_set_start_angle
(
        DxfArc *arc,
        double start_angle
);
double
dxf_arc_get_end_angle
(
        DxfArc *arc
);
DxfArc *
dxf_arc_set_end_angle
(
        DxfArc *arc,
        double end_angle
);
struct DxfArc *
dxf_arc_get_next
(
        DxfArc *arc
);


#endif /* LIBDXF_SRC_ARC_H */


/* EOF */
