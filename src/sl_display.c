/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:06:00 by abollia           #+#    #+#             */
/*   Updated: 2025/03/24 13:20:10 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	sl_open_tex(mlx_image_t **img, t_data *d, char *file)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png(file);
	if (!tex)
		sl_exit_handler("Error - MLX (loading png)", 0, NULL, d);
	*img = mlx_texture_to_image(d->mlx, tex);
	if (!img)
	{
		mlx_delete_texture(tex);
		sl_exit_handler("Error - MLX (tex_to_img)", 0, NULL, d);
	}
	mlx_delete_texture(tex);
}

void	sl_display_map(t_data *d)
{
	int		x;
	int		y;
	char	tile;

	y = -1;
	while (++y < d->map.height)
	{
		x = -1;
		while (++x < d->map.width)
		{
			mlx_image_to_window(d->mlx, d->tex.e, x * TILE, y * TILE);
			tile = d->map.pattern[y][x];
			if (tile == '1')
				mlx_image_to_window(d->mlx, d->tex.w, x * TILE, y * TILE);
			else if (tile == 'C')
				mlx_image_to_window(d->mlx, d->tex.c, x * TILE, y * TILE);
			else if (tile == 'E')
				mlx_image_to_window(d->mlx, d->tex.ex, x * TILE, y * TILE);
		}
	}
	mlx_image_to_window(d->mlx, d->tex.p, d->p.p_x * TILE, d->p.p_y * TILE);
}

void	sl_display_update(t_data *d, int x, int y)
{
	char	*pos;

	pos = &d->map.pattern[y][x];
	mlx_image_to_window(d->mlx, d->tex.p, d->p.n_x * TILE, d->p.n_y * TILE);
	if (*pos == '0' || *pos == 'C' || *pos == 'P')
		mlx_image_to_window(d->mlx, d->tex.e, x * TILE, y * TILE);
	if (*pos == 'E')
		mlx_image_to_window(d->mlx, d->tex.ex, x * TILE, y * TILE);
}

void	sl_display_init(t_data *d)
{
	int		win_height;
	int		win_width;

	win_height = d->map.height * TILE;
	win_width = d->map.width * TILE;
	d->mlx = mlx_init(win_width, win_height, "so_long", false);
	if (!d->mlx)
		sl_exit_handler("Error - MLX initialization failed", 1, NULL, d);
	sl_open_tex(&d->tex.w, d, "textures/wall.png");
	sl_open_tex(&d->tex.e, d, "textures/empty.png");
	sl_open_tex(&d->tex.p, d, "textures/player.png");
	sl_open_tex(&d->tex.c, d, "textures/collec.png");
	sl_open_tex(&d->tex.ex, d, "textures/exit.png");
	if (!d->tex.w || !d->tex.e || !d->tex.p || !d->tex.c || !d->tex.p)
		sl_exit_handler("Error - MLX failed to load image", 1, NULL, d);
}
