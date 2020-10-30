/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_object.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:01:36 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/30 21:24:02 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			parse_sphere(t_rt *rt, char **words)
{
	t_sphere	*sp;
	t_material	*mat;

	if (check_info_cnt(words, 3) == FALSE)
		throw_error_num("Wrong number of informations in Sphere", EIO);
	sp = sphere_new(vec_str(words[0]), ft_atod_strict(words[1]) / 2.0);
	mat = mat_lambertian_new(vec_str(words[2]));
	hitlst_add(rt->hitlst, (void *)sp, OBJ_SPHERE, mat);
	free_material(mat);
}

void			parse_plane(t_rt *rt, char **words)
{
	t_plane		*pl;
	t_material	*mat;

	if (check_info_cnt(words, 3) == FALSE)
		throw_error_num("Wrong number of informations in Plane", EIO);
	pl = plane_new(vec_str(words[0]), vec_str(words[1]));
	mat = mat_lambertian_new(vec_str(words[2]));
	hitlst_add(rt->hitlst, (void *)pl, OBJ_PLANE, mat);
	free_material(mat);
}
