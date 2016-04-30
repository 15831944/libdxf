/*!
 * \file acad_proxy_entity.h
 *
 * \author Copyright (C) 2008 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF acad_proxy_entity entity
 * (\c ACAD_PROXY_ENTITY).
 *
 * \since The \c ACAD_ZOMBIE_ENTITY entity was introduced in DXF R13.
 *
 * \note The \c ACAD_ZOMBIE_ENTITY entity was renamed to 
 * \c ACAD_PROXY_ENTITY in DXF R14.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
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


#ifndef LIBDXF_SRC_ACAD_PROXY_ENTITY_H
#define LIBDXF_SRC_ACAD_PROXY_ENTITY_H


#include "global.h"
#include "binary_entity_data.h"
#include "binary_graphics_data.h"


/*!
 * \brief DXF definition of an AutoCAD acad_proxy_entity entity
 * (\c ACAD_PROXY_ENTITY).
 */
typedef struct
dxf_acad_proxy_entity_struct
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
                /*!< Elevation of the entity in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default).\n
                 * Group code = 38.\n
                 * \deprecated As of version R11. */
        double thickness;
                /*!< Thickness of the entity in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double linetype_scale;
                /*!< Linetype scale (optional).\n
                 * Group code = 48.\n
                 * \since Introduced in version R13. */
        int visibility;
                /*!< Object visibility (optional):\n
                 * <ol>
                 * <li value = "0"> Visible</li>
                 * <li value = "1"> Invisible</li>
                 * </ol>
                 * Group code = 60.\n
                 * \since Introduced in version R13. */
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
                 * Group code = 67.\n
                 * \since Introduced in version R13. */
        int16_t shadow_mode;
                /*!< Shadow mode:\n
                 * <ol>
                 * <li value = "0"> Casts and receives shadows.</li>
                 * <li value = "1"> Casts shadows.</li>
                 * <li value = "2"> Receives shadows.</li>
                 * <li value = "3"> Ignores shadows.</li>
                 * </ol>\n
                 * Group code = 284.\n
                 * \since Introduced in version R2009. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330.\n
                 * \since Introduced in version R14. */
        char *material;
                /*!< Hard-pointer ID/handle to material object (present if
                 * not BYLAYER).\n
                 * Group code = 347.\n
                 * \since Introduced in version R2008. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360.\n
                 * \since Introduced in version R14. */
        int16_t lineweight;
                /*!< Lineweight enum value.\n
                 * Stored and moved around as a 16-bit integer.\n
                 * Group code = 370.\n
                 * \since Introduced in version R2002. */
        char *plot_style_name;
                /*!< Hard pointer ID / handle of PlotStyleName object.\n
                 * Group code = 390.\n
                 * \since Introduced in version R2009. */
        long color_value;
                /*!< A 24-bit color value that should be dealt with in
                 * terms of bytes with values of 0 to 255.\n
                 * The lowest byte is the blue value, the middle byte is
                 * the green value, and the third byte is the red value.\n
                 * The top byte is always 0.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 420.\n
                 * \since Introduced in version R2004. */
        char *color_name;
                /*!< Color name.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 430.\n
                 * \since Introduced in version R2004. */
        long transparency;
                /*!< Transparency value.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 440.\n
                 * \since Introduced in version R2004. */
        /* Specific members for a DXF acad_proxy_entity. */
        int original_custom_object_data_format;
                /*!< Original custom object data format:\n
                 * <ol>
                 * <li value = "0"> DWG format</li>
                 * <li value = "1"> DXF format</li>
                 * </ol>
                 * Group code = 70.\n
                 * \since Introduced in version R2000. */
        int proxy_entity_class_id;
                /*!< Always 498.\n
                 * Group code = 90. */
        int application_entity_class_id;
                /*!< Class IDs are based on the order of the class in the
                 * CLASSES section.\n
                 * The first class is given the ID of 500, the next is
                 * 501, and so on.\n
                 * Group code = 91. */
        int graphics_data_size;
                /*!< Size of graphics data in bytes.\n
                 * Group code = 92.\n
                 * \since Introduced in version R14.\n
                 * \warning On some 64 bit workstations output is
                 * generated with group code "160", thus omitting group
                 * code "92". */
        int entity_data_size;
                /*!< Size of entity data in bits.\n
                 * Group code = 93. */
        ulong object_drawing_format;
                /*!< Object drawing format when it becomes a proxy
                 * (a 32-bit unsigned integer):\n
                 * Low word is AcDbDwgVersion.\n
                 * High word is MaintenanceReleaseVersion.
                 * Added in AutoCAD release 2000.\n
                 * Group code = 95. */
        DxfBinaryGraphicsData *binary_graphics_data;
                /*!< Proxy entity graphics data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310.\n
                 * \since Introduced in version R14. */
        DxfBinaryEntityData *binary_entity_data;
                /*!< Binary entity data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310.\n
                 * \since Introduced in version R14. */
        char *object_id[DXF_MAX_PARAM];
                /*!< An object ID (multiple entries can appear).\n
                 * Group code = 330 or 340 or 350 or 360. */
        struct DxfAcadProxyEntity *next;
                /*!< Pointer to the next DxfAcadProxyEntity.\n
                 * \c NULL in the last DxfAcadProxyEntity. */
} DxfAcadProxyEntity;


DxfAcadProxyEntity *
dxf_acad_proxy_entity_new ();
DxfAcadProxyEntity *
dxf_acad_proxy_entity_init
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_read
(
        DxfFile *fp,
        DxfAcadProxyEntity *acad_proxy_entity
);
int
dxf_acad_proxy_entity_write
(
        DxfFile *fp,
        DxfAcadProxyEntity *acad_proxy_entity
);
int
dxf_acad_proxy_entity_free
(
        DxfAcadProxyEntity *acad_proxy_entity
);
void
dxf_acad_proxy_entity_free_chain
(
        DxfAcadProxyEntity *acad_proxy_entities
);
int
dxf_acad_proxy_entity_get_id_code
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_id_code
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int id_code
);
char *
dxf_acad_proxy_entity_get_linetype
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_linetype
(
        DxfAcadProxyEntity *acad_proxy_entity,
        char *linetype
);
char *
dxf_acad_proxy_entity_get_layer
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_layer
(
        DxfAcadProxyEntity *acad_proxy_entity,
        char *layer
);
double
dxf_acad_proxy_entity_get_elevation
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_elevation
(
        DxfAcadProxyEntity *acad_proxy_entity,
        double elevation
);
double
dxf_acad_proxy_entity_get_thickness
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_thickness
(
        DxfAcadProxyEntity *acad_proxy_entity,
        double thickness
);
double
dxf_acad_proxy_entity_get_linetype_scale
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_linetype_scale
(
        DxfAcadProxyEntity *acad_proxy_entity,
        double linetype_scale
);
int16_t
dxf_acad_proxy_entity_get_visibility
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_visibility
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int16_t visibility
);
int
dxf_acad_proxy_entity_get_color
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_color
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int color
);
int
dxf_acad_proxy_entity_get_paperspace
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_paperspace
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int paperspace
);
int16_t
dxf_acad_proxy_entity_get_shadow_mode
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_shadow_mode
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int16_t shadow_mode
);
char *
dxf_acad_proxy_entity_get_dictionary_owner_soft
(
        DxfAcadProxyEntity *acad_proxy_entity
);
char *
dxf_acad_proxy_entity_get_material
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_dictionary_owner_soft
(
        DxfAcadProxyEntity *acad_proxy_entity,
        char *dictionary_owner_soft
);
char *
dxf_acad_proxy_entity_get_dictionary_owner_hard
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_dictionary_owner_hard
(
        DxfAcadProxyEntity *acad_proxy_entity,
        char *dictionary_owner_hard
);
int
dxf_acad_proxy_entity_get_original_custom_object_data_format
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_original_custom_object_data_format
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int original_custom_object_data_format
);
int
dxf_acad_proxy_entity_get_proxy_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_proxy_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int proxy_entity_class_id
);
int
dxf_acad_proxy_entity_get_application_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_application_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int application_entity_class_id
);
int
dxf_acad_proxy_entity_get_graphics_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_graphics_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int graphics_data_size
);
int
dxf_acad_proxy_entity_get_entity_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_entity_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int entity_data_size
);
ulong
dxf_acad_proxy_entity_get_object_drawing_format
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_get_next
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_next
(
        DxfAcadProxyEntity *acad_proxy_entity,
        DxfAcadProxyEntity *next
);


#endif /* LIBDXF_SRC_ACAD_PROXY_ENTITY_H */


/* EOF */
