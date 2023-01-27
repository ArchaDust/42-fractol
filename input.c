/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:54:56 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/23 13:44:59 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	key_hook_ext(int keycode, t_prg *p)
{
	if (keycode == KEY_ARROW_UP || keycode == KEY_W)
		move_to_pos(p, (p->fb->w / 2), (p->fb->h / 2) + 40);
	if (keycode == KEY_ARROW_DOWN || keycode == KEY_S)
		move_to_pos(p, (p->fb->w / 2), (p->fb->h / 2) - 40);
	if (keycode == KEY_ARROW_LEFT || keycode == KEY_A)
		move_to_pos(p, (p->fb->w / 2) - 40, (p->fb->h / 2));
	if (keycode == KEY_ARROW_RIGHT || keycode == KEY_D)
		move_to_pos(p, (p->fb->w / 2) + 40, (p->fb->h / 2));
	if (keycode == KEY_PAD_PLUS)
		zoom_in(p, (p->fb->w / 2), (p->fb->h / 2));
	if (keycode == KEY_PAD_MINUS)
		zoom_out(p, (p->fb->w / 2), (p->fb->h / 2));
}
