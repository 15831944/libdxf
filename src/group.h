/*!
 * \file group.h
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF group object (\c GROUP).
 *
 * \version The \c GROUP object was introduced in DXF R13.
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


#ifndef LIBDXF_SRC_GROUP_H
#define LIBDXF_SRC_GROUP_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD group object (\c GROUP).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_group
{
        /* Members common for all DXF group objects. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        /* Specific members for a DXF group. */
        int unnamed_flag;
                /*!< "Unnamed" flag.\n
                 * <ol>
                 * <li value = "0"> named.</li>
                 * <li value = "1"> unnamed.</li>
                 * </ol>
                 * Group code = 70.
                 */
        int selectability_flag;
                /*!< Selectability flag.\n
                 * <ol>
                 * <li value = "0"> not selectable.</li>
                 * <li value = "1"> selectable.</li>
                 * </ol>
                 * Group code = 71. */
        char *description;
                /*!< Group description.\n
                 * Group code = 300. */
        char *handle_entity_in_group;
                /*!< Handle of entity in group (one entry per object).\n
                 * Group code = 340. */
        struct DxfGroup *next;
                /*!< Pointer to the next DxfGroup.\n
                 * \c NULL in the last DxfGroup. */
} DxfGroup;


DxfGroup *
dxf_group_new ();


#endif /* LIBDXF_SRC_GROUP_H */


/* EOF */
