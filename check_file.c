/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:17:10 by mlachheb          #+#    #+#             */
/*   Updated: 2020/11/03 18:50:49 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			check_file(char *file_name)
{
	int				fd;
	char			*line;
	t_data_check	data;
	int				len;

	len = ft_strlen(file_name);
	line = NULL;
	data = initialize_data_check();
	if (len < 3 || file_name[len - 1] != 't' ||
			file_name[len - 2] != 'r' || file_name[len - 3] != '.')
		ft_perror("file extension must be .rt");
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_perror("ERROR: file Does not exist");
	while (get_next_line(fd, &line))
	{
		if (ft_strcmp(line, ""))
			check_data(line, &data);
		free(line);
	}
	if (ft_strcmp(line, ""))
		check_data(line, &data);
	last_data_check(data);
	free(line);
}

void			check_data(char *line, t_data_check *data)
{
	char	**table;

	table = ft_split(line, ' ');
	if (!ft_strcmp(table[0], "R") && table[1] != NULL && table[2] != NULL
			&& table[3] == NULL)
	{
		if (data->resol == 1)
			ft_perror("the Resolution must be just one time");
		if (data->resol == 0)
			data->resol = 1;
	}
	if (!ft_strcmp(table[0], "A") && table[1] != NULL && table[2] != NULL
			&& table[3] == NULL)
	{
		if (data->ambiante == 1)
			ft_perror("the Ambiante must be just one time");
		if (data->ambiante == 0)
			data->ambiante = 1;
	}
	if (!ft_strcmp(table[0], "c") && table[1] != NULL && table[2] != NULL
			&& table[3] != NULL && table[4] == NULL)
		if (data->camera != 1)
			data->camera = 1;
	ft_free_table(table);
}

void			last_data_check(t_data_check data)
{
	if (data.resol == 0)
		ft_perror("1:you must declare a Resolution for the scene\
				\n2:you must declare it as required");
	if (data.ambiante == 0)
		ft_perror("1:you must declare a Ambiante for the scene\
				\n2:you must declare it as required");
	if (data.camera == 0)
		ft_perror("1:you must declare at least one camera for the scene\
				\n2:you must declare it as required");
}

t_data_check	initialize_data_check(void)
{
	t_data_check data;

	data.resol = 0;
	data.ambiante = 0;
	return (data);
}
