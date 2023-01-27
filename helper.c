/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:01:22 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/24 13:47:59 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	ft_ftoa_helper(int high, char *buffer)
{
	int		i;
	int		tmp;
	int		len;

	i = 0;
	tmp = high;
	len = (high == 0);
	while (tmp > 0)
	{
		tmp /= 10;
		len++;
	}
	tmp = high;
	buffer[i] = '0';
	while (high > 0)
	{
		buffer[len - 1 - i] = high % 10 + '0';
		high /= 10;
		i++;
	}
	return (i + (tmp == 0));
}

static void	ft_ftoa(t_ld f, char *buffer)
{
	int		high;
	int		i;
	int		j;

	i = 0;
	if (f < 0)
	{
		buffer[i++] = '-';
		f = -f;
	}
	j = i;
	high = (int)f;
	f = f - high;
	i += ft_ftoa_helper(high, &buffer[i]);
	buffer[i++] = '.';
	high = 3;
	while (high)
	{
		f *= 10.0;
		buffer[i++] = ((int)f) % 10 + '0';
		high--;
	}
	buffer[i] = '\0';
}

void	display_coord(t_prg *p)
{
	char	buffer[16];

	ft_ftoa(p->f.c.x, buffer);
	mlx_string_put(p->mlx, p->win, 5, 15, 0, "X: ");
	mlx_string_put(p->mlx, p->win, 30, 15, 0, buffer);
	ft_ftoa(p->f.c.y, buffer);
	mlx_string_put(p->mlx, p->win, 5, 30, 0, "Y: ");
	mlx_string_put(p->mlx, p->win, 30, 30, 0, buffer);
}

void	thread_helper(t_thinfo *th_info, t_prg *p, t_frac *f)
{
	int		i;
	float	th_step;
	t_vec	tmp;

	i = 0;
	th_step = (float)p->fb->h / (float)MAX_THREADS;
	tmp.x = (f->xborder.y - f->xborder.x) * p->fb->rw;
	tmp.y = (f->yborder.y - f->yborder.x) * p->fb->rh;
	while (i < MAX_THREADS)
	{
		th_info[i].p = p;
		th_info[i].f = *f;
		th_info[i].tmp = tmp;
		th_info[i].y = th_step * i;
		th_info[i].ycap = th_step * i + th_step;
		i++;
	}
}

int	clean_mem(t_prg *p)
{
	if (p->pal)
		free(p->pal);
	if (p->iterfb)
		free(p->iterfb);
	if (p->fbswap)
		delete_img(p->mlx, p->fbswap);
	if (p->fb)
		delete_img(p->mlx, p->fb);
	if (p->win)
		mlx_destroy_window(p->mlx, p->win);
	free(p);
	return (0);
}
