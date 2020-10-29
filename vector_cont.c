/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cont.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:32:46 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/29 17:33:59 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float		vec_lenght(t_vector v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

float		vec_normalize(t_vector *v)
{
	float length;

	length = vec_lenght(*v);
	if (length)
		*v = vec_multiple_n((1 / length), *v);
	return (length);
}

t_vector	vec_cross(t_vector vec1, t_vector vec2)
{
	t_vector vec;

	vec.x = vec1.y * vec2.z - vec1.z * vec2.y;
	vec.y = vec1.z * vec2.x - vec1.x * vec2.z;
	vec.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (vec);
}

t_vector	ray_calculate(t_ray r, float t)
{
	return (vec_plus(r.origin, vec_multiple_n(t, r.direction)));
}

int			vec_compare(t_vector vec, t_vector a, t_vector b)
{
	if (vec.x < a.x || vec.x > b.x)
		return (0);
	if (vec.y < a.y || vec.y > b.y)
		return (0);
	if (vec.z < a.z || vec.z > b.z)
		return (0);
	return (1);
}
