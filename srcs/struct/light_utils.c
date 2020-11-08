/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 21:39:12 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/08 11:31:04 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light				*light_new(t_vec *loc, double bright, t_vec *color)
{
	t_light			*result;

	result = (t_light *)malloc_safe(sizeof(t_light));
	result->loc = loc;
	result->bright = bright;
	result->color = vec_div_const_apply(color, 255);
	return (result);
}

void				free_light(t_light *l)
{
	free(l->loc);
	free(l->color);
	free(l);
}

static t_vec		*get_light_color(t_light *l, t_light_hit_info *info)
{
	t_vec			*color;
	t_vec			*light_to_p;
	t_vec			*reflect;
	t_vec			*see;
	double			c;

	color = vec_mul_const(l->color, l->bright);
	light_to_p = vec_unit_apply(vec_sub(info->to, l->loc));
	reflect = vec_unit_apply(vec_reflect(light_to_p, info->normal));
	see = vec_unit_apply(vec_mul_const(info->r->dir, -1.0));
	c = vec_dot(reflect, see);
	c = ((c < 0) ? 0 : c) / vec_length_squared(light_to_p);
	c = pow(c, 30);
	c += fmax(0, vec_dot(vec_mul_const_apply(light_to_p, -1), info->normal));
	vec_mul_const_apply(color, c);
	free(light_to_p);
	free(reflect);
	free(see);
	return (color);
}

void				light_next(t_list **hitlst, t_hitlst_info *hinfo)
{
	*hitlst = (*hitlst)->next;
	free_material(hinfo->mat);
	hinfo->mat = NULL;
}

void				light_hit(t_light *l, t_list *hitlst, t_vec *color,
								t_light_hit_info *info)
{
	int				is_hit;
	t_vec			*lcolor;
	t_hitlst_info	*hinfo;
	t_hittable		*hittable;

	is_hit = FALSE;
	hinfo = hitlst_info_new(ray_new(l->loc, vec_sub(info->to, l->loc)), 0.9);
	while (is_hit == FALSE && hitlst && hitlst->content)
	{
		hittable = (t_hittable *)(hitlst->content);
		hinfo->mat = material_dup(hittable->mat);
		if (hittable->obj_type == OBJ_SQUARE && hittable->onum == info->onum)
			light_next(&hitlst, hinfo);
		else if ((*(hittable->hit))(hittable->obj, hinfo->ray, hinfo,
					hinfo->rec) == FALSE)
			light_next(&hitlst, hinfo);
		else
			is_hit = TRUE;
	}
	free_hitlst_info(hinfo, FALSE, TRUE);
	if (is_hit)
		return ;
	lcolor = get_light_color(l, info);
	vec_add_apply(color, lcolor);
	free(lcolor);
}
