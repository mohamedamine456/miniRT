/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:16:58 by mlachheb          #+#    #+#             */
/*   Updated: 2020/11/03 18:11:06 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

typedef struct					s_vector
{
	float			x;
	float			y;
	float			z;
}								t_vector;

typedef struct					s_resolution
{
	int				width;
	int				height;
}								t_resolution;

typedef struct					s_ambiante
{
	float			ambiante;
	t_vector		color;
}								t_ambiante;

typedef struct					s_camera
{
	t_vector		origin;
	t_vector		normal;
	float			fov;
	float			rotation_angle;
	char			axe;
	struct s_camera	*next;
	struct s_camera	*previous;
}								t_camera;

typedef struct					s_light
{
	t_vector		origin;
	float			intensite;
	t_vector		color;
	struct s_light	*next;
}								t_light;

typedef struct					s_object
{
	int				selected;
	char			shape;
	int				id;
	t_vector		center;
	float			diameter;
	t_vector		point;
	t_vector		normal;
	float			heigth;
	t_vector		first_point;
	t_vector		second_point;
	t_vector		third_point;
	t_vector		color;
	struct s_object	*next;
}								t_object;

typedef struct					s_ray
{
	t_vector		origin;
	t_vector		direction;
}								t_ray;

typedef struct					s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_add;
	int				bits_pixel;
	int				size_line;
	int				endian;
}								t_window;

typedef struct					s_hited
{
	int				yes;
	t_vector		p;
	t_vector		normal;
	float			t;
	int				obj;
	t_vector		color;
	int				shaded;
	int				rotated;
}								t_hited;

typedef struct					s_data_generate
{
	t_ray			r;
	int				pos;
	int				x;
	int				y;
	t_vector		color;
}								t_data_generate;

typedef struct					s_cylindre_data
{
	float			t;
	float			t1;
	float			t2;
	float			m;
	float			m1;
	float			m2;
	t_vector		oc;
}								t_cylindre_data;

typedef struct					s_sec_degre_equa
{
	float			a;
	float			b;
	float			c;
	float			delta;
}								t_sec_degre_equa;

typedef struct					s_sphere_data
{
	float			t;
	float			t1;
	float			t2;
	t_vector		oc;
}								t_sphere_data;

typedef struct					s_triangle_data
{
	t_vector		edge1;
	t_vector		edge2;
	t_vector		ed2_crs_dir;
	t_vector		org_min_frstpnt;
	t_vector		prev_crs_ed1;
	float			ed1_dot_e2d;
	float			temp;
	float			uniq;
	float			vec_dot;
	float			t;
}								t_triangle_data;

typedef struct					s_square_data
{
	t_vector		oc;
	t_vector		p;
	t_vector		rec;
	t_vector		up_default;
	t_vector		up;
	t_vector		right;
	float			dn;
	float			proj1;
	float			proj2;
	float			t;
}								t_square_data;

typedef struct					s_calculate_color_data
{
	t_vector		diffuse;
	t_vector		specular;
	t_vector		ambient;
	t_vector		intensite;
	t_vector		color;
	t_vector		reflect;
	t_vector		ll;
	float			dot;
}								t_calculate_color_data;

typedef struct					s_read_scene_data
{
	t_object		*obj;
	t_camera		*cam;
	t_light			*light;
}								t_read_scene_data;

typedef struct					s_scene
{
	char			selected;
	t_resolution	resol;
	t_ambiante		amb;
	t_data_generate	dg;
	t_window		window;
	t_camera		*cam;
	t_light			*light;
	t_object		*obj;
}								t_scene;

typedef struct					s_image_header
{
	int				file_size;
	int				ofsset_bits;
	int				width;
	int				height;
	int				bit_planes;
	int				bit_size;
	int				image_size;
	int				bit_count;
}								t_image_header;

typedef struct					s_data_check
{
	int			resol;
	int			ambiante;
	int			camera;
}								t_data_check;

#endif
