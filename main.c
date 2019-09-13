/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 22:37:07 by oouklich          #+#    #+#             */
/*   Updated: 2019/08/16 11:43:48 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <float.h>
# include <pthread.h>
# define MLX_KEY_ESC 53
typedef struct	s_ptr
{
    void		*win;
    void		*mlx;
    void		*img;
    int			*data;
    int			*bpp;
    int			*size;
    int			*endian;
}				t_ptr;

void	ft_free_exit(char *display, int err, t_ptr **p)
{
    char	*msg;

    msg = ft_strjoin(err ? "error: " : "", display);
    ft_putstr(msg);
    free(msg);
    free(*p);
    exit(0);
}

int			ft_close(t_ptr *p)
{
    mlx_destroy_image(p->mlx, p->img);
    mlx_destroy_window(p->mlx, p->win);
    free(p->bpp);
    free(p->size);
    free(p->endian);
    ft_free_exit("", 0, &p);
    return (0);
}

int			ft_deal_key(int key, t_ptr *p)
{
    if (key == MLX_KEY_ESC)
        ft_close(p);
    return (1);
}

int		main(int argc, char **argv)
{
	t_ptr	*p;
	int width = 0;
	int height = 0;
	int fd;
	char *line = NULL;
	char **each;

	if (!(p = (struct s_ptr*)malloc(sizeof(struct s_ptr))))
		return (0);
	if (argc != 2 && argc != 6)
        ft_free_exit("Usage : ./loadxpm file.xpm\n        ./loadxpm file.xpm -w width -h height\n", 0, &p);
    if ((fd = open(argv[1], O_RDONLY)) == -1)
        ft_free_exit(ft_strjoin(argv[1], " : No such file\n"), 1, &p);
    if (read(fd, line, 0) < 0)
        ft_free_exit(ft_strjoin(argv[1], " : must be a file\n"), 1, &p);
    if (argc == 6) {
        if (ft_strcmp(argv[2], "-w") != 0 || ft_strcmp(argv[4], "-h"))
            ft_free_exit("wrong usage\n", 1, &p);
        width = ft_atoi(argv[3]);
        height = ft_atoi(argv[5]);
    }
    else
    {
        while (get_next_line(fd, &line) > 0) {
            if (line[ft_strlen(line) - 1] == ',' && line[0] == '\"') {
                each = ft_strsplit(ft_strsub(line, 1, ft_strlen(line) - 2), ' ');
                width = ft_atoi(each[0]);
                height = ft_atoi(each[1]);
                ft_free_twodim(each);
                break;
            }
            free(line);
        }
    }
    p->bpp = malloc(4);
    p->size = malloc(4);
    p->endian = malloc(4);
    p->mlx = mlx_init();
    p->win = mlx_new_window(p->mlx, width, height, argv[1]);
    p->img = mlx_xpm_file_to_image((void*)p->mlx, argv[1], &width, &height);
    if (!p->img)
        ft_free_exit("wrong texture detected\n", 1, &p);
    p->data = (int *)mlx_get_data_addr(p->img, p->bpp, p->size, p->endian);
    mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
    mlx_hook(p->win, 17, 0, ft_close, p);
    mlx_hook(p->win, 2, 0, ft_deal_key, p);
	mlx_loop(p->mlx);
	return (0);
}
