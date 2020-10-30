/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camlst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 16:29:29 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/30 19:30:13 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			camlst_add(t_rt *rt, t_vec *from, t_vec *at, double fov)
{
	t_list		*camlst;

	camlst = rt->camlst;
	if (camlst->content)
	{
		while (camlst->next)
			camlst = camlst->next;
		camlst->next = rtlst_new();
		camlst = camlst->next;
	}
	camlst->content = camera_locate_new(from, at, rt->img->aspect_ratio, fov);
}

void			free_camlst(t_list *lst)
{
	if (lst->next)
		free_camlst(lst->next);
	free_camera(lst->content);
	free(lst);
}
