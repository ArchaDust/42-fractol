/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:32:25 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/24 13:14:41 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# include <mlx_input.h>
# include <mlx.h>

# define MAX_ITER 256
# define M_PI2 6.28318f

# define WIN_W 1600
# define WIN_H 900

# define MAX_THREADS 8

typedef long double		t_ld;
typedef unsigned char	t_px;

typedef struct s_col
{
	t_px		b;
	t_px		g;
	t_px		r;
	t_px		a;
}				t_col;

typedef union u_color
{
	int				icol;
	unsigned int	ucol;
	t_col			rgba;
}					t_color;

typedef struct s_pal
{
	float		ar;
	float		ag;
	float		ab;
	float		br;
	float		bg;
	float		bb;
	float		cr;
	float		cg;
	float		cb;
	float		dr;
	float		dg;
	float		db;
}				t_pal;

typedef struct s_vec
{
	t_ld		x;
	t_ld		y;
}				t_vec;

typedef struct s_frac
{
	t_vec		c;
	t_vec		z;
	t_vec		xborder;
	t_vec		yborder;
	int			type;
}				t_frac;

typedef struct s_img
{
	t_ld		rw;
	t_ld		rh;
	void		*img;
	void		*px;
	int			bpp;
	int			stride;
	int			end;
	int			w;
	int			h;
}				t_img;

typedef struct s_prgparam
{
	int			frac_type;
	int			maxiter;
}				t_prgparam;

typedef struct s_prg
{
	t_frac		f;
	void		*mlx;
	void		*win;
	t_img		*fb;
	t_img		*fbswap;
	int			*iterfb;
	t_color		*pal;
	int			maxiter;
	int			pal_rotate;
	int			modified;
	int			tstamp;
	int			frac_type;
	int			lock;
	int			exiting;
}				t_prg;

typedef struct s_thinfo
{
	t_prg		*p;
	t_frac		f;
	t_vec		tmp;
	int			y;
	int			ycap;
}				t_thinfo;

// init.c
int		fractol_init(t_prg *p, t_prgparam *param);
int		hook_init(t_prg *p);
void	get_frac_default(t_prg *p);
void	render_frac(t_prg *p);

// image.c
t_img	*new_img(void *mlx, int w, int h);
void	swap_img(t_img **img, t_img **swap);
void	delete_img(void *mlx, t_img *img);

// color.c
t_pal	new_palette(float a[3], float b[3], float c[3], float d[3]);
t_pal	rainbow_palette(void);
t_color	palette(t_pal p, int iter, const int maxiter);
t_color	*palette_lookup(t_pal p, const int maxiter);

// hook.c
int		loop_hook_func(void *vp);
int		key_hook_func(int keycode, void *vp);
int		mouse_motion_hook_func(int x, int y, void *vp);
int		mouse_hook_func(int button, int x, int y, void *vp);
int		quit_hook_func(void *vp);

// input.c
void	key_hook_ext(int keycode, t_prg *p);

// draw.c
void	iter_to_buffer(t_prg *p);
void	draw_px(t_img *i, int x, int y, t_color c);
void	draw_px_f(t_img *i, int x, int y, t_color c);

// mandel.c
t_frac	get_mandel(void);
void	mandel_compute(t_prg *p, t_frac *f);

// julia.c
t_frac	get_julia(void);
void	julia_compute(t_prg *p, t_frac *f);

// custom.c
t_frac	get_custom(void);
void	custom_compute(t_prg *p, t_frac *f);

// helper.c
void	display_coord(t_prg *p);
void	thread_helper(t_thinfo *th_info, t_prg *p, t_frac *f);
int		clean_mem(t_prg *p);

// move.c
void	move_to_pos(t_prg *p, int x, int y);
void	zoom_in(t_prg *p, int x, int y);
void	zoom_out(t_prg *p, int x, int y);

// from libft
void	*ft_memset(void *b, int c, size_t len);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);

#endif
