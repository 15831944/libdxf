/*!
 * \file util.h
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \author Copyright (C) 2010, 2014, 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for libDXF coding utilities.
 *
 * <hr>
 * <h1><b>Copyright Notices.</b></h1>\n
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.\n\n
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


#ifndef LIBDXF_SRC_UTIL_H
#define LIBDXF_SRC_UTIL_H

#include "global.h"
#include "file.h"


#ifdef __cplusplus
extern "C" {
#endif


/*! Macro to return if the expression is false */
#define dxf_return_val_if_fail(expr, val) if (!expr) return val;

/*! Macro to return according to the expression */
enum return_state { FAIL = 0, SUCCESS, FOUND };

#define dxf_return(expr) switch(expr) \
	{ \
	case FAIL: \
		return FAIL; \
		break; \
	case FOUND: \
		return FOUND; \
		break; \
	}


DxfChar *dxf_char_new ();
DxfChar *dxf_char_init (DxfChar *c);
int dxf_char_free (DxfChar *c);
int dxf_char_free_list (DxfChar *chars);
DxfDouble *dxf_double_new ();
DxfDouble *dxf_double_init (DxfDouble *d);
int dxf_double_free (DxfDouble *d);
int dxf_double_free_list (DxfDouble *doubles);
DxfInt *dxf_int_new ();
DxfInt *dxf_int_init (DxfInt *i);
int dxf_int_free (DxfInt *i);
int dxf_int_free_chain (DxfInt *ints);
int dxf_read_is_double (int type);
int dxf_read_is_int (int type);
int dxf_read_is_string (int type);
int dxf_read_line (char * temp_string, DxfFile *fp);
int dxf_read_scanf (DxfFile *fp, const char *template, ...);
DxfFile *dxf_read_init (const char *filename);
void dxf_read_close (DxfFile *file);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_UTIL_H */


/* EOF */
