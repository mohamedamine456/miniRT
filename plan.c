/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:41:48 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/29 12:42:50 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			hit_plan(t_object *plan, t_ray ray, t_hited *hited)
{
	t_vector	vec;
	float		t;
	float		dn;

	dn = vec_dot(ray.direction, plan->normal);
	if (dn > 1e-6)
	{
		vec = vec_minus(ray.origin, plan->point);
		t = -vec_dot(vec, plan->normal) / dn;
		if (t > 1e-6 && t < hited->t)
		{
			hited->t = t;
			hited->p = ray_calculate(ray, hited->t);
			hited->normal = dn > 0 ? plan->normal :
				vec_multiple_n(-1, plan->normal);
			vec_normalize(&(*hited).normal);
			hited->color = plan->color;
			hited->obj = plan->id;
			return (1);
		}
	}
	return (0);
}

void		verify_plane(t_object *obj)
{
	if (!vec_compare(obj->normal, vec_initialize(-1, -1, -1),
				vec_initialize(1, 1, 1)))
		ft_perror("the plane normal must be between -1 and 1");
	if (!vec_compare(obj->color, vec_initialize(0, 0, 0),
				vec_initialize(255, 255, 255)))
		ft_perror("the plane colors must be between 0 and 255");
}
