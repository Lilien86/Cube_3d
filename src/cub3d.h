#ifndef CUB3D_H
# define CUB3D_H

# define BUFFER_SIZE 1024

//COLORS
# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define MAGENTA	"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include <time.h>
# include <sys/time.h>
# include "../Libft/libft.h"
# include <math.h>


typedef struct s_data t_data;
typedef struct s_read_file t_read_file;

typedef struct s_read_file
{
	t_data  *data;
	char    **tab_content;
	char    buffer[BUFFER_SIZE];
	char    *str_content;
	ssize_t bytes_read;
	size_t  total_size;
	size_t  new_size;
} t_read_file;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

// RAYCASTING & GRAPHICS
typedef struct s_ray
{
	void        *mlx;
	void        *mlx_win;
	void        *img;
	int         *addr;
	int         bpp;
	int         line_length;
	int         endian;

	int     screen_width;
	int     screen_height;
	int		screen_half_width;
	int		screen_half_height;
	int		render_delay;
	double	player_fov;
	double	player_half_fov;
	double	ray_increment_angle;
	int		raycasting_precision;
	int		**map;
	double	player_angle;
	double	pos_x;
	double	pos_y;
	double  dir_x;
	double  dir_y;
	double  plane_x;
	double  plane_y;
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	double  time;
	double  old_time;
	int     map_x;
	int     map_y;
	double  side_dist_x;
	double  side_dist_y;
	double  delta_dist_x;
	double  delta_dist_y;
	double  perp_wall_dist;
	int     step_x;
	int     step_y;
	int     hit;
	int     side;
	int     line_height;
	int     draw_start;
	int     draw_end;
	double  move_speed;
	double  rot_speed;
	double  frame_time;

} t_ray;

typedef struct s_data
{
	int         fd_map;
	t_read_file *read_file;
} t_data;

//INIT
void	init_ray(t_ray *ray);
//int		init_graphics(t_graphics *graph);

//FILE
int         open_file(char *file, t_data *data);
t_read_file *read_file_to_string(int fd, t_data *data);
void        string_to_tab(t_read_file *rf);
int			key_hook(int keycode, t_ray *ray);

void parse_map(t_ray *ray, char **char_map, int **int_map, int width, int height);
//EXITS
void    clean_exit(t_data *data);
void    clean_return(t_data *data);
void	cleanup_graphics(t_ray *ray);

#endif