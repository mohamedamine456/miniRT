/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:29:59 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/29 17:31:31 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		hit_triangle(t_object *tr, t_ray ray, t_hited *hited)
{
	t_triangle_data	data;
	int				var;

	var = 0;
	var = solve_triangle(ray, tr, &data);
	if (var == -1)
		return (0);
	if (data.t > 1e-6 && data.t < hited->t)
	{
		hited->t = data.t;
		hited->p = ray_calculate(ray, hited->t);
		(*hited).normal = vec_cross(data.edge1, data.edge2);
		vec_normalize(&(*hited).normal);
		hited->color = tr->color;
		hited->obj = tr->id;
		hited->rotated = 0;
		return (1);
	}
	return (0);
}

int		solve_triangle(t_ray ray, t_object *tr, t_triangle_data *data)
{
	data->edge1 = vec_minus(tr->second_point, tr->first_point);
	data->edge2 = vec_minus(tr->third_point, tr->first_point);
	data->ed2_crs_dir = vec_cross(ray.direction, data->edge2);
	data->ed1_dot_e2d = vec_dot(data->edge1, data->ed2_crs_dir);
	if (data->ed1_dot_e2d > -1e-6 && data->ed1_dot_e2d < 1e-6)
		return (-1);
	data->temp = 1.0 / data->ed1_dot_e2d;
	data->org_min_frstpnt = vec_minus(ray.origin, tr->first_point);
	data->uniq = data->temp * (vec_dot(data->org_min_frstpnt,
				data->ed2_crs_dir));
	if (data->uniq < 0.0 || data->uniq > 1.0)
		return (-1);
	data->prev_crs_ed1 = vec_cross(data->org_min_frstpnt, data->edge1);
	data->vec_dot = data->temp * vec_dot(ray.direction, data->prev_crs_ed1);
	if (data->vec_dot < 0.0 || data->uniq + data->vec_dot > 1.0)
		return (-1);
	data->t = data->temp * vec_dot(data->edge2, data->prev_crs_ed1);
	return (1);
}

void	verify_triangle(t_object *obj)
{
	if (!vec_compare(obj->color, vec_initialize(0, 0, 0),
				vec_initialize(255, 255, 255)))
		ft_perror("the Triangle colors must be between 0 and 255");
}
