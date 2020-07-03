/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_bmp.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adtheus <adtheus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:59:27 by adtheus           #+#    #+#             */
/*   Updated: 2020/07/01 16:15:45 by adtheus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AT_BMP_H
# define AT_BMP_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include "struc.h"

extern t_app	*g_su;

/*
**	__BMP file header structure__
** Size of file
** Reserved
** ...
** Offset to bitmap data
*/

typedef struct	s_bitmapfileheader
{
	unsigned int	bf_size;
	unsigned short	bf_reserved1;
	unsigned short	bf_reserved2;
	unsigned int	bf_offbits;
}				t_bitmapfileheader;

typedef struct	s_bitmapinfoheader
{
	unsigned int	bi_size;
	int				bi_width;
	int				bi_height;
	unsigned short	bi_planes;
	unsigned short	bi_bitcount;
	unsigned int	bi_compression;
	unsigned int	bi_sizeimage;
	int				bi_xpelspermeter;
	int				bi_ypelspermeter;
	unsigned int	bi_clrused;
	unsigned int	bi_clrimportant;
}				t_bitmapinfoheader;

/*
** BMP file info structure
** Size of info header
** Width of image
** Height of image
** Number of color planes
** Number of bits per pixel
** Type of compression to use
** Size of image data
** X pixels per meter
** Y pixels per meter
** Number of colors used
** Number of important colors
*/

int				bitmap(int fd);

#endif
