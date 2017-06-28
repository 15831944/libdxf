/*!
 * \file object_ptr.c
 *
 * \author Copyright (C) 2015, 2017 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF object_ptr object (\c OBJECT_PTR).
 *
 * \since The \c OBJECT_PTR object was introduced in DXF R14.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
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


#include "object_ptr.h"


/*!
 * \brief Allocate memory for a \c DxfObjectPtr.
 *
 * Fill the memory contents with zeros.
 */
DxfObjectPtr *
dxf_object_ptr_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfObjectPtr *object_ptr = NULL;
        size_t size;

        size = sizeof (DxfObjectPtr);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((object_ptr = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfObjectPtr struct.\n")),
                  __FUNCTION__);
                object_ptr = NULL;
        }
        else
        {
                memset (object_ptr, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_ptr);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c OBJECT_PTR
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfObjectPtr *
dxf_object_ptr_init
(
        DxfObjectPtr *object_ptr
                /*!< a pointer to the DXF \c OBJECT_PTR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (object_ptr == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                object_ptr = dxf_object_ptr_new ();
        }
        if (object_ptr == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfObjectPtr struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        object_ptr->id_code = 0;
        object_ptr->dictionary_owner_soft = strdup ("");
        object_ptr->dictionary_owner_hard = strdup ("");
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                object_ptr->xdata[i] = strdup ("");
        }
        object_ptr->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_ptr);
}


/*!
 * \brief Read data from a DXF file into a DXF \c OBJECT_PTR object.
 *
 * The last line read from file contained the string "OBJECT_PTR". \n
 * Now follows some data for the \c OBJECT_PTR, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c object_ptr. \n
 *
 * \return a pointer to \c object_ptr.
 */
DxfObjectPtr *
dxf_object_ptr_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfObjectPtr *object_ptr
                /*!< a pointer to the DXF \c OBJECT_PTR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (temp_string);
                return (NULL);
        }
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (object_ptr == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                object_ptr = dxf_object_ptr_new ();
                object_ptr = dxf_object_ptr_init (object_ptr);
        }
        i = 0;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &object_ptr->id_code);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", object_ptr->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", object_ptr->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, (_("DXF comment: %s\n")), temp_string);
                }
                else if (strcmp (temp_string, "1001") == 0)
                {
                        /* Now follows a string containing extended data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", object_ptr->xdata[i]);
                        i++;
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_ptr);
}


/*!
 * \brief Write DXF output to a file for a DXF \c OBJECT_PTR object.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_object_ptr_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfObjectPtr *object_ptr
                /*!< a pointer to the DXF \c OBJECT_PTR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("OBJECT_PTR");
        int i;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (object_ptr == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, object_ptr->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (object_ptr->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", object_ptr->id_code);
        }
        /*!
         * \todo for version R14.\n
         * Implementing the start of application-defined group
         * "{application_name", with Group code 102.\n
         * For example: "{ACAD_REACTORS" indicates the start of the
         * AutoCAD persistent reactors group.\n\n
         * application-defined codes: Group codes and values within the
         * 102 groups are application defined (optional).\n\n
         * End of group, "}" (optional), with Group code 102.
         */
        if ((strcmp (object_ptr->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", object_ptr->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (object_ptr->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", object_ptr->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        i = 0;
        while (strlen (object_ptr->xdata[i]) > 0)
        {
                fprintf (fp->fp, "1001\n%s\n", object_ptr->xdata[i]);
                i++;
                /*! \todo Check for overrun of array index. */
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c OBJECT_PTR and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_object_ptr_free
(
        DxfObjectPtr *object_ptr
                /*!< a pointer to the memory occupied by the DXF
                 * \c OBJECT_PTR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (object_ptr->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfObjectPtr was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (object_ptr->dictionary_owner_soft);
        free (object_ptr->dictionary_owner_hard);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (object_ptr->xdata[i]);
        }
        free (object_ptr);
        object_ptr = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c OBJECT_PTR
 * objects and all their data fields.
 */
void
dxf_object_ptr_free_chain
(
        DxfObjectPtr *objectptrs
                /*!< a pointer to the chain of DXF \c OBJECT_PTR objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (objectptrs == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (objectptrs != NULL)
        {
                struct DxfObjectPtr *iter = objectptrs->next;
                dxf_object_ptr_free (objectptrs);
                objectptrs = (DxfObjectPtr *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c OBJECT_PTR object.
 *
 * \return \c id_code.
 */
int
dxf_object_ptr_get_id_code
(
        DxfObjectPtr *object_ptr
                /*!< a pointer to a DXF \c OBJECT_PTR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_ptr == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (object_ptr->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_ptr->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c OBJECT_PTR object.
 */
DxfObjectPtr *
dxf_object_ptr_set_id_code
(
        DxfObjectPtr *object_ptr,
                /*!< a pointer to a DXF \c OBJECT_PTR object. */
        int id_code
                /*!< Identification number for the object.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_ptr == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        object_ptr->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_ptr);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c OBJECT_PTR object.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_object_ptr_get_dictionary_owner_soft
(
        DxfObjectPtr *object_ptr
                /*!< a pointer to a DXF \c OBJECT_PTR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_ptr == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_ptr->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (object_ptr->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c OBJECT_PTR object.
 */
DxfObjectPtr *
dxf_object_ptr_set_dictionary_owner_soft
(
        DxfObjectPtr *object_ptr,
                /*!< a pointer to a DXF \c OBJECT_PTR object. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_ptr == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        object_ptr->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_ptr);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c OBJECT_PTR object.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_object_ptr_get_dictionary_owner_hard
(
        DxfObjectPtr *object_ptr
                /*!< a pointer to a DXF \c OBJECT_PTR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_ptr == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_ptr->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (object_ptr->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c OBJECT_PTR object.
 */
DxfObjectPtr *
dxf_object_ptr_set_dictionary_owner_hard
(
        DxfObjectPtr *object_ptr,
                /*!< a pointer to a DXF \c OBJECT_PTR object. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_ptr == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_hard == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        object_ptr->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_ptr);
}


/*!
 * \brief Get the pointer to the next \c OBJECT_PTR object from a DXF 
 * \c OBJECT_PTR object.
 *
 * \return pointer to the next \c OBJECT_PTR object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfObjectPtr *
dxf_object_ptr_get_next
(
        DxfObjectPtr *object_ptr
                /*!< a pointer to a DXF \c OBJECT_PTR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_ptr == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_ptr->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfObjectPtr *) object_ptr->next);
}


/*!
 * \brief Set the pointer to the next \c OBJECT_PTR object for a DXF
 * \c OBJECT_PTR object.
 */
DxfObjectPtr *
dxf_object_ptr_set_next
(
        DxfObjectPtr *object_ptr,
                /*!< a pointer to a DXF \c OBJECT_PTR object. */
        DxfObjectPtr *next
                /*!< a pointer to the next \c OBJECT_PTR object for the
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_ptr == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        object_ptr->next = (struct DxfObjectPtr *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_ptr);
}


/* EOF*/
