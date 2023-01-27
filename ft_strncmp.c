/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 06:03:21 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/24 11:12:29 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n < 1)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if ((unsigned char)(s1[i]) != (unsigned char)(s2[i]))
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	if (i >= n)
		return (0);
	if (s1[i] == '\0' || s2[i] == '\0')
	{
		if ((unsigned char)(s1[i]) != (unsigned char)(s2[i]))
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
	}
	return (0);
}
