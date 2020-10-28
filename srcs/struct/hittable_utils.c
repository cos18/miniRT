/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 16:35:38 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/28 21:17:44 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hittable		*hittable_create(void *obj, int obj_type, t_material *mat)
{
	t_hittable	*result;

	result = (t_hittable *)malloc_safe(sizeof(t_hittable));
	result->obj = obj;
	result->obj_type = obj_type;
	result->mat = material_dup(mat);
	if (obj_type == OBJ_SPHERE)
		result->hit = &sphere_hit;
	return (result);
}

void			free_hittable(t_hittable *h)
{
	if (h->obj_type == OBJ_SPHERE)
		free_sphere(h->obj);
	if (h->mat)
		free_material(h->mat);
	free(h);
}
