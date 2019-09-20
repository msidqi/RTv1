/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_box_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:53:00 by kdaou             #+#    #+#             */
/*   Updated: 2019/09/20 16:42:08 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*
** t[4] => t[0]  x_min    t[1] x_max   t[2] y_min   t[3] y_max
*/
static t_vec4 ft_vec4_inv(t_vec4 v)
{
	t_vec4	new;

	new.x = 1 / v.x;
	new.y = 1 / v.y;
	new.z = 1 / v.z;
	new.w = 0;
	return (new);
}

static int		ft_get_t_bounds(double *t, t_vec4 vec, t_ray *ray, t_box *box)
{
	int	signe[3];

	signe[0] = (vec.x < 0);
	signe[1] = (vec.y < 0);
	signe[2] = (vec.z < 0);
	t[0] = (((signe[0] ? box->bound_max.x : box->bound_min.x) - ray->origin.x) * vec.x);
	t[1] = (((signe[0] ? box->bound_min.x : box->bound_max.x) - ray->origin.x) * vec.x);
	t[2] = (((signe[1] ? box->bound_max.y : box->bound_min.y) - ray->origin.y) * vec.y);
	t[3] = (((signe[1] ? box->bound_min.y : box->bound_max.y) - ray->origin.y) * vec.y);
	if (t[0] > t[3] || t[2] > t[1])
		return (0);
	if (t[2] > t[0])
		t[0] = t[2];
	if (t[3] < t[1])
		t[1] = t[3];
	t[4] = (((signe[2] ? box->bound_max.z : box->bound_min.z) - ray->origin.z) * vec.z);
	t[5] = (((signe[2] ? box->bound_min.z : box->bound_max.z) - ray->origin.z) * vec.z);
	if ((t[0] > t[5]) || t[4] > t[1])
		return (0);
	if (t[4] > t[0])
		t[0] = t[4];
	if (t[5] < t[1])
		t[1] = t[5];
	if (((t[1] <  t[0] || t[0] < NEAR) && t[1] > 0.1) && (t[1] < ray->t))
	{
		ray->t = t[1];
		return (1);
	}
	else if (((t[0] < t[1] || t[1] < NEAR) && t[0] > 0.1) && (t[0] < ray->t))
	{
		ray->t = t[0];
		return (1);
	}
	return (0);
}
int				ft_box_inter(t_ray *ray, t_box *sp)
{
	double	t[6];
	t_vec4	inv_dir;

	inv_dir = ft_vec4_inv(ray->dir);
	int d = ft_get_t_bounds(t, inv_dir, ray, sp);
	return (d);
}

/*
** called foreach pixel
**	foreach light
**	get r_light and normal_sphere(calculate once)
**	check intersection with all objects,
** 		if : (hidden from light source by an obj) then :(its spec/diffuse += 0)
**	else : computed specular,
**		diffuse (light pixel, if : distance to light < (distance to obj == t))
**	ADD to return value
**
**	after foreach loop, add ambient
*/

static t_vec4	ft_get_box_normal(t_ray *ray, t_box *sp)
{
	t_vec4	p;
	t_vec4	c;
	t_vec4	d;

	c = ft_vec4_scalar(ft_vec4_add(sp->bound_min, sp->bound_max), 0.5);
	p = ft_vec4_sub(ft_vec4_add(ray->origin, ft_vec4_scalar(ray->dir, ray->t)), c);
	d = ft_create_vec4(fabs(sp->bound_min.x - sp->bound_max.x) / 2, 
							fabs(sp->bound_min.y - sp->bound_max.y) / 2, 
							fabs(sp->bound_min.z - sp->bound_max.z) / 2 
							, 0);
	return (ft_vec4_normalize(
        ft_create_vec4(p.x / d.x * 1.000001, p.y / d.y * 1.000001, p.z / d.z * 1.000001, 0)));
}

int		ft_texture_sphere(int id, t_ray *ray, t_sphere *sp);

int	ft_box_shader(t_data *data, t_ray *ray, t_box *sp)
{
	t_shader_x	sh_x;
	t_vec4		sp_nor;
	t_vec4		ds[2];
	int			c;

	c = 0x0;
	sp_nor = ft_get_box_normal(ray, sp);
	ds[0] = sp->diffuse;
	ds[1] = ft_create_vec4(sp->specular, sp->specular,
			sp->specular, sp->specular);
	if (sp->ref.w == 1 && ray->refl_depth > 0)
	{
		ray->refl_depth--;
		c = ft_reflected_ray(data, sp_nor, ray, sp->ref);
		if (false) // 100% reflectant, and no shading
			return (c);
	}
	if (sp->ref.w == 2)
		c = ft_refracted_ray(data, sp_nor, ray, sp->ref);
	sh_x = ft_ray_inter_lights(data, sp_nor, ray, ds);
	return (ft_compute_shader(ft_color_add(sp->color, c), &sh_x));
}