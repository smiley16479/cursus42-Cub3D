int     render_next_frame(t_app *g_su)
{
	int color = g_su->square_shape->color;
	//g_su->color_offset += 1;
	// who_wants_a_rainbow((t_app*)(g_su));
	draw_me_a_square();
    mlx_put_image_to_window(g_su->mlx, g_su->mlx_win, g_su->su_img->img_ptr, 0, 0);
	return (0);
}
