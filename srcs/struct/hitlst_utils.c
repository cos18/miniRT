/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitlst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 16:29:29 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/06 21:24:01 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_list			*rtlst_new(void)
{
	t_list		*result;

	result = (t_list *)malloc_safe(sizeof(t_list));
	result->content = NULL;
	result->next = NULL;
	return (result);
}

void			hitlst_add(t_list *lst, void *obj, int obj_type,
								t_material *mat)
{
	if (lst->content)
	{
		while (lst->next)
			lst = lst->next;
		lst->next = rtlst_new();
		lst = lst->next;
	}
	lst->content = hittable_create(obj, obj_type, mat);
}

void			free_hitlst(t_list *lst)
{
	if (lst->next)
		free_hitlst(lst->next);
	free_hittable(lst->content);
	free(lst);
}

int				hitlst_hit(t_list *lst, t_hitlst_info *info)
{
	int			hit_anything;
	t_hittable	*hittable;

	hit_anything = FALSE;
	while (lst && lst->content)
	{
		hittable = (t_hittable *)(lst->content);
		info->mat = material_dup(hittable->mat);
		if ((*(hittable->hit))(hittable->obj, info->ray, info, info->rec))
		{
			hit_anything = TRUE;
			info->t_max = info->rec->t;
		}
		lst = lst->next;
		free_material(info->mat);
	}
	return (hit_anything);
}
