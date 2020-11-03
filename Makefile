# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunpark <sunpark@studne>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/04 13:34:20 by sunpark           #+#    #+#              #
#    Updated: 2020/11/03 15:07:31 by sunpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= main.c error.c color.c mlx_utils.c save_bmp.c cal_utils.c \
		random_bonus.c draw_hittable_pthread_bonus.c \
		struct/vector_calc.c struct/vector_utils.c struct/ray_utils.c \
		struct/vector_apply.c struct/hit_record.c struct/hittable_utils.c \
		struct/hitlst_utils.c struct/hitlst_info_utils.c struct/camera_utils.c \
		struct/vector_create.c struct/vector_random_bonus.c \
		struct/vector_calc_extra.c struct/material_utils.c \
		struct/thread_info_utils_bonus.c struct/img_data_utils.c \
		struct/camlst_utils.c struct/vector_utils_extra.c \
		struct/light_utils.c struct/lightlst_utils.c \
		struct/light_hit_info_utils.c \
		parse/split_space.c parse/parse_string.c parse/parse_element.c \
		parse/parse_element_object.c parse/parse_file.c \
		object/sphere.c object/plane.c \
		material/simple_material.c

SRCDIR	= ./srcs/
SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(SRCS:.c=.o)

INCDIR	= ./includes/
LIBDIR	= ./libft/
LIBNAME	= libft.a
MLXDIR	= ./mlx/
MLXNAME	= libmlx.dylib

NAME	= miniRT

GCC		= gcc
GCCFLAG	= -Wall -Wextra -Werror -g -fsanitize=address
RM		= rm -f

%.o:		%.c
			$(GCC) $(GCCFLAG) -I$(INCDIR) -c $< -o $@

$(NAME):	$(LIBNAME) $(MLXNAME) $(OBJS)
			$(GCC) $(GCCFLAG) -I$(INCDIR) -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJS) $(LIBNAME) $(MLXNAME)

$(LIBNAME):
			@$(MAKE) -C $(LIBDIR) bonus
			@cp $(addprefix $(LIBDIR), $(LIBNAME)) $(LIBNAME)

$(MLXNAME):
			@$(MAKE) -C $(MLXDIR)
			@cp $(addprefix $(MLXDIR), $(MLXNAME)) $(MLXNAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS) $(COBJS) *.bmp

fclean:		clean
			$(RM) $(NAME) $(LIBNAME) $(MLXNAME)
			@$(MAKE) -C $(LIBDIR) fclean
			@$(MAKE) -C $(MLXDIR) clean

re:			fclean all

.PHONY:		all clean fclean re
