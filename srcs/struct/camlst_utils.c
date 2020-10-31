/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camlst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 16:29:29 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/31 14:58:43 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			caminfo_lst_add(t_rt *rt, t_vec *from, t_vec *at, double fov)
{
	t_list		*camlst;
	t_cam_info	*info;

	camlst = rt->camlst;
	if (camlst->content)
	{
		while (camlst->next)
			camlst = camlst->next;
		camlst->next = rtlst_new();
		camlst = camlst->next;
	}
	info = (t_cam_info *)malloc_safe(sizeof(t_cam_info));
	info->from = from;
	info->at = at;
	info->fov = fov;
	camlst->content = (void *)info;
}

void			camlst_add(t_rt *rt, t_list *camlst, t_cam_info *info)
{
	if (camlst->content)
	{
		while (camlst->next)
			camlst = camlst->next;
		camlst->next = rtlst_new();
		camlst = camlst->next;
	}
	camlst->content = camera_locate_new(info->from, info->at,
												rt->aspect_ratio, info->fov);
	((t_camera *)(camlst->content))->data = create_img_data(rt->width, rt->height);
}

void			free_camlst(t_list *lst)
{
	if (lst->next)
		free_camlst(lst->next);
	free_camera(lst->content);
	free(lst);
}

void			free_caminfolst(t_list *lst)
{
	if (lst->next)
		free_camlst(lst->next);
	free(lst->content);
	free(lst);
}
