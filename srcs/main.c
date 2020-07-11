/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 21:12:06 by sunpark           #+#    #+#             */
/*   Updated: 2020/07/11 21:16:45 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "minirt.h"

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int				main(void)
{
	void	*mlx;
	t_data	*img;
	void	*mlx_win;
	int		i;
	int		j;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "miniRT");
	img = (t_data *)malloc(sizeof(t_data));
	img->img = mlx_new_image(mlx, 1000, 1000);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), \
					&(img->line_length), &(img->endian));
	i = 99;
	while (++i < 200)
	{
		j = 99;
		while (++j < 200)
			my_mlx_pixel_put(img, i, j, 0x00FF0000);
	}
	mlx_put_image_to_window(mlx, mlx_win, img->img, 0, 0);
	mlx_loop(mlx);
	free(img);
}
