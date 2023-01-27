/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:42:19 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/23 12:27:06 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_img	*new_img(void *mlx, int w, int h)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx, w, h);
	if (!img->img)
	{
		free(img);
		return (NULL);
	}
	img->px = mlx_get_data_addr(img->img, &img->bpp, &img->stride, &img->end);
	img->bpp /= 8;
	img->w = w;
	img->h = h;
	img->rw = 1.0L / (t_ld)w;
	img->rh = 1.0L / (t_ld)h;
	return (img);
}

void	swap_img(t_img **img, t_img **swap)
{
	t_img	*tmp;

	tmp = *img;
	*img = *swap;
	*swap = tmp;
}

void	delete_img(void *mlx, t_img *img)
{
	mlx_destroy_image(mlx, img->img);
	free(img);
}
