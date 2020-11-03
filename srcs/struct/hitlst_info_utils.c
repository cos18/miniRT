/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitlst_info_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@studne>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 04:25:55 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/03 14:13:05 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hitlst_info		*hitlst_info_new(t_ray *r, double tmax)
{
	t_hitlst_info	*result;

	result = (t_hitlst_info *)malloc_safe(sizeof(t_hitlst_info));
	result->ray = r;
	result->t_min = HIT_T_MIN;
	result->t_max = tmax;
	result->rec = hit_record_new();
	return (result);
}

void				free_hitlst_info(t_hitlst_info *info, int is_ray_ori_free)
{
	free_ray(info->ray, is_ray_ori_free);
	free_hit_record(info->rec);
	free(info);
}
