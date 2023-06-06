/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 01:41:18 by moulmoud          #+#    #+#             */
/*   Updated: 2023/05/16 17:14:21 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

/*	The therd argument is a boolean to know if we,
	have to free the second string or not
*/
int	ft_strcmp(char *s1, char *s2, int free_it)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
	{
		if (free_it)
			free(s2);
		return (1);
	}
	while (s1[i])
	{
		if (s1[i] != s2[i])
		{
			if (free_it)
				free(s2);
			return (1);
		}
		i++;
	}
	if (free_it)
		free(s2);
	return (0);
}

char	*ft_strjoin_pro(char *s1, char *s2, int free1, int free2)
{
	char	*strjoin;
	size_t	len;
	size_t	i;
	size_t	j;

	j = 0;
	len = ft_strlen (s1) + ft_strlen (s2);
	strjoin = malloc (len + 1 * sizeof(char));
	if (!strjoin)
		return (NULL);
	i = -1;
	while (s1 && s1[++i] != '\0')
		strjoin[i] = s1[i];
	while (s2 && s2[j] != '\0')
		strjoin[i++] = s2[j++];
	strjoin[len] = '\0';
	if (free1)
		free(s1);
	if (free2)
		free(s2);
	return (strjoin);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (str && str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
