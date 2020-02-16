/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_vector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 22:48:39 by adtheus           #+#    #+#             */
/*   Updated: 2020/02/10 22:52:46 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_vector2.h"

t_vector2 create_vector2(int x, int y)
{
	t_vector2 to_return;
	to_return.x = x;
	to_return.y = y;
	return (to_return);
}