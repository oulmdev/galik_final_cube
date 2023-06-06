/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_ext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:22:33 by imahri            #+#    #+#             */
/*   Updated: 2023/05/23 02:37:55 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ss;
	char	*ptr;

	ss = (char *)s;
	ptr = 0;
	if (c == 0)
		ptr = ss;
	while (*ss)
	{
		if (*ss == (char)c)
			ptr = ss;
		ss++;
	}
	if (*ss == (char) c)
		ptr = ss;
	return (ptr);
}

bool	check_path(char *path)
{
	char	*check_extension;

	if (ft_strlen(path) == 0)
	{
		print("Error\nEmpty Argumment\n", 2);
		return (false);
	}
	check_extension = ft_strrchr(path, '.');
	if (strcmp(check_extension, ".cub") != 0)
	{
		print("Error\nInvalid Path\n", 2);
		return (false);
	}
	return (true);
}

int	check_for_valid_keys(char **str)
{
	int	i;
	int	j;

	j = 0;
	while (str[j])
	{
		i = 0;
		while (str[j][i])
		{
			if (str[j][i] != '0' && str[j][i] != '1'
				&& str[j][i] != 'N' && str[j][i] != 'S'
				&& str[j][i] != 'E' && str[j][i] != 'W'
				&& str[j][i] != ' ' && str[j][i] != '#')
				return (print("Error\nInvalid keys bro!!\n", 2), 1);
			i++;
		}
		j++;
	}
	return (0);
}
