/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_object.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:01:36 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/31 14:48:19 by sunpark          ###   ########.fr       */
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
