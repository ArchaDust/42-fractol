/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:34:51 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/17 11:07:13 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move_to_pos(t_prg *p, int x, int y)
{
	t_frac	*f;
	t_vec	tmp;

	f = &p->f;
	tmp.x = x * (f->xborder.y - f->xborder.x) * p->fb->rw;
	tmp.y = y * (f->yborder.y - f->yborder.x) * p->fb->rh;
	tmp.x = tmp.x - ((f->xborder.y - f->xborder.x) * 0.5);
	tmp.y = tmp.y - ((f->yborder.y - f->yborder.x) * 0.5);
	f->xborder.x = f->xborder.x + tmp.x;
	f->xborder.y = f->xborder.y + tmp.x;
	f->yborder.x = f->yborder.x - tmp.y;
	f->yborder.y = f->yborder.y - tmp.y;
	p->modified = 1;
}

void	zoom_in(t_prg *p, int x, int y)
{
	t_frac	*f;
	t_vec	tmp;

	f = &p->f;
	move_to_pos(p, x, y);
	tmp.x = (f->xborder.y - f->xborder.x) * 0.95;
	tmp.y = (f->yborder.y - f->yborder.x) * 0.95;
	f->xborder = (t_vec){f->xborder.y - tmp.x, f->xborder.x + tmp.x};
	f->yborder = (t_vec){f->yborder.y - tmp.y, f->yborder.x + tmp.y};
}

void	zoom_out(t_prg *p, int x, int y)
{
	t_frac	*f;
	t_vec	tmp;

	f = &p->f;
	move_to_pos(p, x, y);
	tmp.x = (f->xborder.y - f->xborder.x) / 0.95;
	tmp.y = (f->yborder.y - f->yborder.x) / 0.95;
	f->xborder = (t_vec){f->xborder.y - tmp.x, f->xborder.x + tmp.x};
	f->yborder = (t_vec){f->yborder.y - tmp.y, f->yborder.x + tmp.y};
}
