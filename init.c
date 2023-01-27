/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:51:19 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/24 12:59:48 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	render_frac(t_prg *p)
{
	if (p->exiting)
		return ;
	if (p->frac_type == 1)
		mandel_compute(p, &p->f);
	if (p->frac_type == 2)
		julia_compute(p, &p->f);
	if (p->frac_type == 3)
		custom_compute(p, &p->f);
}

void	get_frac_default(t_prg *p)
{
	if (p->frac_type == 1)
		p->f = get_mandel();
	if (p->frac_type == 2)
	{
		p->lock = 0;
		p->f = get_julia();
	}
	if (p->frac_type == 3)
		p->f = get_custom();
}

int	fractol_init(t_prg *p, t_prgparam *param)
{
	ft_memset(p, 0, sizeof(t_prg));
	p->mlx = mlx_init();
	if (!p->mlx)
		return (clean_mem(p));
	p->win = mlx_new_window(p->mlx, WIN_W, WIN_H, "Fract'Ol");
	if (!p->win)
		return (clean_mem(p));
	p->fb = new_img(p->mlx, WIN_W, WIN_H);
	if (!p->fb)
		return (clean_mem(p));
	p->fbswap = new_img(p->mlx, WIN_W, WIN_H);
	if (!p->fbswap)
		return (clean_mem(p));
	p->iterfb = malloc(sizeof(int) * WIN_W * WIN_H);
	if (!p->iterfb)
		return (clean_mem(p));
	p->maxiter = param->maxiter;
	p->frac_type = param->frac_type;
	p->pal = palette_lookup(rainbow_palette(), p->maxiter);
	if (!p->pal)
		return (clean_mem(p));
	return (1);
}

int	hook_init(t_prg *p)
{
	get_frac_default(p);
	render_frac(p);
	iter_to_buffer(p);
	mlx_put_image_to_window(p->mlx, p->win, p->fb->img, 0, 0);
	swap_img(&p->fb, &p->fbswap);
	mlx_loop_hook(p->mlx, loop_hook_func, p);
	mlx_hook(p->win, 17, (1L << 17), quit_hook_func, p);
	mlx_hook(p->win, 6, (1L << 6), mouse_motion_hook_func, p);
	mlx_key_hook(p->win, key_hook_func, p);
	mlx_mouse_hook(p->win, mouse_hook_func, p);
	mlx_loop(p->mlx);
	return (1);
}
