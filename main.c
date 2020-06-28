/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 20:02:05 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/28 17:47:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelbrot.h"

int	__attribute__((hot)) __attribute__((pure)) create_rgb(unsigned char r, unsigned char g,
					unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

void	__attribute__((hot)) my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void		init_img(void *mlx, int width, int height, t_data *img)
{
	img->img = mlx_new_image(mlx, width, height);
	img->addr = mlx_get_data_addr(img->img,
	&(img->bits_per_pixel), &(img->line_length),
								 &(img->endian));
	img->width = width;
	img->height = height;
}

void	init_window(t_data *buf, t_plane *plane, t_window *window)
{
	window->mlx = mlx_init();
	window->win = mlx_new_window(window->mlx, window->width, window->height, "mandelbrot");
	init_img(window->mlx, window->width, window->height, buf);
	init_img(window->mlx, window->width, window->height, buf + 1);
}

void __attribute__((hot)) draw_mandelbrot(t_window *win, t_data *buf, t_plane *plane)
{
	int		y =	-1;
	int		x;
	t_point	c = (t_point){0};
	t_point	n = (t_point){0};
	t_point tmp = (t_point){0};

	while (++y < win->height)
	{
		x = -1;
		while (++x < win->width)
		{
			c.x = (x * (plane->x_max - plane->x_min) / win->width + plane->x_min);
			c.y = (y * (plane->y_min - plane->y_max) / win->height + plane->y_max);
			n = (t_point){0};
			while ((n.x * n.x + n.y * n.y) < 4 && n.val < MAX_ITER)
			{
				tmp = (t_point){n.x, n.y, 0};
				n = (t_point){tmp.x * tmp.x - tmp.y * tmp.y + c.x, 2 * tmp.x * tmp.y + c.y, n.val + 1};
			}
			if (n.val == MAX_ITER)
				my_mlx_pixel_put(buf, x, y, 0x0);
			else
				my_mlx_pixel_put(buf, x, y,
				create_rgb((3 * n.val), (1 * n.val), (10 * n.val)));
		}
	}
}

void	draw_cross(t_data *img, int x, int y, int size)
{
	int x0 = x - size / 2 - 1;
	int y0 = y - size / 2 - 1;

	while (++x0 < x + size / 2)
		my_mlx_pixel_put(img, x0, y, 0xFFFFFF);
	while (++y0 < y + size / 2)
		my_mlx_pixel_put(img, x, y0, 0xFFFFFF);
}

int		loop_handler(t_game *game)
{
	static clock_t	t0 = 0;
	static int		i = 0;
	static int		mouse_x;
	static int		mouse_y;
	t_window		*window = (game->win);
	t_data			*buffers = game->buffs;
	t_plane			*plane = (game->plane);

	printf("x %d y %d\n", game->cursor_x, game->cursor_y);
	if (clock() - t0 >= CLOCKS_PER_SEC / FRAMECAP)
	{
		key_handler(game->keys, game);
		draw_mandelbrot(window, buffers + i, plane);
		draw_cross(buffers + i, game->cursor_x, game->cursor_y, 10);
		t0 = clock();
		*plane = (t_plane){.x_min=plane->x_min * ZOOM, .x_max=plane->x_max * ZOOM, .y_min=-plane->y_min * ZOOM, .y_max=plane->y_max * ZOOM};
		*plane = (t_plane){.x_min=plane->x_min * ZOOM, .x_max=plane->x_max * ZOOM, .y_min=-plane->y_min * ZOOM, .y_max=plane->y_max * ZOOM};
		i = (i) ? 0 : 1;
		game->redraw = 1;
	}
	if (game->redraw)
	{
		mlx_put_image_to_window(window->mlx, window->win, buffers[i].img, 0, 0);
		game->redraw = 0;
	}
	return (0);
}

int			key_handler(long keys, t_game *game)
{
	if (keys & FORWARD_PRESSED_MASK)
		game->cursor_y -= CURSOR_SPEED;
	if (keys & BACKWARD_PRESSED_MASK)
		game->cursor_y += CURSOR_SPEED;
	if (keys & RIGHT_PRESSED_MASK)
		game->cursor_x += CURSOR_SPEED;
	if (keys & LEFT_PRESSED_MASK)
		game->cursor_x -= CURSOR_SPEED;
	return (0);
}

int			press_handler(int keycode, t_game *game)
{
	if (keycode == FORWARD_KEY)
		game->keys |= FORWARD_PRESSED;
	else if (keycode == BACKWARD_KEY)
		game->keys |= BACKWARD_PRESSED;
	else if (keycode == RIGHT_KEY)
		game->keys |= RIGHT_PRESSED;
	else if (keycode == LEFT_KEY)
		game->keys |= LEFT_PRESSED;
	printf("%LX\n", game->keys);
	return (0);
}

int			release_handler(int keycode, t_game *game)
{
	if (keycode == FORWARD_KEY)
		game->keys &= FORWARD_RELEASED_MASK;
	else if (keycode == BACKWARD_KEY)
		game->keys &= BACKWARD_RELEASED_MASK;
	else if (keycode == RIGHT_KEY)
		game->keys &= RIGHT_RELEASED_MASK;
	else if (keycode == LEFT_KEY)
		game->keys &= LEFT_RELEASED_MASK;
	return (0);
}

void		hooks(t_window *win, t_game *game)
{
	mlx_loop_hook(win->mlx, loop_handler, game);
	mlx_hook(win->win, KEY_PRESS, KEYPRESS_MASK, press_handler, game);
	mlx_hook(win->win, KEY_RELEASE, KEYRELEASE_MASK, release_handler, game);
}

int		main(void)
{
	t_data		buffers[2];
	t_plane		plane = (t_plane){.x_min=-2, .x_max=0.5, .y_min=-1.25, .y_max=1.25};
	t_window	window = (t_window){500, 500, 0, 0};
	t_game		game = (t_game){buffers, &window, &plane, WIN_WIDTH / 2, WIN_HEIGHT / 2, 0};

	init_window(buffers, &plane, &window);
	hooks(&window, &game);
	mlx_do_key_autorepeatoff(window.mlx);
//	for (int i = 0; i < window.width; i++)
//		my_mlx_pixel_put(&buffers, i, 200, 0xF00FFF);
	mlx_loop(window.mlx);
	return (0);
}