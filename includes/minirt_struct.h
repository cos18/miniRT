/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 21:48:41 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/10 20:38:47 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCT_H
# define MINIRT_STRUCT_H

# include "libft.h"

struct s_material;
struct s_rt;
struct s_cam_info;
struct s_light_hit_info;
struct s_camera;

typedef struct			s_vars
{
	void				*mlx;
	void				*win;
}						t_vars;

typedef struct			s_mlx_data
{
	struct s_rt			*rt;
	t_list				*camlst;
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_mlx_data;

typedef struct			s_img_data
{
	int					**img;
	int					width;
	int					height;
	double				aspect_ratio;
}						t_img_data;

t_img_data				*create_img_data(int width, int height);
void					free_img_data(t_img_data *data);

typedef struct			s_vec
{
	double				x;
	double				y;
	double				z;
}						t_vec;

t_vec					*vec_new(double x, double y, double z);
t_vec					*vec_dup(t_vec *ori);

t_vec					*vec_add(t_vec *a, t_vec *b);
t_vec					*vec_sub(t_vec *a, t_vec *b);
t_vec					*vec_mul_c(t_vec *a, double c);
t_vec					*vec_div_c(t_vec *a, double c);
t_vec					*vec_reflect(t_vec *v, t_vec *n);

double					vec_length_squared(t_vec *a);
double					vec_length(t_vec *a);
double					vec_dot(t_vec *a, t_vec *b);
t_vec					*vec_cross(t_vec *a, t_vec *b);
t_vec					*vec_unit(t_vec *a);

int						vec_is_parallel(t_vec *a, t_vec *b);
int						vec_is_orthogonal(t_vec *a, t_vec *b);
double					vec_idx(t_vec *a, int idx);
int						vec_is_color_range(t_vec *a);

t_vec					*vec_add_apply(t_vec *a, t_vec *b);
t_vec					*vec_sub_apply(t_vec *a, t_vec *b);
t_vec					*vec_mul_c_apply(t_vec *a, double c);
t_vec					*vec_div_c_apply(t_vec *a, double c);
t_vec					*vec_unit_apply(t_vec *a);

t_vec					*vec_cross_apply(t_vec *a, t_vec *b);
t_vec					*vec_cross_apply_tob(t_vec *a, t_vec *b);
t_vec					*vec_mul_each(t_vec *a, t_vec *b);
t_vec					*vec_mul_each_apply(t_vec *a, t_vec *b);

typedef struct			s_ray
{
	t_vec				*orig;
	t_vec				*dir;
}						t_ray;

t_ray					*ray_new(t_vec *origin, t_vec *direction);
t_vec					*ray_at(t_ray *ray, double t);
void					free_ray(t_ray *ray, int is_orig_free);

typedef struct			s_hit_record
{
	t_vec				*p;
	t_vec				*normal;
	double				t;
	int					is_front_face;
	struct s_material	*mat;
	int					onum;
}						t_hit_record;

t_hit_record			*hit_record_new(void);
void					reset_hit_record(t_hit_record *rec);
void					free_hit_record(t_hit_record *rec);
void					hit_set_normal(t_hit_record *record, t_ray *r);

typedef struct			s_hitlst_info
{
	t_ray				*ray;
	double				t_min;
	double				t_max;
	double				a;
	double				half_b;
	double				c;
	double				root_d;
	t_hit_record		*rec;
	struct s_material	*mat;
	int					onum;
}						t_hitlst_info;

t_hitlst_info			*hitlst_info_new(t_ray *r, double tmax);
t_hitlst_info			*get_hitlst_info(int x, int y, struct s_camera *cam);
void					free_hitlst_info(t_hitlst_info *info,
							int is_ray_ori_free, int is_mat_free);

typedef struct			s_hittable
{
	void				*obj;
	int					obj_type;
	int					(*hit)(void *s, t_ray *r, t_hitlst_info *info,
									t_hit_record *);
	struct s_material	*mat;
	int					onum;
}						t_hittable;

t_hittable				*hittable_create(void *obj, int obj_type,
										struct s_material *mat, int onum);
void					free_hittable(t_hittable *h);

t_list					*rtlst_new(void);
void					hitlst_add(t_list *lst, void *obj, int obj_type,
										struct s_material *mat);
void					free_hitlst(t_list *lst);
int						hitlst_hit(t_list *lst, t_hitlst_info *info);

void					caminfo_lst_add(struct s_rt *rt, t_vec *from,
											t_vec *at, double fov);
void					camlst_add(struct s_rt *rt, t_list *camlst,
									struct s_cam_info *info);
void					free_camlst(t_list *lst);
void					free_caminfolst(t_list *lst);

typedef struct			s_camera
{
	t_img_data			*data;
	double				aspect_ratio;
	t_vec				*origin;
	t_vec				*lower_left_corner;
	t_vec				*horizontal;
	t_vec				*vertical;
}						t_camera;

t_camera				*camera_new(double aspect_ratio);
t_camera				*camera_locate_new(t_vec *lookfrom, t_vec *lookat,
											double aspect_ratio, double fov);
t_ray					*camera_get_ray(t_camera *cam, double u, double v);
void					free_camera(t_camera *cam);

typedef struct			s_material_info
{
	t_vec				*attenuation;
	t_ray				*scattered;
}						t_material_info;

typedef struct			s_material
{
	int					(*scatter)(struct s_material *mat, t_ray *ray_in,
									t_hit_record *rec, t_material_info *info);
	int					mat_type;
	t_vec				*color;
	t_vec				*amb;
	double				fuzz;
}						t_material;

t_material_info			*material_info_new(void);
void					free_material_info(t_material_info *info);
t_material				*material_new(int mat_type, t_vec *color);
t_material				*material_dup(t_material *mat);
void					free_material(t_material *mat);

typedef struct			s_thread_info
{
	t_camera			*cam;
	t_list				*hitlst;
	t_list				*lightlst;
	int					tnum;
}						t_thread_info;

t_thread_info			*tinfo_new(t_camera *cam, struct s_rt *rt, int tnum);
int						tinfo_get_step(t_thread_info *info);
int						tinfo_get_y_init_value(t_thread_info *info);

typedef struct			s_rt
{
	void				*mlx;
	int					width;
	int					height;
	double				aspect_ratio;
	t_list				*camlst;
	t_list				*lightlst;
	t_list				*hitlst;
	t_vec				*amb_light;
}						t_rt;

typedef struct			s_cam_info
{
	t_vec				*from;
	t_vec				*at;
	double				fov;
}						t_cam_info;

typedef struct			s_light
{
	t_vec				*loc;
	double				bright;
	t_vec				*color;
}						t_light;

t_light					*light_new(t_vec *loc, double bright, t_vec *color);
void					free_light(t_light *l);
void					light_hit(t_light *l, t_list *hitlst, t_vec *color,
										struct s_light_hit_info *info);

void					lightlst_add(t_rt *rt, t_vec *loc,
										double bright, t_vec *color);
void					free_lightlst(t_list *lst);
t_vec					*lightlst_hit(t_list *lightlst, t_list *hitlst,
										struct s_light_hit_info *info);

typedef struct			s_light_hit_info
{
	t_vec				*to;
	t_vec				*normal;
	t_ray				*r;
	int					onum;

}						t_light_hit_info;

t_light_hit_info		*lhit_info_new(t_vec *to, t_vec *normal,
										t_ray *r, int onum);
void					free_lhit_info(t_light_hit_info *info);

#endif
