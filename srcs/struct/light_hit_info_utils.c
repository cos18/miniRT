/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_hit_info_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@studne>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:44:39 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/03 20:39:06 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light_hit_info		*lhit_info_new(t_vec *to, t_vec *normal, t_ray *r)
{
	t_light_hit_info	*result;

	result = (t_light_hit_info *)malloc_safe(sizeof(t_light_hit_info));
	result->to = vec_dup(to);
	result->normal = vec_unit(normal);
	result->r = (t_ray *)malloc_safe(sizeof(t_ray));
	result->r->dir = vec_dup(r->dir);
	result->r->orig = vec_dup(r->orig);
	return (result);
}

void					free_lhit_info(t_light_hit_info *info)
{
	free(info->to);
	free(info->normal);
	free_ray(info->r, TRUE);
	free(info);
}