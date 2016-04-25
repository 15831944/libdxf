/*!
 * \file binary_entity_data.c
 *
 * \author Copyright (C) 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF binary entity data object.
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


#include "binary_entity_data.h"


/*!
 * \brief Allocate memory for a binary entity data object.
 *
 * Fill the memory contents with zeros.
 */
DxfBinaryEntityData *
dxf_binary_entity_data_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfBinaryEntityData *data = NULL;
        size_t size;

        size = sizeof (DxfBinaryEntityData);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((data = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfBinaryEntityData struct.\n")),
                  __FUNCTION__);
                data = NULL;
        }
        else
        {
                memset (data, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Allocate memory and initialize data fields in a binary
 * entity data entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfBinaryEntityData *
dxf_binary_entity_data_init
(
        DxfBinaryEntityData *data
                /*!< a pointer to the binary entity data object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                data = dxf_binary_entity_data_new ();
        }
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfBinaryEntityData struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->data_line = strdup ("");
        data->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Write DXF output to fp for a binary entity data object.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_binary_entity_data_write
(
        DxfFile *fp,
                /*!< file pointer to output file (or device). */
        DxfBinaryEntityData *data
                /*!< a pointer to the binary entity data object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "310\n%s\n", data->data_line);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a binary entity data object
 * and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_binary_entity_data_free
(
        DxfBinaryEntityData *data
                /*!< Pointer to the memory occupied by the binary
                 * entity data entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (data->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfBinaryEntityData was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (data->data_line);
        free (data);
        data = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of binary entity data
 * bobjects and all their data fields.
 */
void
dxf_binary_entity_data_free_chain
(
        DxfBinaryEntityData *data
                /*!< pointer to the chain of DXF \c HATCH binary
                 * entity data objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (data != NULL)
        {
                struct DxfBinaryEntityData *iter = data->next;
                dxf_binary_entity_data_free (data);
                data = (DxfBinaryEntityData *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the data_line from a binary entity data object.
 *
 * \return data_line when sucessful, \c NULL when an error occurred.
 */
char *
dxf_binary_entity_data_get_data_line
(
        DxfBinaryEntityData *data
                /*!< a pointer to a binary entity data object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data->data_line ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the data_line member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (data->data_line);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/* EOF */
