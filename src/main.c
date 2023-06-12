/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:25:43 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/13 00:17:20 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

/*	TODO:
	--	You have to check this before you push.
*/
void	free_stock(t_stock *stock)
{
	if (stock->ea)
		free(stock->ea);
	if (stock->we)
		free(stock->we);
	if (stock->so)
		free(stock->so);
	if (stock->no)
		free(stock->no);
	if (stock->ex_map)
		ft_free(stock->ex_map);
}

int	main(int ac, char *av[])
{
	t_stock	stock;

	if (ac != 2)
		return (print("Error\nWrong number of arguments\n", 2), 1);
	ft_memset(&stock, 0, sizeof(t_stock));
	if (!parsing(av[1], &stock))
		return (free_stock(&stock), 1);

	if (!start_the_game(&stock))
		return (false);
	return (0);
	// return (free_stock(&stock), 0);
}