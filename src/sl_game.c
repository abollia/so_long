/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:59:43 by abollia           #+#    #+#             */
/*   Updated: 2025/03/24 12:36:48 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_game_close(void *param)
{
	sl_terminate((t_data *)param);
}

static void	sl_game_move(t_data *d, int movy, int movx)
{
	char	*pos;

	d->p.n_x = d->p.p_x + movx;
	d->p.n_y = d->p.p_y + movy;
	pos = &d->map.pattern[d->p.n_y][d->p.n_x];
	if (*pos == '1')
		return ;
	if (*pos == 'C')
	{
		d->map.collec_tile--;
		*pos = '0';
	}
	if (*pos == 'E' && d->map.collec_tile == 0)
	{
		d->win = 1;
		sl_terminate(d);
	}
	sl_display_update(d, d->p.p_x, d->p.p_y);
	d->mcount++;
	ft_printf("So far, you moved %d times...\n", d->mcount);
	d->p.p_x = d->p.n_x;
	d->p.p_y = d->p.n_y;
}

void	sl_game_input(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		sl_terminate(data);
	else if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		&& !data->win)
		sl_game_move(data, -1, 0);
	else if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		&& !data->win)
		sl_game_move(data, 1, 0);
	else if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		&& !data->win)
		sl_game_move(data, 0, -1);
	else if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		&& !data->win)
		sl_game_move(data, 0, 1);
}
