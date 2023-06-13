/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalizeAngle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:17:39 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/13 12:22:01 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

/******************************************************************************
 * 						NORMALIZE ANGLE FUNCTION
 * 		normalize_angle: normalize the angle to be between 0 and 360.
 * 		HOW IT WORKS:
 * 		1)	If the angle is negative, we add 360 to it.
 * 		2)	If the angle is greater than 360, we subtract 360 from it.
******************************************************************************/
double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += 360;
	if (angle > 360)
		angle -= 360;
	return (angle);
}