/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_mlx_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:07:17 by adtheus           #+#    #+#             */
/*   Updated: 2020/03/09 20:33:15 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "at_mlx_sprite.h"
#include "struc.h"

int which_sprite(char is_a_sprite)
{
	int i;

	i = -1;
	while (g_su->sprite_tab[++i])
		if (is_a_sprite == g_su->sprite_tab[i])
			return(g_su->sprite_tab[i]);
	return (0);
}

void	join_sprites(t_player *p1, t_player *p2)
{
	t_vector2_d tab[100];
	int i = -1;
	while (++i < 100)
	{
		tab[i].s_dist = 0;
		tab[i].s_impact = 0;
		tab[i].sprite = 0;
	}
	int sprite_num = p1->sprite_num + p2->sprite_num < 100 ? p1->sprite_num + p2->sprite_num : 100;
	i = 0;
	while (p1->sprite_num + p2->sprite_num)
	{
		if (p1->sprite_num < 0 || p2->sprite_num < 0)
		{
			printf("Revoie ton algo coco : dans at_mlx_sprite.c l 44\n");
			break;
		}	
		tab[i].s_dist = p1->sprite_v2[p1->sprite_num - 1].s_dist > p2->sprite_v2[p2->sprite_num - 1].s_dist ? p1->sprite_v2[p1->sprite_num - 1].s_dist : p2->sprite_v2[p2->sprite_num - 1].s_dist;
		tab[i].sprite = tab[i].s_dist == p1->sprite_v2[p1->sprite_num - 1].s_dist ? p1->sprite_v2[p1->sprite_num - 1].sprite : p2->sprite_v2[p2->sprite_num - 1].sprite;
		tab[i].s_dist == p1->sprite_v2[p1->sprite_num - 1].s_dist ? p1->sprite_num-- : p2->sprite_num--;
		++i;
	}
	p1->sprite_num = sprite_num;
	i = 0;
	while (sprite_num--)
	{
		p1->sprite_v2[i].s_dist = tab[i].s_dist;
		p1->sprite_v2[i].sprite = tab[i].sprite;
		++i;
	}
}
/*
int main()
{
	t_player tab[2];
	tab[0].sprite_v2[0].s_dist = 2;
	tab[0].sprite_v2[0].sprite = 2;
	tab[1].sprite_v2[0].s_dist = 3;
	tab[1].sprite_v2[0].sprite = 3;
	tab[0].sprite_v2[1].s_dist = 4;
	tab[0].sprite_v2[1].sprite = 4;
	tab[1].sprite_v2[1].s_dist = 5;
	tab[1].sprite_v2[1].sprite = 5;
	tab[0].sprite_v2[2].s_dist = 10;
	tab[0].sprite_v2[2].sprite = 10;
	tab[1].sprite_v2[2].s_dist = 11;
	tab[1].sprite_v2[2].sprite = 11;
	tab[0].sprite_v2[3].s_dist = 15;
	tab[0].sprite_v2[3].sprite = 15;
	tab[1].sprite_v2[3].s_dist = 16;
	tab[1].sprite_v2[3].sprite = 16;
	tab[1].sprite_v2[4].s_dist = 19;
	tab[1].sprite_v2[4].sprite = 19;

	tab[0].sprite_num = 4;
	tab[1].sprite_num = 5;

	join_sprites(&tab[0] , &tab[1]);

	int i = 0;
	while (i < tab[0].sprite_num)
	{
		printf("%d,\n tab[0].sprite_v2[0].s_dist : %f tab[0].sprite_v2[0].sprite : %d\n", i, tab[0].sprite_v2[i].s_dist , tab[0].sprite_v2[i].sprite);
		++i;
	}

}*/