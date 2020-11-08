/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:34:43 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/08 17:05:07 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		mat->amb = vec_dup(rt->amb_light);
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
	int			fnamelen;
	int			fd;
	t_rt		*result;

	fnamelen = ft_strlen(filename);
	if (fnamelen < 3 || ft_strncmp(filename + fnamelen - 3, ".rt", 4) != 0)
		throw_error_num("Wrong config file extension .rt", EIO);
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

void			free_rt(t_rt *rt)
{
	free_camlst(rt->camlst);
	free_hitlst(rt->hitlst);
	free_lightlst(rt->lightlst);
	free(rt->amb_light);
	free(rt);
}
