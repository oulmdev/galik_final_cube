/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 23:38:09 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/06 00:25:49 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>



typedef struct s_ray{
    int ray;
} t_ray;

typedef struct s_list{
    t_ray **ray;
}	t_list;


int main()
{
    t_list lst;
    
    
    
    
    lst.ray = (t_ray **)malloc((sizeof(t_ray *) * 3));
    if (!lst.ray)
        return (0);
    
    lst.ray[0] = (t_ray *)malloc(sizeof(t_ray));
    if (!lst.ray[0])
        return (0);
    lst.ray[1] = (t_ray *)malloc(sizeof(t_ray));
    if (!lst.ray[1])
        return (0);
    lst.ray[2] = NULL;
    lst.ray[0]->ray = 1;
    lst.ray[1]->ray = 2;
    
    
    int i = 0;
    while (lst.ray[i])
    {
        printf("%d\n", lst.ray[i]->ray);
        i++;
    }
}