/*!
 * \file spline.c
 * 
 * \author Copyright (C) 2013 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * 
 * \brief Functions for a DXF spline entity (\c SPLINE).
 *
 * A spline is a smooth curve that passes through or near a given set of
 * points.\n
 * You can control how closely the curve fits the points.\n
 * The SPLINE creates a particular type of spline known as a nonuniform
 * rational B-spline (NURBS) curve.\n
 * A NURBS curve produces a smooth curve between control points.\n
 * You create splines by specifying points.\n
 * You can close the spline so that the start and endpoints are
 * coincident and tangent.\n
 * Tolerance describes how closely the spline fits the set of fit points
 * you specify.\n
 * The lower the tolerance, the more closely the spline fits the points.\n
 * At zero tolerance, the spline passes through the points.\n
 *
 * <b>Order.</b>\n
 * The order of a NURBS curve defines the number of nearby control
 * points that influence any given point on the curve.\n
 * The curve is represented mathematically by a polynomial of degree one
 * less than the order of the curve.\n
 * Hence, second-order curves (which are represented by linear
 * polynomials) are called linear curves, third-order curves are called
 * quadratic curves, and fourth-order curves are called cubic curves.\n
 * The number of control points must be greater than or equal to the
 * order of the curve.\n
 * \n
 * In practice, cubic curves are the ones most commonly used.\n
 * Fifth- and sixth-order curves are sometimes useful, especially for
 * obtaining continuous higher order derivatives, but curves of higher
 * orders are practically never used because they lead to internal
 * numerical problems and tend to require disproportionately large
 * calculation times.\n
 *
 * <b>Control points.</b>\n
 * The control points determine the shape of the curve.\n
 * Typically, each point of the curve is computed by taking a weighted
 * sum of a number of control points.\n
 * The weight of each point varies according to the governing parameter.\n
 * For a curve of degree d, the weight of any control point is only
 * nonzero in d+1 intervals of the parameter space.\n
 * Within those intervals, the weight changes according to a polynomial
 * function (basis functions) of degree d.\n
 * At the boundaries of the intervals, the basis functions go smoothly
 * to zero, the smoothness being determined by the degree of the
 * polynomial.\n
 * \n
 * As an example, the basis function of degree one is a triangle
 * function.\n
 * It rises from zero to one, then falls to zero again.\n
 * While it rises, the basis function of the previous control point
 * falls.\n
 * In that way, the curve interpolates between the two points, and the
 * resulting curve is a polygon, which is continuous, but not
 * differentiable at the interval boundaries, or knots.\n
 * Higher degree polynomials have correspondingly more continuous
 * derivatives.\n
 * Note that within the interval the polynomial nature of the basis
 * functions and the linearity of the construction make the curve
 * perfectly smooth, so it is only at the knots that discontinuity can
 * arise.\n
 * \n
 * The fact that a single control point only influences those intervals
 * where it is active is a highly desirable property, known as local
 * support.\n
 * In modeling, it allows the changing of one part of a surface while
 * keeping other parts equal.\n
 * \n
 * Adding more control points allows better approximation to a given
 * curve, although only a certain class of curves can be represented
 * exactly with a finite number of control points.\n
 * NURBS curves also feature a scalar weight for each control point.\n
 * This allows for more control over the shape of the curve without
 * unduly raising the number of control points.\n
 * In particular, it adds conic sections like circles and ellipses to
 * the set of curves that can be represented exactly.\n
 * The term rational in NURBS refers to these weights.\n
 * \n
 * The control points can have any dimensionality.\n
 * One-dimensional points just define a scalar function of the
 * parameter.\n
 * These are typically used in image processing programs to tune the
 * brightness and color curves.\n
 * Three-dimensional control points are used abundantly in 3D modeling,
 * where they are used in the everyday meaning of the word 'point', a
 * location in 3D space.\n
 * Multi-dimensional points might be used to control sets of time-driven
 * values, e.g. the different positional and rotational settings of a
 * robot arm.\n
 * NURBS surfaces are just an application of this.\n
 * Each control 'point' is actually a full vector of control points,
 * defining a curve.\n
 * These curves share their degree and the number of control points, and
 * span one dimension of the parameter space.\n
 * By interpolating these control vectors over the other dimension of
 * the parameter space, a continuous set of curves is obtained, defining
 * the surface.\n
 *
 * <b>The knot vector.</b>\n
 * The knot vector is a sequence of parameter values that determines
 * where and how the control points affect the NURBS curve.\n
 * The number of knots is always equal to the number of control points
 * plus curve degree plus one (i.e. number of control points plus curve
 * order).\n
 * The knot vector divides the parametric space in the intervals
 * mentioned before, usually referred to as knot spans.\n
 * Each time the parameter value enters a new knot span, a new control
 * point becomes active, while an old control point is discarded.\n
 * It follows that the values in the knot vector should be in
 * nondecreasing order, so (0, 0, 1, 2, 3, 3) is valid while (0, 0, 2,
 * 1, 3, 3) is not.\n
 * \n
 * Consecutive knots can have the same value.\n
 * This then defines a knot span of zero length, which implies that two
 * control points are activated at the same time (and of course two
 * control points become deactivated).\n
 * This has impact on continuity of the resulting curve or its higher
 * derivatives; for instance, it allows the creation of corners in an
 * otherwise smooth NURBS curve.\n
 * A number of coinciding knots is sometimes referred to as a knot with
 * a certain multiplicity.\n
 * Knots with multiplicity two or three are known as double or triple
 * knots.\n
 * The multiplicity of a knot is limited to the degree of the curve;
 * since a higher multiplicity would split the curve into disjoint parts
 * and it would leave control points unused.\n
 * For first-degree NURBS, each knot is paired with a control point.\n
 * \n
 * The knot vector usually starts with a knot that has multiplicity
 * equal to the order.\n
 * This makes sense, since this activates the control points that have
 * influence on the first knot span.\n
 * Similarly, the knot vector usually ends with a knot of that
 * multiplicity.\n
 * Curves with such knot vectors start and end in a control point.\n
 * \n
 * The individual knot values are not meaningful by themselves; only the
 * ratios of the difference between the knot values matter.\n
 * Hence, the knot vectors (0, 0, 1, 2, 3, 3) and (0, 0, 2, 4, 6, 6)
 * produce the same curve.\n
 * The positions of the knot values influences the mapping of parameter
 * space to curve space.\n
 * Rendering a NURBS curve is usually done by stepping with a fixed
 * stride through the parameter range.\n
 * By changing the knot span lengths, more sample points can be used in
 * regions where the curvature is high.\n
 * Another use is in situations where the parameter value has some
 * physical significance, for instance if the parameter is time and the
 * curve describes the motion of a robot arm.\n
 * The knot span lengths then translate into velocity and acceleration,
 * which are essential to get right to prevent damage to the robot arm
 * or its environment.\n
 * This flexibility in the mapping is what the phrase non uniform in
 * NURBS refers to.\n
 * \n
 * Necessary only for internal calculations, knots are usually not
 * helpful to the users of modeling software.\n
 * Therefore, many modeling applications do not make the knots editable
 * or even visible.\n
 * It's usually possible to establish reasonable knot vectors by looking
 * at the variation in the control points.\n
 * More recent versions of NURBS software (e.g., Autodesk Maya and
 * Rhinoceros 3D) allow for interactive editing of knot positions, but
 * this is significantly less intuitive than the editing of control
 * points.\n
 *
 * <b>Fit Tolerance.</b>\n
 * Changes the tolerance for fitting of the current spline curve.\n
 * The spline curve is redefined so that it fits through the existing
 * points according to the new tolerance.\n
 * You can repeatedly change the fit tolerance, but doing so changes the
 * fit tolerance for all the control points regardless of the control
 * point that is selected.\n
 * If you set the tolerance to 0, the spline curve passes through the
 * fit points.\n
 * Entering a tolerance greater than 0 allows the spline curve to pass
 * through the fit points within the specified tolerance.
 *
 * \image html dxf_spline_tolerance.png
 *
 * <b>Tangents.</b>\n
 * Defines the tangency for the first and last points of the spline
 * curve.\n
 * The Start Tangent specifies the tangency of the spline curve at the
 * first point.\n
 *
 * \image html dxf_spline_first_tangent_point.png
 *
 * The End Tangent specifies the tangency of the spline curve at the
 * last point.\n
 *
 * \image html dxf_spline_last_tangent_point.png
 *
 * \version According to DXF R10 (backward compatibility). 
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
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
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#include "spline.h"


/*!
 * \brief Allocate memory for a DXF \c SPLINE.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfSpline *
dxf_spline_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSpline *spline = NULL;
        size_t size;

        size = sizeof (DxfSpline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((spline = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSpline struct.\n")),
                  __FUNCTION__);
                spline = NULL;
        }
        else
        {
                memset (spline, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c SPLINE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfSpline *
dxf_spline_init
(
        DxfSpline *spline
                /*!< a pointer to the DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                spline = dxf_spline_new ();
        }
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSpline struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->id_code = 0;
        spline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        spline->layer = strdup (DXF_DEFAULT_LAYER);
        spline->elevation = 0.0;
        spline->thickness = 0.0;
        spline->linetype_scale = 1.0;
        spline->visibility = 0;
        spline->color = DXF_COLOR_BYLAYER;
        spline->paperspace = DXF_MODELSPACE;
        spline->graphics_data_size = 0;
        spline->shadow_mode = 0;
        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) spline->binary_graphics_data);
        spline->dictionary_owner_soft = strdup ("");
        spline->material = strdup ("");
        spline->dictionary_owner_hard = strdup ("");
        spline->lineweight = 0;
        spline->plot_style_name = strdup ("");
        spline->color_value = 0;
        spline->color_name = strdup ("");
        spline->transparency = 0;
        spline->p0 = dxf_point_init (spline->p0);
        spline->p1 = dxf_point_init (spline->p1);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                spline->knot_value[i] = 0.0;
                spline->weight_value[i] = 0.0;
        }
        spline->x2 = 0.0;
        spline->y2 = 0.0;
        spline->z2 = 0.0;
        spline->x3 = 0.0;
        spline->y3 = 0.0;
        spline->z3 = 0.0;
        spline->extr_x0 = 0.0;
        spline->extr_y0 = 0.0;
        spline->extr_z0 = 0.0;
        spline->knot_tolerance = DXF_SPLINE_KNOT_TOLERANCE_DEFAULT;
        spline->control_point_tolerance = DXF_SPLINE_CONTROL_POINT_TOLERANCE_DEFAULT;
        spline->fit_tolerance = DXF_SPLINE_FIT_TOLERANCE_DEFAULT;
        spline->flag = 0;
        spline->degree = 0;
        spline->number_of_knots = 0;
        spline->number_of_control_points = 0;
        spline->number_of_fit_points = 0;
        spline->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Read data from a DXF file into a DXF \c SPLINE entity.
 *
 * The last line read from file contained the string "SPLINE". \n
 * Now follows some data for the \c SPLINE, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c spline. \n
 *
 * \return a pointer to \c spline, or \c NULL when an error occurred.
 */
DxfSpline *
dxf_spline_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfSpline *spline
                /*!< a pointer to the DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i_x0;
        int i_y0;
        int i_z0;
        int i_x1;
        int i_y1;
        int i_z1;
        int i_knot_value;
        int i_weight_value;
        DxfBinaryGraphicsData *binary_graphics_data = NULL;
        DxfPoint *p0 = NULL;
        DxfPoint *p1 = NULL;

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
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                spline = dxf_spline_new ();
                spline = dxf_spline_init (spline);
        }
        i_x0 = 0;
        i_y0 = 0;
        i_z0 = 0;
        i_x1 = 0;
        i_y1 = 0;
        i_z1 = 0;
        i_knot_value = 0;
        i_weight_value = 0;
        binary_graphics_data = (DxfBinaryGraphicsData *) spline->binary_graphics_data;
        p0 = (DxfPoint *) spline->p0;
        p1 = (DxfPoint *) spline->p1;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        fclose (fp->fp);
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &spline->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", spline->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", spline->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the control point coordinate
                         * (multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of control point coordinate
                         * (multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the control point coordinate
                         * (multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &p0->z0);
                        dxf_point_init ((DxfPoint *) p0->next);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the fit point coordinate
                         * (multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the fit point coordinate
                         * (multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the fit point coordinate
                         * (multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &p1->z0);
                        dxf_point_init ((DxfPoint *) p1->next);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the start tangent,
                         * may be omitted (in WCS). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spline->x2);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the start tangent,
                         * may be omitted (in WCS). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spline->y2);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the start tangent,
                         * may be omitted (in WCS). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spline->z2);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the end tangent,
                         * may be omitted (in WCS). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spline->x3);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the end tangent,
                         * may be omitted (in WCS). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spline->y3);
                }
                else if (strcmp (temp_string, "33") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the end tangent,
                         * may be omitted (in WCS). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spline->z3);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (spline->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spline->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a thickness value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spline->thickness);
                        i_knot_value++;
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a knot value (one entry per knot, multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spline->knot_value[i_knot_value]);
                        i_knot_value++;
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a weight value (one entry per knot, multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spline->weight_value[i_weight_value]);
                        i_weight_value++;
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a knot tolerance value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spline->knot_tolerance);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a control point tolerance value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spline->control_point_tolerance);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a fit point tolerance value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spline->fit_tolerance);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a linetype scale value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spline->linetype_scale);
                        i_knot_value++;
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &spline->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &spline->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &spline->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a flag value (bit coded). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &spline->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a degree of spline curve value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &spline->degree);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a number of knots value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &spline->number_of_knots);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a number of control points value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &spline->number_of_control_points);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a number of fit points value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &spline->number_of_fit_points);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &spline->graphics_data_size);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &spline->shadow_mode);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", binary_graphics_data->data_line);
                        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) binary_graphics_data->next);
                        binary_graphics_data = (DxfBinaryGraphicsData *) binary_graphics_data->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing a
                         * soft-pointer ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", spline->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", spline->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", spline->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &spline->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", spline->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &spline->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", spline->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &spline->transparency);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (spline->linetype, "") == 0)
        {
                spline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (spline->layer, "") == 0)
        {
                spline->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Write DXF output for a DXF \c SPLINE entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_spline_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfSpline *spline
                /*!< a pointer to the DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("SPLINE");
        int i;
        DxfBinaryGraphicsData *binary_graphics_data = NULL;
        DxfPoint *p0 = NULL;
        DxfPoint *p1 = NULL;

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
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (strcmp (spline->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, spline->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                spline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (spline->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, spline->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to default layer.\n")),
                  dxf_entity_name);
                spline->layer = DXF_DEFAULT_LAYER;
        }
        /* Start writing output. */
        binary_graphics_data = (DxfBinaryGraphicsData *) spline->binary_graphics_data;
        p0 = (DxfPoint *) spline->p0;
        p1 = (DxfPoint *) spline->p1;
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (spline->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", spline->id_code);
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
        if ((strcmp (spline->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", spline->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (spline->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", spline->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (spline->paperspace != DXF_MODELSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", spline->layer);
        if (strcmp (spline->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", spline->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (spline->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", spline->elevation);
        }
        if ((fp->acad_version_number >= AutoCAD_2007)
          && (strcmp (spline->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", spline->material);
        }
        if (spline->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", spline->color);
        }
        if (spline->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", spline->thickness);
        }
        fprintf (fp->fp, "370\n%d\n", spline->lineweight);
        fprintf (fp->fp, " 48\n%f\n", spline->linetype_scale);
        if (spline->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", spline->visibility);
        }
        fprintf (fp->fp, " 92\n%d\n", spline->graphics_data_size);
        while (binary_graphics_data != NULL)
        {
                fprintf (fp->fp, "310\n%s\n", binary_graphics_data->data_line);
                binary_graphics_data = (DxfBinaryGraphicsData *) binary_graphics_data->next;
        }
        fprintf (fp->fp, "420\n%ld\n", spline->color_value);
        fprintf (fp->fp, "430\n%s\n", spline->color_name);
        fprintf (fp->fp, "440\n%ld\n", spline->transparency);
        fprintf (fp->fp, "390\n%s\n", spline->plot_style_name);
        fprintf (fp->fp, "284\n%d\n", spline->shadow_mode);
        fprintf (fp->fp, "100\nAcDbSpline\n");
        if ((fp->acad_version_number >= AutoCAD_12)
                && (spline->extr_x0 != 0.0)
                && (spline->extr_y0 != 0.0)
                && (spline->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", spline->extr_x0);
                fprintf (fp->fp, "220\n%f\n", spline->extr_y0);
                fprintf (fp->fp, "230\n%f\n", spline->extr_z0);
        }
        fprintf (fp->fp, " 70\n%d\n", spline->flag);
        fprintf (fp->fp, " 71\n%d\n", spline->degree);
        fprintf (fp->fp, " 72\n%d\n", spline->number_of_knots);
        fprintf (fp->fp, " 73\n%d\n", spline->number_of_control_points);
        fprintf (fp->fp, " 74\n%d\n", spline->number_of_fit_points);
        fprintf (fp->fp, " 42\n%f\n", spline->knot_tolerance);
        fprintf (fp->fp, " 43\n%f\n", spline->control_point_tolerance);
        fprintf (fp->fp, " 12\n%f\n", spline->x2);
        fprintf (fp->fp, " 22\n%f\n", spline->y2);
        fprintf (fp->fp, " 32\n%f\n", spline->z2);
        fprintf (fp->fp, " 13\n%f\n", spline->x3);
        fprintf (fp->fp, " 23\n%f\n", spline->y3);
        fprintf (fp->fp, " 33\n%f\n", spline->z3);
        for (i = 0; i < spline->number_of_knots; i++)
        {
                fprintf (fp->fp, " 40\n%f\n", spline->knot_value[i]);
        }
        if (spline->number_of_fit_points != 0)
        {
        for (i = 0; i < spline->number_of_fit_points; i++)
                {
                        fprintf (fp->fp, " 41\n%f\n", spline->weight_value[i]);
                }
        }
        while (spline->p0 != NULL)
        {
                fprintf (fp->fp, " 10\n%f\n", p0->x0);
                fprintf (fp->fp, " 20\n%f\n", p0->y0);
                fprintf (fp->fp, " 30\n%f\n", p0->z0);
                p0 = (DxfPoint *) p0->next;
        }
        while (spline->p1 != NULL)
        {
                fprintf (fp->fp, " 11\n%f\n", p1->x0);
                fprintf (fp->fp, " 21\n%f\n", p1->y0);
                fprintf (fp->fp, " 31\n%f\n", p1->z0);
                p1 = (DxfPoint *) p1->next;
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c SPLINE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_spline_free
(
        DxfSpline *spline
                /*!< a pointer to the memory occupied by the DXF \c SPLINE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (spline->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfSpline was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (spline->linetype);
        free (spline->layer);
        free (spline->dictionary_owner_soft);
        free (spline->material);
        free (spline->dictionary_owner_hard);
        free (spline->plot_style_name);
        free (spline->color_name);
        dxf_binary_graphics_data_free_chain (spline->binary_graphics_data);
        free (spline);
        spline = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c SPLINE
 * entities and all their data fields.
 */
void
dxf_spline_free_chain
(
        DxfSpline *splines
                /*!< a pointer to the chain of DXF \c SPLINE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (splines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (splines != NULL)
        {
                struct DxfSpline *iter = splines->next;
                dxf_spline_free (splines);
                splines = (DxfSpline *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c SPLINE.
 *
 * \return \c id_code when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_spline_get_id_code
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id_code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = spline->id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the ID code for a DXF \c SPLINE entity.
 *
 * \return \c spline when successful or \c NULL when an error occurred.
 */
DxfSpline *
dxf_spline_set_id_code
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        int id_code
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative id-code value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the \c linetype from a DXF \c SPLINE entity.
 *
 * \return \c linetype when sucessful, or \c NULL when an error occurred.
 */
char *
dxf_spline_get_linetype
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spline->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (spline->linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c linetype for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_linetype
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        char *linetype
                /*!< a string containing the \c linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the \c layer from a DXF \c SPLINE entity.
 *
 * \return \c layer when sucessful, or \c NULL when an error occurred.
 */
char *
dxf_spline_get_layer
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spline->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (spline->layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c layer for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_layer
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        char *layer
                /*!< a string containing the \c layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the \c elevation from a DXF \c SPLINE entity.
 *
 * \return \c elevation when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_spline_get_elevation
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = spline->elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c elevation for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_elevation
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the \c thickness from a DXF \c SPLINE entity.
 *
 * \return \c thickness when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_spline_get_thickness
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the thickness member.\n")),
                  __FUNCTION__);
        }
        result = spline->thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c thickness for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_thickness
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative thickness value was passed.\n")),
                  __FUNCTION__);
        }
        spline->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c SPLINE entity.
 *
 * \return \c linetype_scale when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_spline_get_linetype_scale
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the linetype scale member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = spline->linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_linetype_scale
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative linetype scale value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the \c visibility from a DXF \c SPLINE entity.
 *
 * \return \c visibility when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_spline_get_visibility
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int16_t result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = spline->visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c visibility for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_visibility
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the \c color from a DXF \c SPLINE entity.
 *
 * \return \c color when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_spline_get_color
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the color member.\n")),
                  __FUNCTION__);
        }
        result = spline->color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c color for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_color
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative color value was passed.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("\teffectively turning this entity it's visibility off.\n")));
        }
        spline->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c SPLINE entity.
 *
 * \return \c paperspace flag value when successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int
dxf_spline_get_paperspace
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        if (spline->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        result = spline->paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_paperspace
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c SPLINE entity.
 *
 * \return \c graphics_data_size flag value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_spline_get_graphics_data_size
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
        if (spline->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
        result = spline->graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_graphics_data_size
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative graphics_data_size value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a zero graphics_data_size value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c SPLINE entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_spline_get_shadow_mode
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int16_t result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the shadow_mode member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the shadow_mode member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = spline->shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_shadow_mode
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative shadow_mode value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range shadow_mode value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF 
 * \c SPLINE entity.
 *
 * \return a pointer to the \c binary_graphics_data when successful, or
 * \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_spline_get_binary_graphics_data
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfBinaryGraphicsData *result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spline->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the binary_graphics_data member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfBinaryGraphicsData *) spline->binary_graphics_data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_binary_graphics_data
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF
 * \c SPLINE entity.
 *
 * \return a pointer to \c dictionary_owner_soft when successful, or
 * \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_spline_get_dictionary_owner_soft
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spline->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (spline->dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_dictionary_owner_soft
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
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
        spline->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c SPLINE entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_spline_get_material
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spline->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the material member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (spline->material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_material
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (material == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF
 * \c SPLINE entity.
 *
 * \return a pointer to \c dictionary_owner_hard when successful, or
 * \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_spline_get_dictionary_owner_hard
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spline->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_hard member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (spline->dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_dictionary_owner_hard
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
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
        spline->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the \c lineweight from a DXF \c SPLINE entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_spline_get_lineweight
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int16_t result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = spline->lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c lineweight for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_lineweight
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c SPLINE entity.
 *
 * \return \c plot_style_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_spline_get_plot_style_name
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spline->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the plot_style_name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (spline->plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_plot_style_name
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (plot_style_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the \c color_value from a DXF \c SPLINE entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_spline_get_color_value
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        long result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = spline->color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c color_value for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_color_value
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the \c color_name from a DXF \c SPLINE entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_spline_get_color_name
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spline->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the color_name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (spline->color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c color_name for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_color_name
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the \c transparency from a DXF \c SPLINE entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_spline_get_transparency
(
        DxfSpline *spline
                /*!< a pointer to a DXF \c SPLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        long result;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = spline->transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c transparency for a DXF \c SPLINE entity.
 *
 * \return a pointer to \c spline when successful, or \c NULL when an
 * error occurred.
 */
DxfSpline *
dxf_spline_set_transparency
(
        DxfSpline *spline,
                /*!< a pointer to a DXF \c SPLINE entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/* EOF */
