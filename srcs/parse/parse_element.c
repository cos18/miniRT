/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:58:17 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/30 21:25:03 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int				check_info_cnt(char **words, int len)
{
	int			cnt;

	cnt = 0;
	while (words[cnt] != NULL)
		cnt++;
	return (cnt == len ? TRUE : FALSE);
}

void			parse_resolution(t_rt *rt, char **words)
{
	if (rt->img != NULL)
		throw_error_num("Multi Resolution in .rt file", EIO);
	if (check_info_cnt(words, 2) == FALSE)
		throw_error_num("Wrong number of informations in Resolution", EIO);
	rt->img = create_img_data(ft_atod_strict(words[0]),
								ft_atod_strict(words[1]));
}

void			parse_amb_light(t_rt *rt, char **words)
{
	if (rt->amb_light != NULL)
		throw_error_num("Multi Ambient Light in .rt file", EIO);
	if (check_info_cnt(words, 2) == FALSE)
		throw_error_num("Wrong number of informations in Ambient Light", EIO);
	rt->amb_light = vec_str(words[1]);
	vec_mul_const_apply(rt->amb_light, ft_atod_strict(words[0]) / 255.0);
}

void			parse_camera(t_rt *rt, char **words)
{
	double		degree;

	if (check_info_cnt(words, 3) == FALSE)
		throw_error_num("Wrong number of informations in Camera", EIO);
	degree = ft_atod_strict(words[2]);
	camlst_add(rt, vec_str(words[0]), vec_str(words[1]), get_radian(degree));
}

// void			parse_light(t_rt *rt, char **words);
