/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:03:42 by abollia           #+#    #+#             */
/*   Updated: 2025/04/15 12:48:21 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/inc/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>

/* ************************************************************************** */
/*-------------------------\\\\\___VARIABLES___/////--------------------------*/
# define TILE 100

/*--------------------------\\\\\___STRUCTS___/////---------------------------*/
typedef struct s_map
{
	int			infile_fd;
	int			line_count;
	char		**pattern;
	int			width;
	int			height;
	int			start_tile;
	int			exit_tile;
	int			collec_tile;
	int			empty_tile;
	int			wall_tile;
}	t_map;

typedef struct s_tex
{
	mlx_image_t	*w;
	mlx_image_t	*e;
	mlx_image_t	*p;
	mlx_image_t	*c;
	mlx_image_t	*ex;
	mlx_image_t	*win;
}	t_tex;

typedef struct s_play
{
	int	p_x;
	int	p_y;
	int	n_x;
	int	n_y;
}	t_play;

typedef struct s_data
{
	int				win;
	int				mcount;
	mlx_t			*mlx;
	struct s_map	map;
	struct s_tex	tex;
	struct s_play	p;
}	t_data;

/*------------------------\\\\\___INITIALIZERS___/////------------------------*/
void	sl_init_data(t_data *data);
void	sl_init_player(t_data *data);

/*---------------------------\\\\\___UTILS___/////----------------------------*/
void	sl_exit_handler(char *message, int errcode, char *tofree, t_data *data);
int		sl_map_error(char *message);
void	sl_terminate(t_data *d);

/*---------------------\\\\\___INPUT_MANAGEMENT___/////-----------------------*/
void	sl_read_infile(char *infile, t_data *data);

/*--------------------------\\\\\___PARSING___/////---------------------------*/
int		sl_map_check(t_data *data);
int		sl_map_respath(t_data *data);

/*--------------------------\\\\\___DISPLAY___/////---------------------------*/
void	sl_display_init(t_data *data);
void	sl_display_map(t_data *d);
void	sl_display_update(t_data *d, int x, int y);

/*---------------------------\\\\\___GAME___/////-----------------------------*/
void	sl_game_input(mlx_key_data_t keydata, void *param);
void	sl_game_close(void *param);

/* ************************************************************************** */

#endif