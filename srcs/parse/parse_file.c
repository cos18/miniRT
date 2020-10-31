/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:34:43 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/31 17:53:27 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Using ft_isalpha -> Not impledmented yet
*/

static void		parse_line(t_rt *rt, char **words)
{
	if (ft_strncmp(*words, "R", 2) == 0)
		parse_resolution(rt, ++words);
	else if (ft_strncmp(*words, "A", 2) == 0)
		parse_amb_light(rt, ++words);
	else if (ft_strncmp(*words, "c", 2) == 0)
		parse_camera(rt, ++words);
	else if (ft_strncmp(*words, "l", 2) == 0)
		ft_isalpha(**words);
	else if (ft_strncmp(*words, "sp", 3) == 0)
		parse_sphere(rt, ++words);
	else if (ft_strncmp(*words, "pl", 3) == 0)
		parse_plane(rt, ++words);
	else if (ft_strncmp(*words, "sq", 3) == 0)
		ft_isalpha(**words);
	else if (ft_strncmp(*words, "cy", 3) == 0)
		ft_isalpha(**words);
	else if (ft_strncmp(*words, "tr", 3) == 0)
		ft_isalpha(**words);
	else
		throw_error_num("Wrong identifier in .rt file", EIO);
}

static void		read_line(t_rt *rt, int fd)
{
	char		**words;
	char		*line;
	int			status;

	line = NULL;
	while ((status = get_next_line(fd, &line)) != GNL_ERROR)
	{
		if (*line != 0 && *line != '#')
		{
			if (!ft_isalpha(*line))
				throw_error_num("Form error in .rt file", EIO);
			if ((words = split_space(line)) == NULL)
				throw_error("Split string failed");
			parse_line(rt, words);
			free_strs(words, TRUE, 0);
		}
		free(line);
		line = NULL;
		if (status == GNL_READ_EOF)
			break ;
	}
	if (line)
		free(line);
	if (status == GNL_ERROR)
		throw_error("GNL failed");
}

static void		apply_lst(t_rt *rt)
{
	t_list		*lst;
	t_material	*mat;
	t_list		*info_lst;
	t_cam_info	*info;

	lst = rt->hitlst;
	while (lst && lst->content)
	{
		mat = ((t_hittable *)(lst->content))->mat;
		vec_mul_each_apply(mat->color, rt->amb_light);
		lst = lst->next;
	}
	info_lst = rt->camlst;
	lst = rtlst_new();
	while (info_lst && info_lst->content)
	{
		info = info_lst->content;
		camlst_add(rt, lst, info);
		info_lst = info_lst->next;
	}
	free_caminfolst(rt->camlst);
	rt->camlst = lst;
}

t_rt			*parse_file(char *filename, int is_mlx)
{
	int			fd;
	t_rt		*result;

	if ((fd = open(filename, O_RDONLY)) < 0)
		throw_error("File open error");
	result = (t_rt *)malloc_safe(sizeof(t_rt));
	result->mlx = (is_mlx ? mlx_init() : NULL);
	result->width = 0;
	result->camlst = rtlst_new();
	result->lightlst = rtlst_new();
	result->hitlst = rtlst_new();
	result->amb_light = NULL;
	read_line(result, fd);
	close(fd);
	if (result->width == 0 || result->camlst->content == NULL
		|| result->amb_light == NULL)
		throw_error_num("Nessesary element missing in .rt file", EIO);
	apply_lst(result);
	return (result);
}

// NEED TO FIX LIGHTLST FREE & camlst free in later!!!!

void			free_rt(t_rt *rt)
{
	// free_camlst(rt->camlst);
	free_hitlst(rt->hitlst);
	free(rt->lightlst);
	free(rt->amb_light);
	free(rt);
}
