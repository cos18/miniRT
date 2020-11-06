/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 20:31:29 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/06 21:38:43 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material		*mat_lambertian_new(t_vec *color)
{
	t_material	*result;

	result = material_new(MAT_LAMBERTIAN, color);
	return (result);
}
