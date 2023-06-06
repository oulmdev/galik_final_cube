/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 01:42:46 by moulmoud          #+#    #+#             */
/*   Updated: 2023/05/15 01:43:50 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

int	ft_atoi(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] && is_digit(str[i]))
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*src;

	src = (unsigned char *) b;
	while (len--)
	{
		*src = (unsigned char)c;
		src++;
	}
	return ((void *)b);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
