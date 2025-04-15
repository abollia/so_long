/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:36:52 by abollia           #+#    #+#             */
/*   Updated: 2025/03/25 13:54:10 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_exit_handler(char *message, int errcode, char *tofree, t_data *data)
{
	if (errcode)
		ft_dprintf(2, "%s\n", message);
	else
		perror(message);
	if (tofree)
		free(tofree);
	if (data)
	{
		if (data->map.pattern)
		{
			ft_ffa(data->map.pattern);
			data->map.pattern = NULL;
		}
		if (data->map.infile_fd != -1)
		{
			close(data->map.infile_fd);
			data->map.infile_fd = -1;
		}
		if (data->mlx != NULL)
			mlx_terminate(data->mlx);
	}
	exit(EXIT_FAILURE);
}

int	sl_map_error(char *message)
{
	ft_dprintf(2, "Map Error - %s\n", message);
	return (1);
}

void	sl_init_data(t_data *data)
{
	data->win = 0;
	data->mcount = 0;
	data->map.infile_fd = -1;
	data->map.line_count = 0;
	data->map.pattern = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->map.start_tile = 0;
	data->map.exit_tile = 0;
	data->map.collec_tile = 0;
	data->map.empty_tile = 0;
	data->map.wall_tile = 0;
	data->tex.e = NULL;
	data->tex.w = NULL;
	data->tex.p = NULL;
	data->tex.c = NULL;
	data->tex.ex = NULL;
	data->tex.win = NULL;
	data->mlx = NULL;
}

void	sl_init_player(t_data *data)
{
	int	x;
	int	y;

	data->p.p_x = -1;
	data->p.p_y = -1;
	data->p.n_x = -1;
	data->p.n_y = -1;
	y = -1;
	while (++y < data->map.height)
	{
		x = -1;
		while (++x < data->map.width)
		{
			if (data->map.pattern[y][x] == 'P')
			{
				data->p.p_x = x;
				data->p.p_y = y;
			}
		}
	}
}

void	sl_terminate(t_data *d)
{
	if (!d)
		return ;
	if (d->mlx)
	{
		mlx_close_window(d->mlx);
		if (d->tex.w)
			mlx_delete_image(d->mlx, d->tex.w);
		if (d->tex.e)
			mlx_delete_image(d->mlx, d->tex.e);
		if (d->tex.p)
			mlx_delete_image(d->mlx, d->tex.p);
		if (d->tex.c)
			mlx_delete_image(d->mlx, d->tex.c);
		if (d->tex.ex)
			mlx_delete_image(d->mlx, d->tex.ex);
		mlx_terminate(d->mlx);
	}
	if (d->map.pattern)
		ft_ffa(d->map.pattern);
	if (d->map.infile_fd != -1)
		close(d->map.infile_fd);
	if (d->win)
		ft_printf("-----> WELL PLAYED, YOU BEAT THE GUIGYRINTHE <-----\n");
	exit(EXIT_SUCCESS);
}
