/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:13:02 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/07 16:58:54 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mlx_data		*g_img;
int				g_camnum;

static void		mlx_draw_img(t_mlx_data *mlx_data, t_img_data *img_data)
{
	int			width;
	int			height;
	char		*dst;
	int			next;

	width = -1;
	while ((++width) < img_data->width)
	{
		height = -1;
		while ((++height) < img_data->height)
		{
			next = (img_data->height - height - 1) * mlx_data->line_length;
			next += width * (mlx_data->bits_per_pixel / 8);
			dst = mlx_data->addr + next;
			*(unsigned int*)dst = img_data->img[width][height];
		}
	}
}

static int		exit_program(void)
{
	free_rt(g_img->rt);
	mlx_destroy_window(g_img->mlx, g_img->win);
	free(g_img->mlx);
	free(g_img);
	exit(0);
	return (0);
}

static void		draw_control(void)
{
	int			locate;
	t_list		*camlst;
	t_img_data	*data;

	camlst = g_img->camlst;
	locate = -1;
	while (++locate != g_camnum)
		camlst = camlst->next;
	data = ((t_camera *)(camlst->content))->data;
	g_img->img = mlx_new_image(g_img->mlx, data->width, data->height);
	g_img->addr = mlx_get_data_addr(g_img->img, &(g_img->bits_per_pixel), \
					&(g_img->line_length), &(g_img->endian));
	mlx_draw_img(g_img, data);
	mlx_put_image_to_window(g_img->mlx, g_img->win, g_img->img, 0, 0);
	mlx_destroy_image(g_img->mlx, g_img->img);
	g_camnum = (camlst->next) ? g_camnum + 1 : 0;
}

static int		mlx_key_handle(int keycode)
{
	if (keycode == 53)
		return (exit_program());
	if (keycode == 49)
		draw_control();
	return (0);
}

void			mlx_show(t_rt *rt)
{
	t_img_data	*data;

	g_camnum = 0;
	data = ((t_camera *)(rt->camlst->content))->data;
	g_img = (t_mlx_data *)malloc_safe(sizeof(t_mlx_data));
	g_img->rt = rt;
	g_img->camlst = rt->camlst;
	g_img->mlx = rt->mlx;
	g_img->win = mlx_new_window(rt->mlx, data->width, data->height, "miniRT");
	draw_control();
	mlx_hook(g_img->win, 2, 1L << 0, mlx_key_handle, 0);
	mlx_hook(g_img->win, 17, 1L << 17, exit_program, 0);
	mlx_loop(g_img->mlx);
}
