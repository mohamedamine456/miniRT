/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_file_save.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:27:23 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/30 17:35:13 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void				save_bmp_file(t_scene scene)
{
	t_image_header	ih;
	int				fd;
	char			*buff;
	t_data_generate	dg;
	char			header[54];

	ih = initialize_image_header(scene.resol);
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 2, &ih.file_size, 4);
	ft_memcpy(header + 10, &ih.ofsset_bits, 4);
	ft_memcpy(header + 14, &ih.bit_size, 4);
	ft_memcpy(header + 18, &ih.width, 4);
	ft_memcpy(header + 22, &ih.height, 4);
	ft_memcpy(header + 26, &ih.bit_planes, 2);
	ft_memcpy(header + 28, &ih.bit_count, 2);
	ft_memcpy(header + 34, &ih.image_size, 4);
	buff = malloc(ih.image_size);
	dg = dg_initialize(scene.cam);
	apply_scene(scene, dg, buff);
	buff = reverse_image_file(buff, ih);
	fd = open("testtt.bmp", O_CREAT | O_RDWR);
	write(fd, header, 54);
	write(fd, buff, ih.image_size);
	close(fd);
	free(buff);
}

t_image_header		initialize_image_header(t_resolution resol)
{
	t_image_header ih;

	ih.width = resol.width;
	ih.height = resol.height;
	ih.bit_count = 32;
	ih.image_size = ih.width * ih.height * 4;
	ih.bit_size = 40;
	ih.ofsset_bits = 54;
	ih.file_size = 54 + ih.image_size;
	ih.bit_planes = 1;
	return (ih);
}

char				*reverse_image_file(char *buff, t_image_header ih)
{
	int		row;
	int		col;

	row = 0;
	while (row < ih.height / 2)
	{
		col = 0;
		while (col < ih.width)
		{
			swap_for_file(buff, ih, row, col);
			col++;
		}
		row++;
	}
	return (buff);
}

void				swap_for_file(char *buff, t_image_header ih,
		int row, int col)
{
	int		pos1;
	int		pos2;
	char	c;

	pos1 = (row * ih.width + col) * 4;
	pos2 = ((ih.height - 1 - row) * ih.width + col) * 4;
	c = buff[pos1 + 2];
	buff[pos1 + 2] = buff[pos2 + 2];
	buff[pos2 + 2] = c;
	c = buff[pos1 + 1];
	buff[pos1 + 1] = buff[pos2 + 1];
	buff[pos2 + 1] = c;
	c = buff[pos1];
	buff[pos1] = buff[pos2];
	buff[pos2] = c;
}
