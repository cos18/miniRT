/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_object.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:01:36 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/06 21:23:42 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			parse_sphere(t_rt *rt, char **words)
{
	t_sphere	*sp;
	t_material	*mat;
	t_vec		*color;

	if (check_info_cnt(words, 3) == FALSE)
		throw_error_num("Wrong number of informations in Sphere", EIO);
	color = vec_atoi(words[2]);
	if (vec_is_color_range(color) == FALSE)
		throw_error_num("Wrong RGB color value in Sphere", EIO);
	sp = sphere_new(vec_atod(words[0]), ft_atod_strict(words[1]) / 2.0);
	mat = mat_lambertian_new(color);
	hitlst_add(rt->hitlst, (void *)sp, OBJ_SPHERE, mat);
	free_material(mat);
}

void			parse_plane(t_rt *rt, char **words)
{
	t_plane		*pl;
	t_material	*mat;
	t_vec		*color;

	if (check_info_cnt(words, 3) == FALSE)
		throw_error_num("Wrong number of informations in Plane", EIO);
	color = vec_atoi(words[2]);
	if (vec_is_color_range(color) == FALSE)
		throw_error_num("Wrong RGB color value in Plane", EIO);
	pl = plane_new(vec_atod(words[0]), vec_atod(words[1]));
	mat = mat_lambertian_new(color);
	hitlst_add(rt->hitlst, (void *)pl, OBJ_PLANE, mat);
	free_material(mat);
}

void			parse_cylinder(t_rt *rt, char **words)
{
	t_cylinder	*cy;
	t_material	*mat;
	t_vec		*color;
	double		radius;
	double		height;

	if (check_info_cnt(words, 5) == FALSE)
		throw_error_num("Wrong number of informations in Cylinder", EIO);
	color = vec_atoi(words[2]);
	if (vec_is_color_range(color) == FALSE)
		throw_error_num("Wrong RGB color value in Cylinder", EIO);
	radius = ft_atod_strict(words[3]) / 2.0;
	if (radius <= 0)
		throw_error_num("Wrong diameter value in Cylinder", EIO);
	height = ft_atod_strict(words[4]);
	if (height <= 0)
		throw_error_num("Wrong height value in Cylinder", EIO);
	cy = cylinder_new(vec_atod(words[0]), vec_atod(words[1]), radius, height);
	mat = mat_lambertian_new(color);
	hitlst_add(rt->hitlst, (void *)cy, OBJ_CYLINDER, mat);
	free_material(mat);
}

void			parse_triangle(t_rt *rt, char **words)
{
	t_triangle	*tr;
	t_material	*mat;
	t_vec		*color;

	if (check_info_cnt(words, 4) == FALSE)
		throw_error_num("Wrong number of informations in Triangle", EIO);
	color = vec_atoi(words[3]);
	if (vec_is_color_range(color) == FALSE)
		throw_error_num("Wrong RGB color value in Triangle", EIO);
	tr = triangle_new(vec_atod(words[0]), vec_atod(words[1]),
						vec_atod(words[2]));
	mat = mat_lambertian_new(color);
	hitlst_add(rt->hitlst, (void *)tr, OBJ_TRIANGLE, mat);
	free_material(mat);
}

void			parse_square(t_rt *rt, char **words)
{
	t_square	*sq;
	t_material	*mat;
	t_vec		*color;
	double		side;

	if (check_info_cnt(words, 4) == FALSE)
		throw_error_num("Wrong number of informations in Square", EIO);
	color = vec_atoi(words[3]);
	if (vec_is_color_range(color) == FALSE)
		throw_error_num("Wrong RGB color value in Square", EIO);
	side = ft_atod_strict(words[2]);
	if (side < 0)
		throw_error_num("Wrong side size value in Square", EIO);
	sq = square_new(vec_atod(words[0]), vec_atod(words[1]), side);
	mat = mat_lambertian_new(color);
	hitlst_add(rt->hitlst, (void *)sq, OBJ_SQUARE, mat);
	free_material(mat);
}
