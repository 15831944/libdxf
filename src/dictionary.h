/*!
 * \file dictionary.h
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF dictionary object (\c DICTIONARY).
 *
 * \version The \c DICTIONARY object was introduced in DXF R13.
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


#ifndef LIBDXF_SRC_DICTIONARY_H
#define LIBDXF_SRC_DICTIONARY_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD dictionary object (\c DICTIONARY).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_dictionary
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
        /* Specific members for a DXF dictionary. */
        char *entry_name;
                /*!< Entry name (one for each entry).\n
                 * Group code = 3. */
        char *entry_object_handle;
                /*!< Handle of entry object (one for each entry).\n
                 * Group code = 350. */
        struct DxfDictionary *next;
                /*!< Pointer to the next DxfDictionary.\n
                 * \c NULL in the last DxfDictionary. */
} DxfDictionary;


DxfDictionary *
dxf_dictionary_new ();
DxfDictionary *
dxf_dictionary_init
(
        DxfDictionary *dictionary
);
DxfDictionary *
dxf_dictionary_read
(
        DxfFile *fp,
        DxfDictionary *dictionary
);
int
dxf_dictionary_write
(
        DxfFile *fp,
        DxfDictionary *dictionary
);
int
dxf_dictionary_free
(
        DxfDictionary *dictionary
);
void
dxf_dictionary_free_chain
(
        DxfDictionary *dictionaries
);
int
dxf_dictionary_get_id_code
(
        DxfDictionary *dictionary
);
DxfDictionary *
dxf_dictionary_set_id_code
(
        DxfDictionary *dictionary,
        int id_code
);
char *
dxf_dictionary_get_dictionary_owner_soft
(
        DxfDictionary *dictionary
);


#endif /* LIBDXF_SRC_DICTIONARY_H */


/* EOF */
