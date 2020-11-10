/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 20:27:10 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/10 20:38:47 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material_info		*material_info_new(void)
{
	t_material_info	*result;

	result = (t_material_info *)malloc_safe(sizeof(t_material_info));
	result->attenuation = NULL;
	result->scattered = NULL;
	return (result);
}

void				free_material_info(t_material_info *info)
{
	if (info->attenuation)
		free(info->attenuation);
	if (info->scattered)
		free_ray(info->scattered, TRUE);
}

t_material			*material_new(int mat_type, t_vec *color)
{
	t_material		*result;

	result = (t_material *)malloc_safe(sizeof(t_material));
	vec_div_c_apply(color, 255.0);
	result->color = color;
	result->mat_type = mat_type;
	result->amb = NULL;
	return (result);
}

t_material			*material_dup(t_material *mat)
{
	t_material		*result;

	result = (t_material *)malloc_safe(sizeof(t_material));
	result->color = vec_dup(mat->color);
	result->mat_type = mat->mat_type;
	result->scatter = mat->scatter;
	result->amb = (mat->amb != NULL) ? vec_dup(mat->amb) : NULL;
	if (mat->mat_type == MAT_METAL)
		result->fuzz = mat->fuzz;
	return (result);
}

void				free_material(t_material *mat)
{
	if (mat->amb)
		free(mat->amb);
	free(mat->color);
	free(mat);
}
