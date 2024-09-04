#include "cub3d.h"

int main(int ac, char **av)
{
    t_ray *ray;

    (void)ac;
    (void)av;
    ray = (t_ray *)malloc(sizeof(t_ray));
    if (!ray)
    {
        ft_printf("Error\nmalloc() failed\n", 2);
        exit(1);
    }
    init_ray(ray);

    printf("screen_width: %d\n", ray->screen_width);
    printf("screen_height: %d\n", ray->screen_height);
    printf("screen_half_width: %d\n", ray->screen_half_width);
    printf("screen_half_height: %d\n", ray->screen_half_height);
    printf("render_delay: %d\n", ray->render_delay);
    printf("player_fov: %f\n", ray->player_fov);
    printf("player_half_fov: %f\n", ray->player_half_fov);
    printf("player_x: %f\n", ray->player_x);
    // if (ac != 2)
    // {
    //     ft_printf(RED"Error:\nNumber of arguments is incorrect:" WHITE"require format (./cub3d file.cub)");
    //     return (1);
    // }
    // data = malloc(sizeof(t_data));
    // if (!data)
    // {
    //     ft_printf("Error\nmalloc() failed\n", 2);
    //     exit(1);
    // }
    // data->fd_map = open_file(av[1], data);
    // data->read_file = read_file_to_string(data->fd_map, data);
    // string_to_tab(data->read_file);
    // clean_return(data);
    return (0);
}
