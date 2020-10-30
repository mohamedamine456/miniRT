/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:58:54 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/30 11:34:14 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "structs.h"

/*
** read_scene.c prototypes
*/

t_scene						read_scene_file(char *file_name);
int							read_data(char *line, t_scene *scene,
		t_read_scene_data rs_data);
int							read_data2(char **table, t_object *object);
t_vector					chaine_to_vector(char *str);
void						ft_free_table(char **table);

/*
** apply_scene.c prototypes
*/

void						apply_scene(t_scene scene, t_data_generate dg,
		char *img_add);
t_vector					generate_direction(t_scene scene, int x, int y);
int							generate_direction_finish(t_scene scene,
		t_vector *direction, int x, int y);

/*
** additional_fonctions.c prototypes
*/

t_window					set_new_window(t_resolution resol, char *name);
t_data_generate				dg_initialize(t_camera *cam);
t_object					*object_init();
t_object					*ft_objlast(t_object *object);
t_camera					*cam_init();
t_camera					*ft_camlast(t_camera *cam);
t_light						*light_init();
t_light						*ft_lightlast(t_light *lum);
t_vector					apply_rotation(t_vector direction, int key,
		t_camera *cam);
t_calculate_color_data		initialize_color_data(t_ambiante amb);

/*
** vector.c prototypes
*/

t_vector					vec_initialize(float x, float y, float z);
t_vector					vec_plus(t_vector v1, t_vector v2);
t_vector					vec_minus(t_vector v1, t_vector v2);
t_vector					vec_multiple_n(float t, t_vector v);
float						vec_dot(t_vector v1, t_vector v2);
float						vec_normalize(t_vector *v);
t_vector					ray_calculate(t_ray r, float t);
t_vector					vec_cross(t_vector vec1, t_vector vec2);
float						vec_lenght(t_vector v);
int							vec_compare(t_vector vec, t_vector a, t_vector b);

/*
** ray.c prototypes
*/

t_vector					color_generate(t_ray ray, t_scene scene);
t_hited						initialize_hited();

/*
** sphere.c prototypes
*/

int							hit_sphere(t_ray r, t_object *sp, t_hited *hited);
int							solve_sphere(t_ray ray, t_object *sphere,
		t_sphere_data *data);
void						verify_sphere(t_object *obj);

/*
** plan.c prototypes
*/

int							hit_plan(t_object *plan, t_ray ray, t_hited *hited);
void						verify_plane(t_object *obj);

/*
** triangle.c prototypes
*/

int							hit_triangle(t_object *tr, t_ray ray,
		t_hited *hited);
int							solve_triangle(t_ray ray, t_object *tr,
		t_triangle_data *data);
void						verify_triangle(t_object *obj);

/*
** cylindre.c prototypes
*/

int							hit_cylindre(t_object *cyl, t_ray ray,
		t_hited *hited);
int							solve_cylindre(t_ray ray, t_object *cyl,
		t_cylindre_data *data);
t_cylindre_data				cylindre_data_initialize();
void						verify_cylindre(t_object *obj);

/*
** square.c prototypes
*/

int							hit_square(t_object *square, t_ray ray,
		t_hited *hited);
int							solve_square(t_ray ray, t_object *square,
		t_square_data *data);
void						verify_square(t_object *obj);

/*
** color.c prototypes
*/

t_vector					set_to_range(t_vector col);
t_vector					calculate_color(t_hited hited, t_object *obj,
		t_scene scene);
int							calculate_shadow(t_hited hited, t_object *obj,
		t_light *lum);
t_hited						calculate_shadow_helper(t_hited hited,
		t_object *object, t_light *light, t_ray shad_ray);
void						calculate_color_helper(t_calculate_color_data
		*cc_data, t_hited hited, t_light *lum);

/*
** keys_events.c prototypes
*/

int							key_generate(int key, t_scene *scene);
void						key_generate_second(int key, t_scene *scene);
void						generate_selected_item(int key, t_scene *scene);
void						camera_rotation(t_scene scene, t_data_generate dg,
		int key);

/*
** read_camera.c prototypes
*/

void						read_cam(char **table, t_camera *cam);
t_resolution				read_resolution(char **table);
t_ambiante					read_ambiante(char **table);
void						read_light(char **table, t_light *light);
void						set_axe_camera(t_camera *cam);

/*
** read_objects.c prototypes
*/

void						read_sphere(char **table, t_object *object);
void						read_plane(char **table, t_object *object);
void						read_square(char **table, t_object *object);
void						read_cylindre(char **table, t_object *object);
void						read_triangle(char **table, t_object *object);

/*
** translate.c prototypes
*/

void						translate_vec(t_object *object, t_light *light,
		int key, t_scene scene);
void						translate_vec_light_cam(t_light *light,
		t_vector *vt, t_scene scene);
t_vector					calculate_trans_vec(int key);
void						rotation_vec(int key, t_object *object,
		t_scene scene);

/*
** error_manage.x prototypes
*/

void						error_manage(t_scene scene);
void						verify_objects(t_object *object);
void						verify_lights(t_light *light);
void						verify_cameras(t_camera *camera);
void						ft_perror(char *s);

/*
**main.c prototypes
*/

int							close_window(int key, t_scene *scene);

/*
**	bmp_file_save.c prototypes
*/

void						save_bmp_file(t_scene scene);
t_image_header				initialize_image_header(t_resolution resol);
char						*reverse_image_file(char *buff, t_image_header ih);
#endif
