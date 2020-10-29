/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:43:54 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/28 13:47:57 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int					hit_cylindre(t_object *cyl, t_ray ray, t_hited *hited)
{
	t_cylindre_data		data;
	int					var;

	data = cylindre_data_initialize();
	var = solve_cylindre(ray, cyl, &data);
	if (var == 0)
		return (0);
	if (data.t == data.t1 && data.t != 0)
		data.m = data.m1;
	if (data.t == data.t2 && data.t != 0)
		data.m = data.m2;
	if (data.t >= 1e-6 && data.t < hited->t)
	{
		hited->t = data.t;
		hited->p = ray_calculate(ray, data.t);
		hited->normal = vec_minus(hited->p, vec_minus(cyl->center,
					vec_multiple_n(data.m, cyl->normal)));
		vec_normalize(&(*hited).normal);
		hited->color = cyl->color;
		hited->obj = cyl->id;
		return (1);
	}
	return (0);
}

int					solve_cylindre(t_ray ray, t_object *cyl,
		t_cylindre_data *data)
{
	t_sec_degre_equa	res;

	data->oc = vec_minus(ray.origin, cyl->center);
	res.a = vec_dot(ray.direction, ray.direction) - (vec_dot(ray.direction,
				cyl->normal) * vec_dot(ray.direction, cyl->normal));
	res.b = 2 * (vec_dot(ray.direction, data->oc) - (vec_dot(ray.direction,
					cyl->normal) * vec_dot(data->oc, cyl->normal)));
	res.c = vec_dot(data->oc, data->oc) - (vec_dot(data->oc,
				cyl->normal) * vec_dot(data->oc, cyl->normal)) -
		((cyl->diameter / 2) * (cyl->diameter / 2));
	res.delta = (res.b * res.b) - (4 * res.a * res.c);
	if (res.delta < 0)
		return (0);
	data->t1 = (-res.b + sqrt(res.delta)) / (2 * res.a);
	data->t2 = (-res.b - sqrt(res.delta)) / (2 * res.a);
	data->m1 = vec_dot(ray.direction, cyl->normal) * data->t1
		+ vec_dot(data->oc, cyl->normal);
	data->m2 = vec_dot(ray.direction, cyl->normal) * data->t2
		+ vec_dot(data->oc, cyl->normal);
	if (data->m1 > 0 && data->m1 < cyl->heigth)
		data->t = data->t1;
	else if (data->m2 > 0 && data->m2 < cyl->heigth)
		data->t = data->t2;
	return (1);
}

t_cylindre_data		cylindre_data_initialize(void)
{
	t_cylindre_data data;

	data.oc = vec_initialize(0, 0, 0);
	data.m = 0;
	data.m1 = 0;
	data.m2 = 0;
	data.t = 0;
	data.t1 = 0;
	data.t2 = 0;
	return (data);
}

void				verify_cylindre(t_object *obj)
{
	if (!vec_compare(obj->normal, vec_initialize(-1, -1, -1),
				vec_initialize(1, 1, 1)))
		ft_perror("the cylindre normal must be between -1 and 1");
	if (!vec_compare(obj->color, vec_initialize(0, 0, 0),
				vec_initialize(255, 255, 255)))
		ft_perror("the cylindre colors must be between 0 and 255");
	if (obj->diameter < 0)
		ft_perror("the cylindre diameter must be over than 0");
	if (obj->heigth < 0)
		ft_perror("the cylindre height must be over than 0");
}
