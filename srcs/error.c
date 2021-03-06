/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:46:52 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/30 20:14:14 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		throw_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void		throw_error_num(char *message, int pnum)
{
	errno = pnum;
	throw_error(message);
}

void		*malloc_safe(size_t size)
{
	void	*result;

	result = malloc(size);
	if (result == NULL)
		throw_error("Malloc failed");
	return (result);
}
