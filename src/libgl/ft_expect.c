/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 08:03:33 by kdaou             #+#    #+#             */
/*   Updated: 2019/07/16 17:18:19 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int	ft_expect_vector(char *line, char *name, t_vec4 *vector)
{
	char	**tab;
	int		i;

	if (!line || !(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 4 ||
			ft_strncmp(tab[0], name, ft_strlen(name)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	i = 0;
	while (tab[++i])
		if (!ft_is_numeric(tab[i]))
		{
			ft_free_tab(&tab);
			return (0);
		}
	i = !ft_strcmp(tab[0], "\tnormal") ? 0 : 1;
	*vector = ft_create_vec4(ft_atof(tab[1]), ft_atof(tab[2]),
			ft_atof(tab[3]), i);
	ft_free_tab(&tab);
	return (1);
}

int	ft_expect_value(char *line, char *name, double *value)
{
	char	**tab;

	if (!line || !(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 2 || ft_strncmp(tab[0],
				name, ft_strlen(name)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	if (!ft_is_numeric(tab[1]))
	{
		ft_free_tab(&tab);
		return (0);
	}
	if (!ft_strcmp(tab[0], "\tspecular") && !ft_is_limited(ft_atof(tab[1])))
	{
		ft_free_tab(&tab);
		return (0);
	}
	*value = ft_atof(tab[1]);
	ft_free_tab(&tab);
	return (1);
}

int ft_expect_refl(char *line, char *n, t_vec4 *refl)
{
	char	**tab;
	int		i;
	float	t;
	if (!line || !(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 5 || ft_strncmp(tab[0], n, ft_strlen(n)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	i = 0;
	t = ft_atof(tab[4]);
	while (tab[++i] && i < 4)
		if (!ft_is_numeric(tab[i]) || !ft_is_limited(ft_atof(tab[i])))
		{
			ft_free_tab(&tab);
			return (0);
		}
	refl->x = ft_atof(tab[1]);
	refl->y = ft_atof(tab[2]);
	refl->z = ft_atof(tab[3]);
	refl->w =  (t > 3 || t < 0) ? 0 : t;
	ft_free_tab(&tab);
	return (1);
}

int ft_expect_spot_dot(char *line, char *name, float *spot_dot)
{
	char	**tab;
	float	val;

	if (!line || !(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 2 ||
			ft_strncmp(tab[0], name, ft_strlen(name)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	val = ft_atof(tab[1]);
	if (!ft_is_numeric(tab[1]) || val >= 0.0|| val <= -1.0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	*spot_dot = val;
	ft_free_tab(&tab);
	return (1);
}

int ft_expect_area_uv(char *line, char *name, t_vec4 *uv_dir, unsigned short *uv_nodes)
{
	char	**tab;
	int		i;

	if (!line || !(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 5 ||
			ft_strncmp(tab[0], name, ft_strlen(name)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	i = 0;
	while (tab[++i])
		if (!ft_is_numeric(tab[i]))
		{
			ft_free_tab(&tab);
			return (0);
		}
	uv_dir->x = ft_atof(tab[1]);
	uv_dir->y = ft_atof(tab[2]);
	uv_dir->z = ft_atof(tab[3]);
	*uv_nodes = (unsigned short)ft_atoi(tab[4]);
	ft_free_tab(&tab);
	return (1);
}

int	ft_expect_intensity(char *line, char *name, t_light *light)
{
	char	**tab;
	int		i;

	if (!line || !(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 4 ||
			ft_strncmp(tab[0], name, ft_strlen(name)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	i = 0;
	while (tab[++i])
		if (!ft_is_numeric(tab[i]) || !ft_is_limited(ft_atof(tab[i])))
		{
			ft_free_tab(&tab);
			return (0);
		}
	light->r = ft_atof(tab[1]);
	light->g = ft_atof(tab[2]);
	light->b = ft_atof(tab[3]);
	ft_free_tab(&tab);
	return (1);
}

int	ft_expect_diffuse(char *line, char *name, t_vec4 *vector)
{
	char	**tab;
	int		i;

	if (!line || !(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 4 ||
			ft_strncmp(tab[0], name, ft_strlen(name)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	i = 0;
	while (tab[++i])
		if (!ft_is_numeric(tab[i]) || !ft_is_limited(ft_atof(tab[i])))
		{
			ft_free_tab(&tab);
			return (0);
		}
	*vector = ft_create_vec4(ft_atof(tab[1]), ft_atof(tab[2]),
			ft_atof(tab[3]), 0);
	ft_free_tab(&tab);
	return (1);
}

int	ft_expect_color(char *line, char *name, int *color)
{
	char	**tab;

	if (!line)
		return (0);
	if (!(tab = ft_strsplit(line, ' ')))
		return (0);
	if (ft_table_size(tab) != 4 ||
			ft_strncmp(tab[0], name, ft_strlen(name)) != 0)
	{
		ft_free_tab(&tab);
		return (0);
	}
	if (!ft_is_numeric(tab[1]))
	{
		ft_free_tab(&tab);
		return (0);
	}
	*color = (ft_atoi(tab[1]) << 16) | (ft_atoi(tab[2]) << 8) | ft_atoi(tab[3]);
	ft_free_tab(&tab);
	return (1);
}
