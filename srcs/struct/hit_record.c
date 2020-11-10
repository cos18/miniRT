/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 15:57:03 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/10 20:38:26 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit_record	*hit_record_new(void)
{
	t_hit_record	*result;

	result = (t_hit_record *)malloc_safe(sizeof(t_hit_record));
	result->normal = NULL;
	result->p = NULL;
	result->mat = NULL;
	return (result);
}

void			reset_hit_record(t_hit_record *rec)
{
	if (rec->normal)
	{
		free(rec->normal);
		rec->normal = NULL;
	}
	if (rec->p)
	{
		free(rec->p);
		rec->p = NULL;
	}
	if (rec->mat)
	{
		free_material(rec->mat);
		rec->mat = NULL;
	}
}

void			free_hit_record(t_hit_record *rec)
{
	reset_hit_record(rec);
	free(rec);
}

void			hit_set_normal(t_hit_record *record, t_ray *r)
{
	vec_unit_apply(record->normal);
	record->is_front_face = (vec_dot(r->dir, record->normal) < 0) ?
								TRUE : FALSE;
	if (record->is_front_face == FALSE)
		vec_mul_c_apply(record->normal, -1);
}
