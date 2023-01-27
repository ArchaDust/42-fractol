/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:04:16 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/23 13:55:14 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	compute(t_prg *p, t_frac *f, int iter)
{
	t_vec	opti;

	opti = (t_vec){f->z.x * f->z.x, f->z.y * f->z.y};
	while (opti.x + opti.y <= 4.0 && iter < p->maxiter)
	{
		f->z.y = f->z.x * f->z.y;
		f->z.y += f->z.y + f->c.y;
		f->z.x = opti.x - opti.y + f->c.x;
		opti.x = f->z.x * f->z.x;
		opti.y = f->z.y * f->z.y;
		iter++;
	}
	if (iter < p->maxiter)
		return (iter);
	return (-1);
}

static void	*julia_threading(void *a)
{
	t_thinfo	*th_info;
	t_prg		*p;
	t_frac		*f;
	int			y;
	int			x;

	th_info = (t_thinfo *)a;
	p = th_info->p;
	f = &th_info->f;
	y = th_info->y;
	while (y < th_info->ycap)
	{
		x = 0;
		while (x < p->fb->w)
		{
			f->z.y = f->yborder.x + th_info->tmp.y * y;
			f->z.x = f->xborder.x + th_info->tmp.x * x;
			p->iterfb[x + p->fb->w * y] = compute(p, f, 0);
			x++;
		}
		y++;
	}
	return (NULL);
}

t_frac	get_julia(void)
{
	t_frac	f;

	f.xborder.x = -2.0;
	f.xborder.y = 2.0;
	f.yborder.x = -1.12;
	f.yborder.y = 1.12;
	f.c = (t_vec){0.0, 0.0};
	f.z = (t_vec){0.0, 0.0};
	f.type = 2;
	return (f);
}

void	julia_compute(t_prg *p, t_frac *f)
{
	pthread_t		th[MAX_THREADS];
	t_thinfo		th_info[MAX_THREADS];
	int				i;

	thread_helper(th_info, p, f);
	i = 0;
	while (i < MAX_THREADS)
	{
		pthread_create(&th[i], NULL, julia_threading, &th_info[i]);
		i++;
	}
	i = 0;
	while (i < MAX_THREADS)
	{
		pthread_join(th[i], NULL);
		i++;
	}
}
