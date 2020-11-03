/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 21:39:12 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/02 21:45:20 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light		*light_new(t_vec *loc, double bright, t_vec *color)
{
	t_light	*result;

	result = (t_light *)malloc_safe(sizeof(t_light));
	result->loc = loc;
	result->bright = bright;
	result->color = color;
	return (result);
}

void		free_light(t_light *l)
{
	free(l->loc);
	free(l->color);
	free(l);
}
