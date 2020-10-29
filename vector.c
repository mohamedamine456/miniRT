/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:31:41 by mlachheb          #+#    #+#             */
/*   Updated: 2020/10/29 17:32:37 by mlachheb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	vec_initialize(float x, float y, float z)
{
	t_vector v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector	vec_plus(t_vector v1, t_vector v2)
{
	t_vector v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vector	vec_minus(t_vector v1, t_vector v2)
{
	t_vector v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

float		vec_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	vec_multiple_n(float t, t_vector v)
{
	v.x *= t;
	v.y *= t;
	v.z *= t;
	return (v);
}
