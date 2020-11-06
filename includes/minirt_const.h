/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_const.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@studne>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:11:02 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/05 21:15:00 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_CONST_H
# define MINIRT_CONST_H

# define TRUE 1
# define FALSE 0

# define MINI_PI 3.1415926535897932385

# define OBJ_SPHERE 1
# define OBJ_PLANE 2
# define OBJ_SQUARE 3
# define OBJ_CYLINDER 4
# define OBJ_TRIANGLE 5

# define MAT_LAMBERTIAN 1
# define MAT_METAL 2

# define HIT_T_MIN 0.001
# define ANTI_SAMPLES 100
# define REFLECT_DEPTH 5
# define PTHREAD_CNT 16

#endif
