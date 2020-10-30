/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:08:48 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/30 21:25:13 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int						ft_atoi_strict(char *str)
{
	unsigned long long	ans;
	int					minus;

	minus = 1;
	if (*str == '-' || *str == '+')
	{
		minus = ((*str == '-') ? -1 : 1);
		str++;
	}
	ans = 0;
	while (*str)
	{
		if (ft_isdigit(*str) == FALSE)
			throw_error_num("Wrong number character in .rt file", EIO);
		ans *= 10;
		ans += (*str - '0');
		str++;
	}
	return ((int)(ans * minus));
}

double					ft_atod_strict(char *str)
{
	int					len;
	char				**nums;
	double				result;
	double				tmp;

	nums = ft_split(str, '.');
	len = 0;
	while (nums[len] != NULL)
		len++;
	if (len == 0)
		throw_error_num("Wrong number character in .rt file", EIO);
	result = ft_atoi_strict(nums[0]);
	if (len == 2)
	{
		tmp = ft_atoi_strict(nums[1]);
		if (tmp < 0)
			throw_error_num("Wrong number character in .rt file", EIO);
		tmp /= pow(10, ft_strlen(nums[1]));
		result += (result < 0 ? (-1 * tmp) : tmp);
	}
	free_strs(nums, TRUE, 0);
	if (len >= 3)
		throw_error_num("Wrong number character in .rt file", EIO);
	return (result);
}

t_vec					*vec_str(char *str)
{
	t_vec				*result;
	char				**nums;
	double				val[3];
	int					len;

	nums = ft_split(str, ',');
	len = 0;
	while (nums[len] != NULL)
		len++;
	if (len != 3)
		throw_error_num("Wrong vector string in .rt file", EIO);
	len = -1;
	while ((++len) < 3)
		val[len] = ft_atod_strict(nums[len]);
	result = vec_create(val[0], val[1], val[2]);
	free_strs(nums, TRUE, 0);
	return (result);
}
