/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:34:43 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/08 10:59:27 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void		pyramid_add_tri(t_rt *rt, t_square *sq, t_vec *point,
								t_material *mat)
{
	t_triangle	*tr;

	tr = triangle_new(vec_dup(point), vec_dup(sq->a), vec_dup(sq->b));
	hitlst_add(rt->hitlst, (void *)tr, OBJ_TRIANGLE, mat);
	tr = triangle_new(vec_dup(point), vec_dup(sq->b), vec_dup(sq->c));
	hitlst_add(rt->hitlst, (void *)tr, OBJ_TRIANGLE, mat);
	tr = triangle_new(vec_dup(point), vec_dup(sq->c), vec_dup(sq->d));
	hitlst_add(rt->hitlst, (void *)tr, OBJ_TRIANGLE, mat);
	tr = triangle_new(point, vec_dup(sq->a), vec_dup(sq->d));
	hitlst_add(rt->hitlst, (void *)tr, OBJ_TRIANGLE, mat);
}

/*
** pyramid format
** py (point of center of square) (up normal vector) (square side size)
** (pyramid height) (color)
*/

static void		parse_pyramid(t_rt *rt, char **words)
{
	t_square	*sq;
	t_vec		*point;
	t_material	*mat;
	t_vec		*color;
	double		s[2];

	if (check_info_cnt(words, 5) == FALSE)
		throw_error_num("Wrong number of informations in Pyramid", EIO);
	color = vec_atoi(words[4]);
	if (vec_is_color_range(color) == FALSE)
		throw_error_num("Wrong RGB color value in Pyramid", EIO);
	s[0] = ft_atod_strict(words[2]);
	if (s[0] < 0)
		throw_error_num("Wrong square side size value in Pyramid", EIO);
	s[1] = ft_atod_strict(words[3]);
	if (s[1] < 0)
		throw_error_num("Wrong height value in Pyramid", EIO);
	point = vec_atod(words[0]);
	sq = square_new(point, vec_atod(words[1]), s[0]);
	mat = mat_lambertian_new(color);
	hitlst_add(rt->hitlst, (void *)sq, OBJ_SQUARE, mat);
	color = vec_mul_const(sq->normal, s[1]);
	pyramid_add_tri(rt, sq, vec_add_apply(point, color), mat);
	free(color);
	free_material(mat);
}

void			parse_line(t_rt *rt, char **words)
{
	if (ft_strncmp(*words, "R", 2) == 0)
		parse_resolution(rt, ++words);
	else if (ft_strncmp(*words, "A", 2) == 0)
		parse_amb_light(rt, ++words);
	else if (ft_strncmp(*words, "c", 2) == 0)
		parse_camera(rt, ++words);
	else if (ft_strncmp(*words, "l", 2) == 0)
		parse_light(rt, ++words);
	else if (ft_strncmp(*words, "sp", 3) == 0)
		parse_sphere(rt, ++words);
	else if (ft_strncmp(*words, "pl", 3) == 0)
		parse_plane(rt, ++words);
	else if (ft_strncmp(*words, "sq", 3) == 0)
		parse_square(rt, ++words);
	else if (ft_strncmp(*words, "cy", 3) == 0)
		parse_cylinder(rt, ++words);
	else if (ft_strncmp(*words, "tr", 3) == 0)
		parse_triangle(rt, ++words);
	else if (ft_strncmp(*words, "py", 3) == 0)
		parse_pyramid(rt, ++words);
	else
		throw_error_num("Wrong identifier in .rt file", EIO);
}
