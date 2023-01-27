/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:45:37 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/24 13:40:06 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	loop_hook_func(void *vp)
{
	t_prg	*p;

	p = (t_prg *)vp;
	if (p->exiting)
	{
		clean_mem(p);
		exit(0);
	}
	if (p->pal_rotate)
		p->tstamp += 1;
	if (p->modified)
	{
		render_frac(p);
		p->modified = 0;
	}
	iter_to_buffer(p);
	mlx_put_image_to_window(p->mlx, p->win, p->fb->img, 0, 0);
	if (p->frac_type == 2)
		display_coord(p);
	swap_img(&p->fb, &p->fbswap);
	return (1);
}

int	key_hook_func(int keycode, void *vp)
{
	t_prg	*p;

	p = (t_prg *)vp;
	if (p->exiting)
		return (1);
	if (keycode == KEY_ESCAPE)
		p->exiting = 1;
	if (keycode == KEY_R)
	{
		get_frac_default(p);
		p->modified = 1;
	}
	if (keycode == KEY_P)
		p->pal_rotate = !p->pal_rotate;
	if (keycode == KEY_L)
		p->lock = !p->lock;
	key_hook_ext(keycode, p);
	return (1);
}

int	mouse_motion_hook_func(int x, int y, void *vp)
{
	t_prg	*p;
	t_vec	tmp;

	p = (t_prg *)vp;
	if (p->exiting)
		return (1);
	if (p->frac_type != 2)
		return (1);
	if (p->lock)
		return (1);
	tmp.x = (p->f.xborder.y - p->f.xborder.x) * p->fb->rw;
	tmp.y = (p->f.yborder.y - p->f.yborder.x) * p->fb->rh;
	p->f.c.x = p->f.xborder.x + tmp.x * x;
	p->f.c.y = p->f.yborder.x + tmp.y * y;
	p->modified = 1;
	return (1);
}

int	mouse_hook_func(int button, int x, int y, void *vp)
{
	t_prg	*p;

	p = (t_prg *)vp;
	if (p->exiting)
		return (1);
	if (p->frac_type == 2 && !p->lock)
		return (1);
	if (button == MBUTTON_SCROLLUP)
		zoom_in(p, x, y);
	if (button == MBUTTON_SCROLLDOWN)
		zoom_out(p, x, y);
	return (1);
}

int	quit_hook_func(void *vp)
{
	t_prg		*p;

	p = (t_prg *)vp;
	clean_mem(p);
	exit(0);
	return (1);
}
