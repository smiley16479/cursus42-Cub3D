/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_bmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:31:30 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/01 16:16:14 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "at_bmp.h"

static inline void	set_header(t_bitmapfileheader *bfh,
					t_bitmapinfoheader *bih, unsigned short *bf_type)
{
	*bf_type = 0x4d42;
	bfh->bf_reserved1 = 0;
	bfh->bf_reserved2 = 0;
	bfh->bf_size = 2 + sizeof(t_bitmapfileheader)
					+ sizeof(t_bitmapinfoheader) + 640 * 480 * 4;
	bfh->bf_offbits = 0x36;
	bih->bi_size = sizeof(t_bitmapinfoheader);
	bih->bi_width = g_su->su_img->size.x;
	bih->bi_height = g_su->su_img->size.y;
	bih->bi_planes = 1;
	bih->bi_bitcount = 32;
	bih->bi_compression = 0;
	bih->bi_sizeimage = 0;
	bih->bi_xpelspermeter = 5000;
	bih->bi_ypelspermeter = 5000;
	bih->bi_clrused = 0;
	bih->bi_clrimportant = 0;
}
// Envoi une des variables en param pour aimer la norm
int					bitmap(void)
{
	t_bitmapfileheader	bfh;
	t_bitmapinfoheader	bih;
	unsigned short		bf_type;
	t_vector2			xy;
	int					file;
	unsigned int		color;

	set_header(&bfh, &bih, &bf_type);
	if (!(file = open("a.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666)))
	{
		printf("Could not write file\n");
		return (1);
	}
	write(file, &bf_type, sizeof(bf_type));
	write(file, &bfh, sizeof(bfh));
	write(file, &bih, sizeof(bih));
	xy.y = bih.bi_height;
	while (--(xy.y) >= 0 && (xy.x = -1))
		while (++(xy.x) < bih.bi_width)
		{
			color = ((int*)(g_su->su_img->addr))
			[bih.bi_width * xy.y + xy.x];
			write(file, &color, 4);
		}
	close(file);
	return (0);
}
