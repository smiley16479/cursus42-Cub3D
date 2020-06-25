#include "at_bmp.h"

static inline void set_header(t_BITMAPFILEHEADER *bfh, 
					t_BITMAPINFOHEADER *bih, unsigned short *bfType)
{
*bfType=0x4d42;
bfh->bfReserved1 = 0;
bfh->bfReserved2 = 0;
bfh->bfSize = 2 + sizeof(t_BITMAPFILEHEADER) 
				+ sizeof(t_BITMAPINFOHEADER)+640*480*4;
bfh->bfOffBits = 0x36;

bih->biSize = sizeof(t_BITMAPINFOHEADER);
bih->biWidth = g_su->su_img->size.x;
bih->biHeight = g_su->su_img->size.y;
bih->biPlanes = 1;
bih->biBitCount = 32;
bih->biCompression = 0;
bih->biSizeImage = 0;
bih->biXPelsPerMeter = 5000;
bih->biYPelsPerMeter = 5000;
bih->biClrUsed = 0;
bih->biClrImportant = 0;
}

int bitmap(void)
{
t_BITMAPFILEHEADER bfh;
t_BITMAPINFOHEADER bih;
unsigned short bfType;
t_vector2 xy;
int file; 

set_header(&bfh, &bih, &bfType);
if (!(file = open("a.bmp",O_CREAT | O_RDWR | O_TRUNC, 0666)))
    {
        printf("Could not write file\n");
        return (1);
    }
write(file, &bfType, sizeof(bfType));
write(file, &bfh, sizeof(bfh));
write(file, &bih, sizeof(bih));
xy.y = bih.biHeight; 
while (--(xy.y) >= 0 && (xy.x = - 1))
    while (++(xy.x )< bih.biWidth)
	{
		unsigned int color = ((int*)(g_su->su_img->addr))
		[bih.biWidth * xy.y + xy.x];
		write(file, &color, 4);
    }
close(file);
return (0);
}