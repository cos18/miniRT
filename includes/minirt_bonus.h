/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@studne>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 12:42:18 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/03 14:59:06 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "minirt.h"
# include <pthread.h>

double			random_double(void);
double			random_double_range(double min, double max);
t_hitlst_info	*get_hitlst_info_anti(int x, int y, t_camera *cam);

t_vec			*vec_random_range(double min, double max);
t_vec			*vec_random_in_unit_sphere(void);
t_vec			*vec_random_unit(void);
t_vec			*vec_random_in_hemisphere(t_vec *normal);

int				get_color_sample_gamma(t_vec *color);

void			draw_hittable_pthread(t_camera *cam, t_rt *rt);

#endif
