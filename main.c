/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:30:56 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/24 12:58:19 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	usage(void)
{
	ft_putstr_fd("usage: fractol fractal [-i iter]\n", 1);
	ft_putstr_fd("  fractal: mandlebrot julia ship\n", 1);
	ft_putstr_fd("  -i: iteration nuumber, will be clamped in [16-512].\n", 1);
	return (0);
}

static int	read_param(int argc, char **argv, t_prgparam *param)
{
	if (argc < 2)
		return (0);
	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		param->frac_type = 1;
	else if (ft_strncmp(argv[1], "julia", 6) == 0)
		param->frac_type = 2;
	else if (ft_strncmp(argv[1], "ship", 5) == 0)
		param->frac_type = 3;
	else
		return (0);
	param->maxiter = MAX_ITER;
	if (argc < 3)
		return (1);
	if (argc > 4)
		return (0);
	if (ft_strncmp(argv[2], "-i", 2) != 0)
		return (0);
	param->maxiter = ft_atoi(argv[3]);
	if (param->maxiter < 16)
		param->maxiter = 16;
	if (param->maxiter >= 512)
		param->maxiter = 512;
	return (1);
}

int	main(int argc, char **argv)
{
	t_prg		*p;
	t_prgparam	param;

	if (!read_param(argc, argv, &param))
		return (usage());
	p = malloc(sizeof(t_prg));
	if (!p)
	{
		ft_putstr_fd("Alloc Error\n", 2);
		return (0);
	}
	if (!fractol_init(p, &param))
	{
		ft_putstr_fd("Alloc Error\n", 2);
		free(p);
		return (0);
	}
	hook_init(p);
	return (0);
}
