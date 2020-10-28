/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:46:52 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/28 21:08:27 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		throw(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void		*malloc_safe(size_t size)
{
	void	*result;

	result = malloc(size);
	if (result == NULL)
		throw("Malloc Failed");
	return (result);
}
