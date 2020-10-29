/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:32:11 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/29 14:59:44 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"

int		main(int argv, char **args)
{
	t_scene		scene;

	scene = read_scene_file("scene1.rt");
	error_manage(scene);
	scene.dg = dg_initialize(scene.cam);
	scene.window = set_new_window(scene.resol, "MiniRT");
	apply_scene(scene, scene.dg, scene.window.img_add);
	mlx_put_image_to_window(scene.window.mlx_ptr, scene.window.win_ptr,
			scene.window.img_ptr, 0, 0);
	if (argv == 2 && !ft_strcmp(args[1], "--save"))
	{
		save_bmp_file(scene);
		close_window(0, &scene);
	}
	mlx_key_hook(scene.window.win_ptr, key_generate, &scene);
	mlx_hook(scene.window.win_ptr, 17, 1L << 2, close_window, &scene);
	mlx_loop(scene.window.mlx_ptr);
	return (0);
}

int		close_window(int key, t_scene *scene)
{
	//key = 0;
	//scene->cam->fov = 0;
	exit(1);
	return (0);
}
