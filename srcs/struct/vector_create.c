/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:40:57 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/06 21:24:24 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec		*vec_new(double x, double y, double z)
{
	t_vec	*result;

	result = (t_vec*)malloc_safe(sizeof(t_vec));
	result->x = x;
	result->y = y;
	result->z = z;
	return (result);
}

t_vec		*vec_dup(t_vec *ori)
{
	return (vec_new(ori->x, ori->y, ori->z));
}
