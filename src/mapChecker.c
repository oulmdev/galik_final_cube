/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapChecker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:00:08 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/12 20:22:54 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

char	**fill_the_new_map(char **new, char **tab)
{
	int	x;
	int	y;

	y = 0;
	while (new[y])
	{
		x = 0;
		while (new[y][x])
		{
			if (x < ft_strlen(tab[y + 6]) && tab[y + 6][x] != ' ')
				new[y][x] = tab[y + 6][x];
			x++;
		}
		y++;
	}
	return (new);
}

char	**realloc_map(char **tab, int y, int x)
{
	char	**new_tab;

	new_tab = malloc(sizeof(char *) * (y + 1));
	if (!new_tab)
		return (print(ERROR_MALLOC, 2), NULL);
	new_tab[y] = NULL;
	while (y--)
	{
		new_tab[y] = malloc(sizeof(char) * (x + 1));
		if (!new_tab[y])
			return (print(ERROR_MALLOC, 2), NULL);
		new_tab[y][x] = '\0';
		ft_memset(new_tab[y], '#', x);
	}
	return (fill_the_new_map(new_tab, tab));
}

bool	norm_check_close(t_tools *pars, char **tab)
{
	if (tab[pars->x][pars->y] == 'N' || tab[pars->x][pars->y] == 'S'
		|| tab[pars->x][pars->y] == 'E' || tab[pars->x][pars->y] == 'W')
		pars->player++;
	if (pars->x == 0 || pars->y == 0 || pars->x == pars->len - 1
		|| pars->y == ft_strlen(tab[pars->x]) - 1)
		return (false);
	if ((pars->x - 1) >= 0 && (tab[pars->x - 1][pars->y] == '#'))
		return (false);
	if ((pars->x + 1) < pars->len && tab[pars->x + 1][pars->y] == '#')
		return (false);
	if ((pars->y + 1) < ft_strlen(tab[pars->x])
		&& tab[pars->x][pars->y + 1] == '#')
		return (false);
	if ((pars->y - 1) >= 0 && tab[pars->x][pars->y - 1] == '#')
		return (false);
	return (true);
}

bool	check_close(char **tab)
{
	t_tools	pars;

	ft_memset(&pars, 0, sizeof(t_tools));
	while (tab && tab[pars.len])
		pars.len++;
	while (tab && tab[pars.x])
	{
		pars.y = 0;
		while (tab[pars.x][pars.y])
		{
			if (tab[pars.x][pars.y] == '0' || tab[pars.x][pars.y] == 'N' ||
				tab[pars.x][pars.y] == 'S' || tab[pars.x][pars.y] == 'E'
				|| tab[pars.x][pars.y] == 'W')
				if (!norm_check_close(&pars, tab))
					return (print(ERROR_CLOSED_MAP, 2), false);
			pars.y++;
		}
		pars.x++;
	}
	if (tab && pars.player != 1)
		return (print(ERROR_PLAYER, 2), false);
	return (true);
}
