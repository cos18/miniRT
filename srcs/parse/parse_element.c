/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:58:17 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/31 14:56:18 by sunpark          ###   ########.fr       */
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
	int			swidth;
	int			sheight;

	if (rt->width != 0)
		throw_error_num("Multi Resolution in .rt file", EIO);
	if (check_info_cnt(words, 2) == FALSE)
		throw_error_num("Wrong number of informations in Resolution", EIO);
	rt->width = ft_atoi_strict(words[0]);
	rt->height = ft_atoi_strict(words[1]);
	if (rt->width <= 0 || rt->height <= 0)
		throw_error_num("Resolution must be positive", EIO);
	if (rt->mlx)
	{
		mlx_get_screen_size(rt->mlx, &swidth, &sheight);
		rt->width = (rt->width > swidth) ? swidth : rt->width;
		rt->height = (rt->height > sheight) ? sheight : rt->height;
	}
	rt->aspect_ratio = (double)(rt->width) / (double)(rt->height);
}

void			parse_amb_light(t_rt *rt, char **words)
{
	if (rt->amb_light != NULL)
		throw_error_num("Multi Ambient Light in .rt file", EIO);
	if (check_info_cnt(words, 2) == FALSE)
		throw_error_num("Wrong number of informations in Ambient Light", EIO);
	rt->amb_light = vec_atoi(words[1]);
	if (vec_is_color_range(rt->amb_light) == FALSE)
		throw_error_num("Wrong RGB color value in Ambient Light", EIO);
	vec_mul_const_apply(rt->amb_light, ft_atod_strict(words[0]) / 255.0);
}

void			parse_camera(t_rt *rt, char **words)
{
	double		degree;

	if (check_info_cnt(words, 3) == FALSE)
		throw_error_num("Wrong number of informations in Camera", EIO);
	degree = ft_atod_strict(words[2]);
	if (degree < 0 || 180 < degree)
		throw_error_num("Wrong fov value in Camera", EIO);
	caminfo_lst_add(rt, vec_atod(words[0]), vec_atod(words[1]), get_radian(degree));
}

// void			parse_light(t_rt *rt, char **words);
