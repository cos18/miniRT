/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:34:43 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/08 10:40:10 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			parse_line(t_rt *rt, char **words)
{
	if (ft_strncmp(*words, "R", 2) == 0)
		parse_resolution(rt, ++words);
	else if (ft_strncmp(*words, "A", 2) == 0)
		parse_amb_light(rt, ++words);
	else if (ft_strncmp(*words, "c", 2) == 0)
		parse_camera(rt, ++words);
	else if (ft_strncmp(*words, "l", 2) == 0)
		parse_light(rt, ++words);
	else if (ft_strncmp(*words, "sp", 3) == 0)
		parse_sphere(rt, ++words);
	else if (ft_strncmp(*words, "pl", 3) == 0)
		parse_plane(rt, ++words);
	else if (ft_strncmp(*words, "sq", 3) == 0)
		parse_square(rt, ++words);
	else if (ft_strncmp(*words, "cy", 3) == 0)
		parse_cylinder(rt, ++words);
	else if (ft_strncmp(*words, "tr", 3) == 0)
		parse_triangle(rt, ++words);
	else
		throw_error_num("Wrong identifier in .rt file", EIO);
}
