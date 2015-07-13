/*!
 * \file comment.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief DXF comment entity (\c COMMENT).
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

#include "comment.h"

/*!
 * \brief Allocate memory for a DXF \c COMMENT.
 *
 * Fill the memory contents with zeros.
 */
DxfComment *
dxf_comment_new ()
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfComment *comment = NULL;
        size_t size;

        size = sizeof (DxfComment);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((comment = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfComment struct.\n")),
                  __FUNCTION__);
                comment = NULL;
        }
        else
        {
                memset (comment, 0, size);
        }
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (comment);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c COMMENT
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfComment *
dxf_comment_init
(
        DxfComment *comment
                /*!< a pointer to the DXF \COMMENT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (comment == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                comment = dxf_comment_new ();
        }
        if (comment == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfComment struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        comment->id_code = 0;
        comment->value = strdup ("");
        comment->next = NULL;
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (comment);
}


/*!
 * \brief Write DXF output to fp for a comment.
 *
 * The 999 group code indicates that the following line is a comment string.\n
 * DXFOUT does not currently include such groups in a DXF output file, but
 * DXFIN honors them and ignores the comments.\n
 * Thus, you can use the 999 group to include comments in a DXF file you've
 * edited.
 */
int
dxf_comment_write
(
        DxfFile *fp,
                /*!< file pointer to output file (or device). */
        DxfComment *comment
                /*!< a pointer to the DXF \COMMENT entity. */
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
        fprintf (fp->fp, "999\n%s\n", comment->value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c COMMENT and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_comment_free
(
        DxfComment *comment
                /*!< a pointer to the memory occupied by the DXF \c COMMENT
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (comment->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfComment was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (comment->value);
        free (comment);
        comment = NULL;
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c COMMENT
 * entities and all their data fields.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
void
dxf_comment_free_chain
(
        DxfComment *comments
                /*!< a pointer to the chain of DXF \c COMMENT entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (comments == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (comments != NULL)
        {
                struct DxfComment *iter = comments->next;
                dxf_comment_free (comments);
                comments = (DxfComment *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Set the given string for a DXF \c COMMENT entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfComment *
dxf_comment_set_value
(
        char *value,
                /*!< the comment value (string) to be set.*/
        DxfComment *comment
                /*!< a pointer to the chain of DXF \c COMMENT entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (comment == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        if (comment->value != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to the member in DxfComment was not NULL.\n")),
                __FUNCTION__);
              return (NULL);
        }
        comment->value = strdup (value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (comment);
}


/* EOF */
