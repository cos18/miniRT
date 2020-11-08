# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/04 13:34:20 by sunpark           #+#    #+#              #
#    Updated: 2020/11/08 11:25:27 by sunpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= error.c color.c mlx_utils.c save_bmp.c cal_utils.c \
		struct/vector_calc.c struct/vector_utils.c struct/ray_utils.c \
		struct/vector_apply.c struct/hit_record.c struct/hittable_utils.c \
		struct/hitlst_utils.c struct/hitlst_info_utils.c struct/camera_utils.c \
		struct/vector_create.c \
		struct/vector_calc_extra.c struct/material_utils.c \
		struct/img_data_utils.c \
		struct/camlst_utils.c struct/vector_utils_extra.c \
		struct/light_utils.c struct/lightlst_utils.c \
		struct/light_hit_info_utils.c \
		parse/split_space.c parse/parse_string.c parse/parse_element.c \
		parse/parse_element_object.c parse/parse_file.c \
		object/sphere.c object/plane.c object/cylinder.c \
		object/cylinder_hit.c object/triangle.c object/square.c \
		object/square_hit.c \

MSRC	= main.c draw_hittable.c material/simple_material.c \
		parse/parse_line.c

BSRC	= main_bonus.c random_bonus.c draw_hittable_pthread_bonus.c \
		struct/vector_random_bonus.c struct/thread_info_utils_bonus.c \
		material/simple_material_bonus.c parse/parse_bonus.c \

SRCDIR	= ./srcs/
SRCS	= $(addprefix $(SRCDIR), $(SRC))
MSRCS	= $(addprefix $(SRCDIR), $(MSRC))
BSRCS	= $(addprefix $(SRCDIR), $(BSRC))
OBJS	= $(SRCS:.c=.o)
MOBJS	= $(MSRCS:.c=.o)
BOBJS	= $(BSRCS:.c=.o)

INCDIR	= ./includes/
LIBDIR	= ./libft/
LIBNAME	= libft.a
MLXDIR	= ./mlx/
MLXNAME	= libmlx.dylib

NAME	= miniRT

GCC		= gcc
GCCFLAG	= -Wall -Wextra -Werror
RM		= rm -f

%.o:		%.c
			$(GCC) $(GCCFLAG) -I$(INCDIR) -c $< -o $@

$(NAME):	$(LIBNAME) $(MLXNAME) $(OBJS) $(MOBJS)
			$(GCC) $(GCCFLAG) -I$(INCDIR) -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJS) $(MOBJS) $(LIBNAME) $(MLXNAME)

$(LIBNAME):
			@$(MAKE) -C $(LIBDIR) bonus
			@cp $(addprefix $(LIBDIR), $(LIBNAME)) $(LIBNAME)

$(MLXNAME):
			@$(MAKE) -C $(MLXDIR)
			@cp $(addprefix $(MLXDIR), $(MLXNAME)) $(MLXNAME)

bonus:		$(LIBNAME) $(MLXNAME) $(OBJS) $(BOBJS)
			$(GCC) $(GCCFLAG) -I$(INCDIR) -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJS) $(BOBJS) $(LIBNAME) $(MLXNAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS) $(MOBJS) $(BOBJS) *.bmp

fclean:		clean
			$(RM) $(NAME) $(LIBNAME) $(MLXNAME)
			@$(MAKE) -C $(LIBDIR) fclean
			@$(MAKE) -C $(MLXDIR) clean

re:			fclean all

.PHONY:		all clean fclean re
