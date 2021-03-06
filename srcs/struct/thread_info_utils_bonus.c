/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_info_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 11:23:18 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/06 21:24:18 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_thread_info		*tinfo_new(t_camera *cam, t_rt *rt, int tnum)
{
	t_thread_info	*result;

	result = (t_thread_info *)malloc_safe(sizeof(t_thread_info));
	result->cam = cam;
	result->hitlst = rt->hitlst;
	result->lightlst = rt->lightlst;
	result->tnum = tnum;
	return (result);
}

int					tinfo_get_step(t_thread_info *info)
{
	return (info->cam->data->height / PTHREAD_CNT);
}

int					tinfo_get_y_init_value(t_thread_info *info)
{
	if (info->tnum == PTHREAD_CNT)
		return (info->cam->data->height);
	return (tinfo_get_step(info) * info->tnum);
}
