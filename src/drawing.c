/*!
 * \file drawing.c
 *
 * \author Copyright (C) 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a libDXF drawing.
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


#include "drawing.h"


/*!
 * \brief Allocate memory for a libDXF \c drawing.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfDrawing *
dxf_drawing_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfDrawing *drawing = NULL;
        size_t size;

        size = sizeof (DxfDrawing);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((drawing = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfDrawing struct.\n")),
                  __FUNCTION__);
                drawing = NULL;
        }
        else
        {
                memset (drawing, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (drawing);
}


/*!
 * \brief Allocate memory and initialize data fields in a libDXF drawing.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfDrawing *
dxf_drawing_init
(
        DxfDrawing *drawing,
                /*!< a pointer to the libDXF drawing. */
        int acad_version_number
                /*!< AutoCAD version number.\n */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                drawing = dxf_drawing_new ();
        }
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfDrawing struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_header_init ((DxfHeader *) drawing->header, acad_version_number);
        dxf_class_init ((DxfClass *) drawing->class_list);
        dxf_block_init ((DxfBlock *) drawing->block_list);
        //dxf_entities_init ((DxfEntities *) drawing->entities_list);
        dxf_object_init ((DxfObject *) drawing->object_list);
        dxf_thumbnail_init ((DxfThumbnail *) drawing->thumbnail);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (drawing);
}


/*!
 * \brief Free the allocated memory for a libDXF drawing and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_drawing_free
(
        DxfDrawing *drawing
                /*!< a pointer to the memory occupied by the libDXF
                 * drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        dxf_header_free ((DxfHeader *) drawing->header);
        dxf_class_free_chain ((DxfClass *) drawing->class_list);
        dxf_block_free_chain ((DxfBlock *) drawing->block_list);
        //dxf_entities_free_chain ((DxfEntities *) drawing->entities_list);
        dxf_object_free_chain ((DxfObject *) drawing->object_list);
        dxf_thumbnail_free ((DxfThumbnail *) drawing->thumbnail);
        free (drawing);
        drawing = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Get the header from a libDXF drawing.
 *
 * \return \c header when successful, \c NULL when an error occurred.
 */
DxfHeader *
dxf_drawing_get_header
(
        DxfDrawing *drawing
                /*!< a pointer to a libDXF drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHeader *result = NULL;

        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (drawing->header ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the header member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfHeader *) drawing->header;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the header for a libDXF drawing.
 *
 * \return a pointer to the libDXF drawing when OK, \c NULL when an
 * error occurred.
 */
DxfDrawing *
dxf_drawing_set_header
(
        DxfDrawing *drawing,
                /*!< a pointer to a libDXF drawing. */
        DxfHeader *header
                /*!< a string containing the header for the libDXF
                 * drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (header == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        drawing->header = (struct DxfHeader *) header;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (drawing);
}


/*!
 * \brief Get the first entry to the Classes list from a libDXF drawing.
 *
 * \return \c class_list when sucessful, \c NULL when an error occurred.
 */
DxfClass *
dxf_drawing_get_class_list
(
        DxfDrawing *drawing
                /*!< a pointer to a DXF drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfClass *result = NULL;

        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (drawing->class_list ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the class_list member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfClass *) drawing->class_list;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the first entry to the Classes list for a libDXF drawing.
 *
 * \return a pointer to the libDXF drawing when OK, \c NULL when an
 * error occurred.
 */
DxfDrawing *
dxf_drawing_set_class_list
(
        DxfDrawing *drawing,
                /*!< a pointer to a libDXF drawing. */
        DxfClass *class_list
                /*!< a pointer containing the first entry to the Classes
                 * list for the libDXF drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (class_list == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        drawing->class_list = (struct DxfClass *) class_list;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (drawing);
}


/* EOF*/
