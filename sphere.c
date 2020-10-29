/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:12:08 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/29 13:14:01 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		hit_sphere(t_ray ray, t_object *sp, t_hited *hited)
{
	t_sphere_data	data;
	int				temp;

	temp = solve_sphere(ray, sp, &data);
	if (temp == 0)
		return (0);
	if (data.t >= 1e-6 && data.t < hited->t)
	{
		hited->t = data.t;
		hited->p = ray_calculate(ray, hited->t);
		hited->normal = vec_minus(hited->p, sp->center);
		vec_normalize(&(*hited).normal);
		hited->color = sp->color;
		hited->obj = sp->id;
		return (1);
	}
	return (0);
}

int		solve_sphere(t_ray ray, t_object *sphere, t_sphere_data *data)
{
	t_sec_degre_equa	res;

	data->oc = vec_minus(ray.origin, sphere->center);
	res.a = 1;
	res.b = 2 * vec_dot(data->oc, ray.direction);
	res.c = vec_dot(data->oc, data->oc) - pow((sphere->diameter / 2), 2);
	res.delta = (res.b * res.b) - (4 * res.c);
	if (res.delta < 0)
		return (0);
	data->t1 = (-res.b + sqrt(res.delta)) / 2;
	data->t2 = (-res.b - sqrt(res.delta)) / 2;
	if (data->t1 < data->t2)
		data->t = data->t1;
	if (data->t2 < data->t1)
		data->t = data->t2;
	return (1);
}

void	verify_sphere(t_object *obj)
{
	if (obj->diameter < 0)
		ft_perror("the sphere diameter must be over than 0");
	if (!vec_compare(obj->normal, vec_initialize(-1, -1, -1),
				vec_initialize(1, 1, 1)))
		ft_perror("the sphere normal must be between -1 and 1");
	if (!vec_compare(obj->color, vec_initialize(0, 0, 0),
				vec_initialize(255, 255, 255)))
		ft_perror("the sphere colors must be between 0 and 255");
}
