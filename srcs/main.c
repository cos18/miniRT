/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 21:12:06 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/26 22:16:24 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argv, char **argc)
{
	int	chapter;

	if (argv < 2 || argv > 3 ||
			(argv == 3 && (ft_strncmp(argc[2], "--save", 6) != 0)))
		return (ft_printf("Wrong argc\n"));
	chapter = ft_atoi(argc[1]);
	if (chapter == 2)
		show_final(argv - 2);
	else
		ft_printf("Wrong argc\n");
}
