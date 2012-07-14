/*!
 * \file entities.c
 *
 * \author Copyright (C) 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF entities section (/c ENTITIES).
 *
 * This section presents the group codes that apply to graphical
 * objects.\n
 * These codes are found in the ENTITIES section of a DXF file and are
 * used by AutoLISP and ARX applications in entity definition lists.\n
 * \n
 * The group codes shown in this section can apply to DXF files,
 * applications (AutoLISP or ARX), or both.\n
 * When the description of a code is different for applications and DXF
 * files (or only applies to one or the other), the description is
 * preceeded by the following indicators:\n
 * \n
 * APP      Application-specific description.\n
 * \n
 * DXF      DXF file-specific description.\n
 * \n
 * If the description is common to both DXF files and applications, no
 * indicator is provided.\n
 * Otherwise, the appropriate indicator is present.\n
 * \n
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
 * For more details see http://www.autodesk.com.\n\n
 * <hr>
 */


#include "entities.h"


/*!
 * \brief Read and parse the \c ENTITIES table from a DXF file.
 */
int
dxf_entities_read_table
(
        char *filename,
                /*!< filename of input file (or device). */
        FILE *fp,
                /*!< filepointer to the input file (or device). */
        int line_number,
                /*!< current line number in the input file (or device). */
        char *dxf_entities_list, 
                /*!< pointer to a list of entities. */
        int acad_version_number
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_read_entities () function.\n",
                __FILE__, __LINE__);
#endif
        /*! \todo Add code here. */
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_read_entities () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a DXF \c ENTITIES table.
 */
int
dxf_entities_write_table
(
        char *dxf_entities_list, 
        int acad_version_number
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_entities () function.\n",
                __FILE__, __LINE__);
#endif
        /*! \todo Add code here. */
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_entities () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
