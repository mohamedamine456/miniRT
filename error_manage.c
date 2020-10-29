/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:48:16 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/28 13:53:05 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		error_manage(t_scene scene)
{
	if (scene.resol.width < 0 || scene.resol.height < 0)
		ft_perror("resolution over than 0");
	if (scene.amb.ambiante < 0.0 || scene.amb.ambiante > 1.0)
		ft_perror("ambiante coefficient between 0 and 1");
	if (!vec_compare(scene.amb.color, vec_initialize(0, 0, 0),
				vec_initialize(255, 255, 255)))
		ft_perror("the ambiante colors must be between 0 255");
	verify_cameras(scene.cam);
	verify_lights(scene.light);
	verify_objects(scene.obj);
}

void		verify_cameras(t_camera *camera)
{
	t_camera *cam;

	cam = camera;
	while (cam->fov != -1)
	{
		if (cam->fov < 0 || cam->fov > 180)
			ft_perror("camera angle must be between 0 and 180");
		if (!vec_compare(cam->normal, vec_initialize(-1, -1, -1),
					vec_initialize(1, 1, 1)))
			ft_perror("the normal of the camera must be between -1 and 1");
		if (cam->next != NULL)
			cam = cam->next;
		else
			break ;
	}
}

void		verify_lights(t_light *light)
{
	t_light *lum;

	lum = light;
	while (lum->intensite != -1)
	{
		if (lum->intensite < 0.0 || lum->intensite > 1.0)
			ft_perror("the light ratio mast be between 0 and 1");
		if (!vec_compare(lum->color, vec_initialize(0, 0, 0),
					vec_initialize(255, 255, 255)))
			ft_perror("the colors of light must be between 0 and 255");
		if (lum->next != NULL)
			lum = lum->next;
		else
			break ;
	}
}

void		verify_objects(t_object *object)
{
	t_object *obj;

	obj = object;
	while (obj->shape != 0)
	{
		if (obj->shape == 's')
			verify_sphere(obj);
		if (obj->shape == 'p')
			verify_plane(obj);
		if (obj->shape == 't')
			verify_triangle(obj);
		if (obj->shape == 'q')
			verify_square(obj);
		if (obj->shape == 'c')
			verify_cylindre(obj);
		if (obj->next != NULL)
			obj = obj->next;
		else
			break ;
	}
}

void		ft_perror(char *s)
{
	perror(s);
	exit(1);
}
