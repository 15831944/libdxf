/*!
 * \file entity.c
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for DXF entities.
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
 * For more details see http://www.autodesk.com.\n\n
 * <hr>
 */


#include "global.h"


/*!
 * \brief Prints warning on stderr and asks for confirmation (if interactive)
 * on skipping output for an entity to a file (or device).
 */
int
dxf_entity_skip
(
        char *dxf_entity_name
                /*!< Type of the entity skipped from output. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char answer;
        if (dxf_entity_name == NULL) return (EXIT_FAILURE);
        if (INTER_ACTIVE_PROMPT)
        {
                fprintf (stderr, "    skip %s entity ? [Y/N]:\n", dxf_entity_name);
                answer = getchar ();
                if ((answer == 'Y') || (answer == 'y'))
                {
                        fprintf (stderr, "    OK, done.\n");
                }
        }
        else
        {
                fprintf (stderr, "    skipping %s entity.\n", dxf_entity_name);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
