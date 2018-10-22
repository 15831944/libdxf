/*!
 * \file entities.c
 *
 * \author Copyright (C) 2012, 2014, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
 * \brief Allocate memory for a DXF \c ENTITIES section.
 *
 * Fill the memory contents with zeros.
 */
DxfEntities *
dxf_entities_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfEntities *entities = NULL;
        size_t size;

        size = sizeof (DxfEntities);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((entities = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfEntities struct.\n")),
                  __FUNCTION__);
                entities = NULL;
        }
        else
        {
                memset (entities, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (entities);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * \c ENTITIES section.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfEntities *
dxf_entities_init
(
        DxfEntities *entities
                /*!< DXF entities section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entities == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                entities = dxf_entities_new ();
        }
        if (entities == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfEntities struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        entities->dface_list = NULL;
        entities->dsolid_list = NULL;
        entities->acad_proxy_entity_list = NULL;
        entities->arc_list = NULL;
        entities->attdef_list = NULL;
        entities->attrib_list = NULL;
        entities->body_list = NULL;
        entities->circle_list = NULL;
        entities->dimension_list = NULL;
        entities->ellipse_list = NULL;
        entities->hatch_list = NULL;
        entities->helix_list = NULL;
        entities->image_list = NULL;
        entities->insert_list = NULL;
        entities->leader_list = NULL;
        //entities->light_list = NULL;
        entities->line_list = NULL;
        entities->lw_polyline_list = NULL;
        //entities->mesh_list = NULL;
        entities->mline_list = NULL;
        //entities->mleader_list = NULL;
        //entities->mleaderstyle_list = NULL;
        entities->mtext_list = NULL;
        entities->oleframe_list = NULL;
        entities->ole2frame_list = NULL;
        entities->point_list = NULL;
        entities->polyline_list = NULL;
        entities->ray_list = NULL;
        entities->region_list = NULL;
        //entities->section_list = NULL;
        entities->shape_list = NULL;
        entities->solid_list = NULL;
        entities->spline_list = NULL;
        //entities->sun_list = NULL;
        //entities->surface_list = NULL;
        entities->table_list = NULL;
        entities->text_list = NULL;
        entities->tolerance_list = NULL;
        entities->trace_list = NULL;
        //entities->underlay_list = NULL;
        entities->vertex_list = NULL;
        entities->viewport_list = NULL;
        //entities->wipeout_list = NULL;
        //entities->xline_list = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (entities);
}


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
                /*!< AutoCAD DXF version number. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /*! \todo Add code here. */
#if DEBUG
        DXF_DEBUG_END
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
                /*!< pointer to a list of entities. */
        int acad_version_number
                /*!< AutoCAD DXF version number. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /*! \todo Add code here. */
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
