/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:55:57 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/31 19:43:45 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void					read_cam(char **table, t_camera *cam)
{
	t_camera	*new_cam;

	if (table[1] == NULL || table[2] == NULL || table[3] == NULL)
		ft_perror("must enter all data required for the Camera");
	if (cam->fov == -1 && cam->next == NULL && cam->previous == NULL)
	{
		cam->origin = chaine_to_vector(table[1] ? table[1] : "");
		cam->normal = chaine_to_vector(table[2] ? table[2] : "");
		cam->fov = ft_atof(table[3] ? table[3] : "");
		set_axe_camera(cam);
	}
	else
	{
		new_cam = cam_init();
		new_cam->origin = chaine_to_vector(table[1] ? table[1] : "");
		new_cam->normal = chaine_to_vector(table[2] ? table[2] : "");
		new_cam->fov = ft_atof(table[3] ? table[3] : "");
		set_axe_camera(new_cam);
		cam = ft_camlast(cam);
		new_cam->previous = cam;
		cam->next = new_cam;
		cam = cam->next;
	}
}

t_resolution			read_resolution(char **table)
{
	t_resolution resol;

	if (table[1] == NULL || table[2] == NULL)
		ft_perror("must enter all data required for the Resolution");
	resol.width = ft_atof(table[1] ? table[1] : "");
	resol.height = ft_atof(table[2] ? table[2] : "");
	if (resol.width > 5120 / 2)
		resol.width = 5120 / 2;
	if (resol.height > 2880 / 2)
		resol.height = 2880 / 2;
	return (resol);
}

t_ambiante				read_ambiante(char **table)
{
	t_ambiante amb;

	if (table[1] == NULL || table[2] == NULL)
		ft_perror("must enter all data required for the Ambiante");
	amb.ambiante = ft_atof(table[1] ? table[1] : "");
	amb.color = chaine_to_vector(table[2] ? table[2] : "");
	return (amb);
}

void					read_light(char **table, t_light *light)
{
	if (table[1] == NULL || table[2] == NULL || table[3] == NULL)
		ft_perror("must enter all data required for the Light");
	if (light->intensite == -1 && light->next == NULL)
	{
		light->origin = chaine_to_vector(table[1] ? table[1] : "");
		light->intensite = ft_atof(table[2] ? table[2] : "");
		light->color = chaine_to_vector(table[3] ? table[3] : "");
	}
	else
	{
		light = ft_lightlast(light);
		light->next = light_init();
		light = light->next;
		light->origin = chaine_to_vector(table[1] ? table[1] : "");
		light->intensite = ft_atof(table[2] ? table[2] : "");
		light->color = chaine_to_vector(table[3] ? table[3] : "");
	}
}

void					set_axe_camera(t_camera *cam)
{
	if ((cam->normal.x == 1 || cam->normal.x == -1) &&
			cam->normal.y == 0 && cam->normal.z == 0)
		cam->axe = 'x';
	else if (cam->normal.x == 0 && (cam->normal.y == 1 ||
				cam->normal.y == -1) && cam->normal.z == 0)
		cam->axe = 'y';
	else if (cam->normal.x == 0 && cam->normal.y == 0 &&
			(cam->normal.z == 1 || cam->normal.z == -1))
		cam->axe = 'z';
	else
		ft_perror("the camera normal must be one axe with a value of 1 or -1");
}
