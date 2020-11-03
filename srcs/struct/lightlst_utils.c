/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightlst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 21:46:12 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/02 21:52:46 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			lightlst_add(t_rt *rt, t_vec *loc, double bright, t_vec *color)
{
	t_list		*lightlst;

	lightlst = rt->lightlst;
	if (lightlst->content)
	{
		while (lightlst->next)
			lightlst = lightlst->next;
		lightlst->next = rtlst_new();
		lightlst = lightlst->next;
	}
	lightlst->content = light_new(loc, bright, color);
}

void			free_lightlst(t_list *lst)
{
	if (lst->next)
		free_camlst(lst->next);
	free_light(lst->content);
	free(lst);
}
