/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:46:25 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/23 12:48:34 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	iter_to_buffer(t_prg *p)
{
	int	x;
	int	y;
	int	iter;

	y = 0;
	while (y < p->fb->h)
	{
		x = 0;
		while (x < p->fb->w)
		{
			iter = p->iterfb[x + y * p->fb->w];
			if (iter < 0)
				draw_px_f(p->fb, x, y, (t_color)0);
			else
				draw_px_f(p->fb, x, y, p->pal[(iter + p->tstamp) % p->maxiter]);
			x++;
		}
		y++;
	}
}

void	draw_px(t_img *i, int x, int y, t_color c)
{
	if (x < 0 || x >= i->w || y < 0 || y >= i->h)
		return ;
	*(unsigned int *)(i->px + (y * i->stride) + (x * i->bpp)) = c.ucol;
}

void	draw_px_f(t_img *i, int x, int y, t_color c)
{
	*(unsigned int *)(i->px + (y * i->stride) + (x * i->bpp)) = c.ucol;
}
