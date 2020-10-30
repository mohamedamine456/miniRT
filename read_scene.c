/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:21:52 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/30 14:51:47 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene			read_scene_file(char *file_name)
{
	int					fd;
	char				*line;
	t_read_scene_data	rs_data;
	t_scene				scene;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_perror("file Does not exist");
	scene.obj = object_init();
	rs_data.obj = scene.obj;
	scene.cam = cam_init();
	rs_data.cam = scene.cam;
	scene.light = light_init();
	rs_data.light = scene.light;
	while (get_next_line(fd, &line))
		if (ft_strcmp(line, ""))
		{
			read_data(line, &scene, rs_data);
			free(line);
		}
	if (ft_strcmp(line, ""))
		read_data(line, &scene, rs_data);
	free(line);
	return (scene);
}

int				read_data(char *line, t_scene *scene,
		t_read_scene_data rs_data)
{
	char	**table;

	table = ft_split(line, ' ');
	if (table[0][0] == 'R')
		scene->resol = read_resolution(table);
	if (table[0][0] == 'A')
		scene->amb = read_ambiante(table);
	if (table[0][0] == 'c' && table[0][1] != 'y')
		read_cam(table, rs_data.cam);
	if (table[0][0] == 'l')
		read_light(table, rs_data.light);
	read_data2(table, rs_data.obj);
	ft_free_table(table);
	return (0);
}

int				read_data2(char **table, t_object *object)
{
	if (table[0][0] == 's' && table[0][1] == 'p')
		read_sphere(table, object);
	if (table[0][0] == 'p' && table[0][1] == 'l')
		read_plane(table, object);
	if (table[0][0] == 's' && table[0][1] == 'q')
		read_square(table, object);
	if (table[0][0] == 'c' && table[0][1] == 'y')
		read_cylindre(table, object);
	if (table[0][0] == 't' && table[0][1] == 'r' && table[0][2] != 'a')
		read_triangle(table, object);
	return (0);
}

t_vector		chaine_to_vector(char *str)
{
	t_vector	vec;
	char		**table;

	table = ft_split(str, ',');
	vec.x = ft_atof(table[0] ? table[0] : "");
	vec.y = ft_atof(table[1] ? table[1] : "");
	vec.z = ft_atof(table[2] ? table[2] : "");
	ft_free_table(table);
	return (vec);
}

void			ft_free_table(char **table)
{
	int i;

	i = 0;
	if (table != NULL)
	{
		while (table[i] != NULL)
		{
			free(table[i]);
			i++;
		}
		free(table);
	}
}
