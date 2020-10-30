/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:14:29 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/30 14:13:31 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		hit_square(t_object *square, t_ray ray, t_hited *hited)
{
	t_square_data	data;
	float			var;

	var = solve_square(ray, square, &data);
	if (var == 0)
		return (0);
	if (data.t >= 1e-6 && data.t < hited->t && data.proj1 <= square->heigth
			/ 2 && data.proj1 > -square->heigth / 2 && data.proj2 <=
			square->heigth / 2 && data.proj2 > -square->heigth / 2)
	{
		hited->t = data.t;
		hited->p = data.p;
		hited->normal = vec_multiple_n(-1, square->normal);
		vec_normalize(&(*hited).normal);
		hited->color = square->color;
		hited->obj = square->id;
		return (1);
	}
	return (0);
}

int		solve_square(t_ray ray, t_object *square, t_square_data *data)
{
	data->up_default = vec_initialize(0, 1, 0);
	if (square->normal.y == 1 || square->normal.y)
		data->up_default = vec_initialize(1, 0, 0);
	data->right = vec_cross(data->up_default, square->normal);
	vec_normalize(&(data->right));
	data->up = vec_cross(data->right, square->normal);
	vec_normalize(&(data->up));
	data->dn = vec_dot(ray.direction, square->normal);
	if (data->dn == 0)
		return (0);
	data->oc = vec_minus(ray.origin, square->center);
	data->t = -vec_dot(data->oc, square->normal) / data->dn;
	if (data->t < 0)
		return (0);
	data->p = ray_calculate(ray, data->t);
	data->rec = vec_minus(data->p, square->center);
	data->proj1 = vec_dot(data->rec, data->up);
	data->proj2 = vec_dot(data->rec, data->right);
	return (1);
}

void	verify_square(t_object *obj)
{
	if (!vec_compare(obj->normal, vec_initialize(-1, -1, -1),
				vec_initialize(1, 1, 1)))
		ft_perror("the square normal must be between -1 and 1");
	if (!vec_compare(obj->color, vec_initialize(0, 0, 0),
				vec_initialize(255, 255, 255)))
		ft_perror("the square colors must be between 0 and 255");
	if (obj->heigth < 0)
		ft_perror("the square height must be over than 0");
}
