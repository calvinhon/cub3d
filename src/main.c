/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:35:32 by nth          #+#    #+#             */
/*   Updated: 2024/10/07 06:14:48 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macros.h"
#include "minirt.h"
#include "mlx.h"
#include "keys.h"

void errors(int err_code, char *err_ms, void *ptr)
{
	t_minirt *minirt;

	minirt = (t_minirt *)ptr;
	if (minirt)
		free_minirt(minirt);
	ft_putstr_fd(err_ms, 2);
	exit(err_code);
}

static t_minirt *init_minirt(void)
{
	t_minirt *minirt;

	minirt = ft_calloc(1, sizeof(t_minirt));
	if (!minirt)
		errors(CER_MALLOC, ER_MALLOC, NULL);
	minirt->mlx = mlx_init();
	if (!minirt->mlx)
		errors(CER_MLX, ER_MLX, minirt);
	minirt->win = mlx_new_window(minirt->mlx, FRAME_W, FRAME_H, "miniRT");
	if (!make_window(minirt, FRAME_W, FRAME_H))
		errors(CER_MLX_WIN, ER_MLX_WIN, minirt);
	//
	minirt->first_time = true;
	minirt->state_changed = false;
	//
	minirt->textures = NULL;
	minirt->selected.is_cam = true;
	minirt->selected.object = NULL;
	return (minirt);
}

static void check_filename(char *file)
{
	size_t len;

	len = ft_strlen(file);
	if (len < 3)
		errors(CER_FILE, ER_FILE, NULL);
	else if (!ft_strnstr(file + (len - 3), ".rt", len))
		errors(CER_NOT_RT, ER_NOT_RT, NULL);
	if (access(file, F_OK) != 0)
		errors(CER_NO_FILE, ER_NO_FILE, NULL);
}

int main(int ac, char **av)
{
	t_minirt *minirt;

	if (ac != 2)
		errors(CER_AGC, ER_AGC, NULL);
	check_filename(av[1]);
	minirt = init_minirt();
	parse(av[1], minirt);
	// int x = -1;
	// int y = -1;
	// while (++y < minirt->cam.vsize - 1)
	// {
	// 	while (++x < minirt->cam.hsize - 1)
	// 		render_pixel(minirt, x, y);
	// 	x = -1;
	// }
	// mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->frame.ptr, 0, 0);

	t_ray r;
	t_point p;
	t_vec4d d;
	t_object c;
	// t_itx_grp xs;

	p = create_point(2, 2, 0);
	d = create_vec4d(-1, 0, 0);
	r = create_ray(&p, &d);
	c.inv_transform = identity_mat();
	// xs.count = 0;
	// intersect_cube(&r, &c, &xs);
	// printf("%d\n", xs.count);
	// if (xs.count > 0)
	// 	printf("%.2f %.2f\n", xs.arr[0].t, xs.arr[1].t);
	t_point wrld_p;
	t_vec4d wrld_normal;
	wrld_p = create_point(-1, -1, -1);
	wrld_normal = cube_normal_at(&c, &wrld_p);
	printf("%.2f %.2f %.2f\n", wrld_normal.x, wrld_normal.y, wrld_normal.z);

	// init_core(minirt);
	// mlx_hook(minirt->win, EVENT_KEYPRESS, 1L, &record_keypress, minirt);
	// mlx_hook(minirt->win, EVENT_KEYRELEASE, 1L << 1,
	// 		 &record_keyrelease, minirt);
	// mlx_mouse_hook(minirt->win, &select_shape, minirt);
	// mlx_loop_hook(minirt->mlx, &update_minirt, minirt);

	// mlx_hook(minirt->win, EVENT_CLOSEWINDOW, 1L >> 2,
	// 		 &destroy_minirt, minirt);
	// mlx_loop(minirt->mlx);
	return (0);
}
