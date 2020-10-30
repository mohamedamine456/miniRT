/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:59:30 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/30 11:52:28 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		read_sphere(char **table, t_object *object)
{
	if (table[1] == NULL || table[2] == NULL || table[3] == NULL)
		ft_perror("must enter all data required for the Sphere");
	if (object->shape == 0 && object->next == NULL)
	{
		object->id = 1;
		object->shape = 's';
		object->center = chaine_to_vector(table[1] ? table[1] : "");
		object->diameter = ft_atof(table[2] ? table[2] : "");
		object->color = chaine_to_vector(table[3] ? table[3] : "");
	}
	else
	{
		object = ft_objlast(object);
		object->next = object_init();
		object->next->id = object->id + 1;
		object = object->next;
		object->shape = 's';
		object->center = chaine_to_vector(table[1] ? table[1] : "");
		object->diameter = ft_atof(table[2] ? table[2] : "");
		object->color = chaine_to_vector(table[3] ? table[3] : "");
	}
}

void		read_plane(char **table, t_object *object)
{
	if (table[1] == NULL || table[2] == NULL || table[3] == NULL)
		ft_perror("must enter all data required for the Plane");
	if (object->shape == 0 && object->next == NULL)
	{
		object->id = 1;
		object->shape = 'p';
		object->point = chaine_to_vector(table[1] ? table[1] : "");
		object->normal = chaine_to_vector(table[2] ? table[2] : "");
		object->color = chaine_to_vector(table[3] ? table[3] : "");
	}
	else
	{
		object = ft_objlast(object);
		object->next = object_init();
		object->next->id = object->id + 1;
		object = object->next;
		object->shape = 'p';
		object->point = chaine_to_vector(table[1] ? table[1] : "");
		object->normal = chaine_to_vector(table[2] ? table[2] : "");
		object->color = chaine_to_vector(table[3] ? table[3] : "");
	}
}

void		read_square(char **table, t_object *object)
{
	if (table[1] == NULL || table[2] == NULL ||
			table[3] == NULL || table[4] == NULL)
		ft_perror("must enter all data required for the Square");
	if (object->shape == 0 && object->next == NULL)
	{
		object->id = 1;
		object->shape = 'q';
		object->center = chaine_to_vector(table[1] ? table[1] : "");
		object->normal = chaine_to_vector(table[2] ? table[2] : "");
		object->heigth = ft_atof(table[3] ? table[3] : "");
		object->color = chaine_to_vector(table[4] ? table[4] : "");
	}
	else
	{
		object = ft_objlast(object);
		object->next = object_init();
		object->next->id = object->id + 1;
		object = object->next;
		object->shape = 'q';
		object->center = chaine_to_vector(table[1] ? table[1] : "");
		object->normal = chaine_to_vector(table[2] ? table[2] : "");
		object->heigth = ft_atof(table[3] ? table[3] : "");
		object->color = chaine_to_vector(table[4] ? table[4] : "");
	}
}

void		read_cylindre(char **table, t_object *object)
{
	if (table[1] == NULL || table[2] == NULL || table[3] == NULL
			|| table[4] == NULL || table[5] == NULL)
		ft_perror("must enter all data required for the Cylinder");
	if (object->shape == 0 && object->next == NULL)
	{
		object->id = 1;
		object->shape = 'c';
		object->center = chaine_to_vector(table[1] ? table[1] : "");
		object->normal = chaine_to_vector(table[2] ? table[2] : "");
		object->diameter = ft_atof(table[3] ? table[3] : "");
		object->heigth = ft_atof(table[4] ? table[4] : "");
		object->color = chaine_to_vector(table[5] ? table[5] : "");
	}
	else
	{
		object = ft_objlast(object);
		object->next = object_init();
		object->next->id = object->id + 1;
		object = object->next;
		object->shape = 'c';
		object->center = chaine_to_vector(table[1] ? table[1] : "");
		object->normal = chaine_to_vector(table[2] ? table[2] : "");
		object->color = chaine_to_vector(table[3] ? table[3] : "");
		object->diameter = ft_atof(table[4] ? table[4] : "");
		object->heigth = ft_atof(table[5] ? table[5] : "");
	}
}

void		read_triangle(char **table, t_object *object)
{
	if (table[1] == NULL || table[2] == NULL || table[3] == NULL ||
			table[4] == NULL)
		ft_perror("must enter all data required for the Triangle");
	if (object->shape == 0 && object->next == NULL)
	{
		object->id = 1;
		object->shape = 't';
		object->first_point = chaine_to_vector(table[1] ? table[1] : "");
		object->second_point = chaine_to_vector(table[2] ? table[2] : "");
		object->third_point = chaine_to_vector(table[3] ? table[3] : "");
		object->color = chaine_to_vector(table[4] ? table[4] : "");
	}
	else
	{
		object = ft_objlast(object);
		object->next = object_init();
		object->next->id = object->id + 1;
		object = object->next;
		object->shape = 't';
		object->first_point = chaine_to_vector(table[1] ? table[1] : "");
		object->second_point = chaine_to_vector(table[2] ? table[2] : "");
		object->third_point = chaine_to_vector(table[3] ? table[3] : "");
		object->color = chaine_to_vector(table[4] ? table[4] : "");
	}
}
