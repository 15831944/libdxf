/*!
 * \file polyline.h
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Header file for a DXF polyline entity (\c PLINE).
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


#ifndef _POLYLINE_H
#define _POLYLINE_H


#include "global.h"
#include "entity.h"


/*!
 * \brief Definition of a DXF polyline entity.
 *
 * A polyface mesh is represented in \c DXF as a variant of a Polyline
 * entity.\n
 * The Polyline header is identified as introducing a polyface mesh by the
 * presence of the 64 bit in the Polyline flags (70) group.\n
 * The 71 group specifies the number of vertices in the mesh, and the 72
 * group, the number of faces.\n
 * While these counts are correct for all meshes created with the \c PFACE
 * command, applications are not required to place correct values in these
 * fields, and AutoCAD actually never relies upon their accuracy.\n
 * \n
 * Following the Polyline header is a sequence of Vertex entities that
 * specify the vertex coordinates and faces that compose the mesh.\n
 * Vertices such as these are described in the following subsection on
 * Vertex.\n
 * \n
 * Applications might want to represent polygons with an arbitrarily large
 * number of sides in polyface meshes.\n
 * However, the AutoCAD entity structure imposes a limit on the number of
 * vertices that a given face entity can specify.\n
 * You can represent more complex polygons by decomposing them into
 * triangular wedges.\n
 * Their edges should be made invisible to prevent visible artifacts of this
 * subdivision from being drawn.\n
 * The \c PFACE command performs this subdivision automatically, but when
 * applications generate polyface meshes directly, the applications must do
 * this themselves.\n
 * \n
 * The number of vertices per face is the key parameter in this subdivision
 * process.\n
 * The \c PFACEVMAX system variable provides an application with the number
 * of vertices per face entity.\n
 * This value is read-only, and is set to 4.\n
 * \n
 * Polyface meshes created with the \c PFACE command are always generated
 * with all the vertex coordinate entities first, followed by the face
 * definition entities.\n
 * The code within AutoCAD that processes polyface meshes does not, at
 * present, require this ordering; it works even with interleaved vertex
 * coordinates and face definitions as long as no face specifies a vertex
 * with an index that appears after it in the database.\n
 * Programs that read polyface meshes from \c DXF would be wise to be as
 * tolerant of odd vertex and face ordering as AutoCAD is.\n
 */
typedef struct
dxf_polyline
{
        DxfEntity common;
                /*!< common properties for DXF entities. */
        double x0;
                /*!< group code = 10\n
                 * defaults to 0.0. */
        double y0;
                /*!< group code = 20\n
                 * defaults to 0.0. */
        double z0;
                /*!< group code = 30\n
                 * default elevation for vertices. */
        double start_width;
                /*!< group code = 40\n
                 * optional, defaults to 0.0\n
                 * the default widths apply to any vertex that doesn't supply
                 * widths.\n */
        double end_width;
                /*!< group code = 41\n
                 * optional, defaults to 0.0\n
                 * the default widths apply to any vertex that doesn't supply
                 * widths.\n */
        int vertices_follow;
                /*!< group code = 66\n
                 * always 1\n
                 * The "vertices follow" flag is always 1, indicating that a
                 * series of Vertex entities is expected to follow the
                 * \c Polyline, terminated by a "sequence end" entity. */
        int flag;
                /*!< group code = 70\n
                 * optional, defaults to 0\n
                 * bit coded:\n
                 * 1 = This is a closed Polyline (or a polygon mesh closed in
                 * the M direction)\n
                 * 2 = Curve-fit vertices have been added\n
                 * 4 = Spline-fit vertices have been added\n
                 * 8 = This is a 3D Polyline\n
                 * 16 = This is a 3D polygon mesh\n
                 * 32 = The polygon mesh is closed in the N direction\n
                 * 64 = This Polyline is a polyface mesh\n
                 * 128 = The linetype pattern is generated continuously
                 *       around the vertices of this Polyline\n. */
        int polygon_mesh_M_vertex_count;
                /*!< group code = 71\n
                 * optional, defaults to 0. */
        int polygon_mesh_N_vertex_count;
                /*!< group code = 72\n
                 * optional, defaults to 0. */
        int smooth_M_surface_density;
                /*!< group code = 73\n
                 * optional, defaults to 0. */
        int smooth_N_surface_density;
                /*!< group code = 74\n
                 * optional, defaults to 0. */
        int surface_type;
                /*!< group code = 75\n
                 * optional, defaults to 0\n
                 * bit coded:\n
                 * 0 = no smooth surface fitted\n
                 * 5 = quadratic B-spline surface\n
                 * 6 = cubic B-spline surface\n
                 * 8 = Bezier surface. */
        double extr_x0;
                /*!< group code = 210\n
                 * Extrusion direction (optional; default = 0, 0, 1)\n
                 * DXF: X value;\n
                 * APP: 3D vector\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
        double extr_y0;
                /*!< group code = 220
                 * DXF: Y value of extrusion direction (optional). */
        double extr_z0;
                /*!< group code = 230
                 * DXF: Z value of extrusion direction (optional). */
} DxfPolyline, * DxfPolylinePtr;


DxfPolyline *
dxf_polyline_new ();
DxfPolyline *
dxf_polyline_init
(
        DxfPolyline *dxf_polyline
);
int
dxf_polyline_read
(
        char *filename,
        FILE *fp,
        int *line_number,
        DxfPolyline *dxf_polyline,
        int acad_version_number
);
int
dxf_polyline_write_lowlevel
(
        FILE *fp,
        int id_code,
        char *linetype,
        char *layer,
        double x0,
        double y0,
        double z0,
        double thickness,
        double start_width,
        double end_width,
        int color,
        int vertices_follow,
        int paperspace,
        int flag,
        int polygon_mesh_M_vertex_count,
        int polygon_mesh_N_vertex_count,
        int smooth_M_surface_density,
        int smooth_N_surface_density,
        int surface_type
);
int
dxf_polyline_write
(
        FILE *fp,
        DxfPolyline dxf_polyline
);


#endif /* _POLYLINE_H */


/* EOF */
