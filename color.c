/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:35:37 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/11 10:57:00 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_pal	new_palette(float a[3], float b[3], float c[3], float d[3])
{
	t_pal	pal;

	pal.ar = a[0];
	pal.ag = a[1];
	pal.ab = a[2];
	pal.br = b[0];
	pal.bg = b[1];
	pal.bb = b[2];
	pal.cr = c[0];
	pal.cg = c[1];
	pal.cb = c[2];
	pal.dr = d[0];
	pal.dg = d[1];
	pal.db = d[2];
	return (pal);
}

t_pal	rainbow_palette(void)
{
	t_pal	pal;

	pal.ar = 0.5;
	pal.ag = 0.5;
	pal.ab = 0.5;
	pal.br = 0.5;
	pal.bg = 0.5;
	pal.bb = 0.5;
	pal.cr = 1.0;
	pal.cg = 1.0;
	pal.cb = 1.0;
	pal.dr = 0.0;
	pal.db = 0.333;
	pal.dg = 0.667;
	return (pal);
}

t_color	palette(t_pal p, int iter, const int maxiter)
{
	t_color	c;
	float	t;

	t = (float)iter / (float)maxiter;
	c.rgba.a = 0;
	c.rgba.r = 255 * (p.ar + p.br * cos(M_PI2 * (p.cr * t + p.dr)));
	c.rgba.g = 255 * (p.ag + p.bg * cos(M_PI2 * (p.cg * t + p.dg)));
	c.rgba.b = 255 * (p.ab + p.bb * cos(M_PI2 * (p.cb * t + p.db)));
	return (c);
}

t_color	*palette_lookup(t_pal p, const int maxiter)
{
	t_color	*c;
	int		i;

	c = malloc(sizeof(t_color) * maxiter);
	if (!c)
		return (NULL);
	i = 0;
	while (i < maxiter)
	{
		c[i] = palette(p, i, maxiter);
		i++;
	}
	return (c);
}
