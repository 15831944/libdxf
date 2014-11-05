/*!
 * \file object.h
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF object entity functions.
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


#ifndef LIBDXF_SRC_OBJECT_H
#define LIBDXF_SRC_OBJECT_H


#include "global.h"
#include "param.h"


/*!
 * \brief DXF definition of an object.
 */
typedef struct
dxf_object
{
        DxfEntityType entity_type;
                /*!< dxf entity type. */
        DxfParam parameter[DXF_MAX_PARAM];
                /*!< corresponding values stored in here. */
        struct DxfObject *next;
                /*!< pointer to the next DxfObject.\n
                 * \c NULL in the last DxfObject. */
} DxfObject;


DxfObject *dxf_object_new ();
int
dxf_object_write_objects
(
        DxfFile *fp,
        DxfObject *dxf_objects_list
);
int
dxf_object_free
(
        DxfObject *dxf_object
);
DxfObject *
dxf_object_init
(
        DxfObject *dxf_object
);


#endif /* LIBDXF_SRC_OBJECT_H */


/* EOF */
