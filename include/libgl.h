/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:43:22 by msidqi            #+#    #+#             */
/*   Updated: 2019/05/10 05:31:38 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGL_H
# define LIBGL_H

# include <mlx.h>
# include "libft.h"
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <time.h>
# include <stdio.h>

# define RIGHT_ARROW 124
# define LEFT_ARROW 123
# define UP_ARROW 126
# define DOWN_ARROW 125
# define ZOOM_OUT 78
# define ZOOM_IN 69
# define SPACE 49
# define LEFT_CLICK 1
# define RIGHT_CLICK 2
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define NUM_LOCK_9 92
# define NUM_LOCK_8 91
# define NUM_LOCK_7 89
# define NUM_LOCK_6 88
# define NUM_LOCK_5 87
# define NUM_LOCK_4 86
# define NUM_LOCK_3 85
# define NUM_LOCK_2 84
# define NUM_LOCK_1 83
# define NUM_LOCK_0 82
# define MOUSE_PRESS_CODE 4
# define MOUSE_MOVE_CODE 6
# define KEY_PRESS_CODE 2
# define RED_BUTTON_CODE 17
# define MAX_ITER 30
# define ABS(Value) (Value >= 0) ? (Value) : -(Value)
# define VERTEX 0
# define VECTOR 1
# define DIRECTION 2
# define MATRIX 3
# define TRANSLATION_MATRIX 0
# define ROTATION_MATRIX 1
# define SCALING_MATRIX 2
# define X 0
# define Y 1
# define Z 2
# define W 3
# define NEAR 1e-6
# define FAR 1e30
# define POINT_LIGHT 0
# define DIRECTIONAL_LIGHT 1
# define SPOT_LIGHT 2
# define AREA_LIGHT 3
# define SPHERE 1
# define PLANE 2
# define CONE 4
# define CYLINDRE 8
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0xFF
# define BLACK 0x0
# define WHITE 0xFFFFFF

typedef struct		t_vector2
{
	double			x;
	double			y;
}					t_vector2;

typedef struct		s_vector3
{
	double			x;
	double			y;
	double			z;
}					t_vector3;

typedef struct		s_matrix
{
	unsigned int	cols;
	unsigned int	rows;
	double			**v;
}					t_matrix;

typedef struct		s_vector4
{
	short			type;
	double			v[4];
}					t_vector4;


/*
** Homogenous Coordinates
**   F U R  T   (Forward/Up/Right/Translation Vector)
** [[1 0 0] 0]
** [[0 1 0] 0]
** [[0 0 1] 0]
** [ 0 0 0  1] 0 Direction Vector 1 Position Vector
** FUR == unit vectors describing object orientation. aka vector basis
**
*/
typedef struct		s_matrix4
{
	short			type;
	double			v[4][4];
}					t_matrix4;

typedef struct		s_startend
{
	t_vector2			start;
	t_vector2			end;
}					t_startend;

typedef struct		s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_color;

typedef enum		e_bool
{
	false, true
}					t_bool;
 
typedef struct		s_ray // P(t) = origin + t * dir
{
	t_vector4		origin; // vector to origin point
	t_vector4		dir; // direction vector
	double			t; // distance
	t_vector4		intersect_point;
}					t_ray;

typedef	struct		s_light_source
{
	float	i_r; // intensity rgb(1.0, 0.0, 0.0) == red
	float	i_g;
	float	i_b;
	short			type;
	double			size;
	t_vector4		origin;
}					t_light_source;

typedef struct		s_camera
{
	t_vector4		to;
	t_vector4		position;
	t_vector2		mousepos;
	double			field_of_view;
	double			size;
	double			l;
	double			bigl;
	double			focal_length;
	t_vector4		up;
	t_vector4		forward;
	t_vector4		left;
	t_matrix4		mx;
}					t_camera;

typedef	struct		s_data
{
	t_light_source	light;
	t_list			*scene;
	t_camera		cam;
	t_vector4		worldpos;
	t_color			color;
	t_startend		thread_range;
	unsigned int	winwidth;
	unsigned int	winheight;
	void			*mlx;
	void			*win;
	void			*img_ptr;
	int				*image;
	double			zoom;
	double			movex;
	double			movey;
	double			movez;
	int				endian;
	int				size_line;
	int				bpp;
}					t_data;

typedef	struct		s_sphere
{
	short			type;
	float			diffuse;
	float			specular;
	unsigned int	color;
	double			radius;
	t_vector4		center;
}					t_sphere;

typedef	struct		s_plane
{
	unsigned int	color;
	t_vector4		normal;
	t_vector4		point;
}					t_plane;

typedef	struct		s_obj // list to store all objects in a scene
{
	void			*obj;
	short			type;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_palette
{
	int				palette[8];
	int				palette_choice;
}					t_palette;

int					ft_window_setup(t_data *data, char *win_name,
											int winheight, int winwidth);
int					ft_image_setup(t_data *data);
void				ft_image_fill(t_data *data, int x, int y, int color);
double				lerp(double x1, double x2, double lerp);
double				ft_get_world_pos(double screen_coord,
								double widthheight, double zoom);
void				ft_refresh_image(t_data *data);
void				ft_mlx_hooks(t_data *data, t_bool ismove);
int					no_event_mouse_move(int x, int y, t_data *data);
int					key_press(int key_code, t_data *data);
int					mouse_press(int button, int x, int y, t_data *data);
int					mouse_move(int x, int y, t_data *data);
void				ft_multi_thread(t_data *data, int n_threads, void *(*f)(void *));
void				drawline(t_data *data, int startline, int nlines, int color);
void				drawnsquares(t_data *data, unsigned int onedlen);
void				connect_dots(t_data *data, t_vector2 a, t_vector2 b, int color);
void				vec2_init(t_vector2 *a, double x, double y);
void				vec3_init(t_vector3 *a, double x, double y, double z);
t_vector2			vec2_add(t_vector2 a, t_vector2 b);
t_vector3			vec3_add(t_vector3 a, t_vector3 b);
t_vector2			vec2_sub(t_vector2 a, t_vector2 b);
t_vector3			vec3_sub(t_vector3 a, t_vector3 b);
t_vector2			vec2_scalar_multi(t_vector2 a, double factor);
t_vector3			vec3_scalar_multi(t_vector3 a, double factor);
double				vec2_magnitude(t_vector2 a);
double				vec3_magnitude(t_vector3 a);
double				vec2_magnitude_cmp(t_vector2 a, t_vector2 b);
double				vec3_magnitude_cmp(t_vector3 a, t_vector3 b);
t_vector2			vec2_normalize(t_vector2 a);
t_vector3			vec3_normalize(t_vector3 a);
double				vec2_dot_product(t_vector2 a, t_vector2 b);
double				vec3_dot_product(t_vector3 a, t_vector3 b);
t_vector2			vec2_rotate_byangle(t_vector2 a, double angle);
t_vector2			vec2_rotate_byaxis(t_vector2 a, t_vector2 x_axis, t_vector2 y_axis);
t_matrix			*ft_create_matrix(unsigned int rows, unsigned int cols);
t_matrix4			ft_create_matrix4();
int					ft_destroy_matrix(t_matrix *mat);
void				ft_putmatrix(t_matrix *mat);
void				ft_putmatrix4(t_matrix4 *mat);
t_matrix4			ft_get_translation_matrix4(double x, double y, double z);
t_vector4			ft_create_vector4(double x, double y, double z, double w) ;
void				ft_putvector4(t_vector4 *vec);
t_vector4			ft_matrix_x_vector(t_matrix4 *mat, t_vector4 *vec);
void				ft_printvector4(t_vector4 *vec);//don't forget to remove this
t_vector4		    ft_vec4_sub(t_vector4 *vec1, t_vector4 *vec2);
t_vector4    		ft_vec4_normalize(t_vector4 *a);
double    			ft_vec4_magnitude(t_vector4 *a);
double				ft_vec4_dot_product(t_vector4 *a, t_vector4 *b);
void				ft_draw(t_data *data);
void				ft_printmatrix4(t_matrix4 *mat);
t_vector4 	   		ft_vec4_cross_product(t_vector4 *vec1, t_vector4 *vec2);
t_vector4			ft_vec4_add(t_vector4 *vec1, t_vector4 *vec2);
t_vector4			ft_vec4_scalar(t_vector4 *a, double factor);
int					ft_plane_intersection(t_ray *ray, t_plane *plane);
int					ft_sphere_intersection(t_ray *ray, t_sphere *sphere);
void				ft_camera(t_data *data, t_vector4 position , t_vector4 lookat, double focal_length);
t_ray				ft_get_ray_to_light(t_ray *ray, t_light_source *source);
void				ft_color_rgb_scalar(unsigned int *color, double r, double g, double b);

#endif
