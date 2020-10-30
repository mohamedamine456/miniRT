/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:30:53 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/30 20:41:12 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int					key_generate(int key, t_scene *scene)
{
	if (key == 53)
	{
		mlx_destroy_window(scene->window.mlx_ptr, scene->window.win_ptr);
		exit(1);
	}
	if (key == 124 || key == 123 || key == 126
			|| key == 125 || key == 32 || key == 2)
	{
		mlx_clear_window(scene->window.mlx_ptr, scene->window.win_ptr);
		translate_vec(scene->obj, scene->light, key, *scene);
		scene->dg = dg_initialize(scene->cam);
		apply_scene(*scene, scene->dg, scene->window.img_add);
		mlx_put_image_to_window(scene->window.mlx_ptr,
				scene->window.win_ptr, scene->window.img_ptr, 0, 0);
	}
	key_generate_cont(key, scene);
	key_generate_second(key, scene);
	return (0);
}

void				key_generate_cont(int key, t_scene *scene)
{
	if (key == 7 || key == 16 || key == 6)
	{
		if (scene->selected == 'q' || scene->selected == 'c' ||
				scene->selected == 'p')
		{
			mlx_clear_window(scene->window.mlx_ptr, scene->window.win_ptr);
			scene->dg = dg_initialize(scene->cam);
			rotation_vec(key, scene->obj, *scene);
			apply_scene(*scene, scene->dg, scene->window.img_add);
			mlx_put_image_to_window(scene->window.mlx_ptr,
					scene->window.win_ptr, scene->window.img_ptr, 0, 0);
		}
		if (scene->selected == 'a')
			camera_rotation(*scene, scene->dg, key);
	}
	if (key == 1 || key == 14 || key == 17 ||
			key == 12 || key == 15 || key == 8 || key == 37)
		generate_selected_item(key, scene);
}

void				key_generate_second(int key, t_scene *scene)
{
	if (key == 45)
	{
		if (scene->cam->next != NULL)
		{
			mlx_clear_window(scene->window.mlx_ptr, scene->window.win_ptr);
			scene->cam = scene->cam->next;
			scene->dg = dg_initialize(scene->cam);
			apply_scene(*scene, scene->dg, scene->window.img_add);
			mlx_put_image_to_window(scene->window.mlx_ptr,
					scene->window.win_ptr, scene->window.img_ptr, 0, 0);
		}
	}
	if (key == 35)
	{
		if (scene->cam->previous != NULL)
		{
			mlx_clear_window(scene->window.mlx_ptr, scene->window.win_ptr);
			scene->cam = scene->cam->previous;
			scene->dg = dg_initialize(scene->cam);
			apply_scene(*scene, scene->dg, scene->window.img_add);
			mlx_put_image_to_window(scene->window.mlx_ptr,
					scene->window.win_ptr, scene->window.img_ptr, 0, 0);
		}
	}
}

void				generate_selected_item(int key, t_scene *scene)
{
	if (key == 1)
		scene->selected = 's';
	if (key == 14)
		scene->selected = 'p';
	if (key == 17)
		scene->selected = 't';
	if (key == 12)
		scene->selected = 'q';
	if (key == 15)
		scene->selected = 'c';
	if (key == 8)
		scene->selected = 'a';
	if (key == 37)
		scene->selected = 'l';
}

void				camera_rotation(t_scene scene, t_data_generate dg, int key)
{
	if (scene.cam->axe != 'x' && scene.cam->axe != 'y')
	{
		mlx_clear_window(scene.window.mlx_ptr, scene.window.win_ptr);
		dg = dg_initialize(scene.cam);
		scene.cam->rotation_angle += M_PI / 12;
		while (dg.x < scene.resol.width)
		{
			dg.y = 0;
			while (dg.y < scene.resol.height)
			{
				camera_rotation_helper(scene, dg, key);
				dg.y++;
			}
			dg.x++;
		}
		mlx_put_image_to_window(scene.window.mlx_ptr,
				scene.window.win_ptr, scene.window.img_ptr, 0, 0);
	}
}
