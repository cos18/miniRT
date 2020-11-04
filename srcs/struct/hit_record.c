/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@studne>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 15:57:03 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/04 17:28:39 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit_record	*hit_record_new(void)
{
	t_hit_record	*result;

	result = (t_hit_record *)malloc_safe(sizeof(t_hit_record));
	result->normal = NULL;
	result->p = NULL;
	return (result);
}

void			reset_hit_record(t_hit_record *rec)
{
	if (rec->normal)
		free(rec->normal);
	if (rec->p)
		free(rec->p);
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
		vec_mul_const_apply(record->normal, -1);
}
