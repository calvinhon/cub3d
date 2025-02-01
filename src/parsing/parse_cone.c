/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:34:49 by nth          #+#    #+#             */
/*   Updated: 2025/01/14 18:20:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "macros.h"
// #include "libft.h"
#include "colors.h"

// static void	set_material_1(t_material *material, char *data, size_t *i, t_minirt *minirt)
//{
//     t_vec4d color_vec;

//    color_vec = material->color.v;
//    material->xordc = (t_color)
//	{
//        .v.a[0] = (int)color_vec.a[0] ^ 1,
//        .v.a[1] = (int)color_vec.a[1] ^ 1,
//        .v.a[2] = (int)color_vec.a[2] ^ 1,
//        .v.a[3] = (int)color_vec.a[3] ^ (OS_MACOS == 0)
//    };
//	material->ambient = 0.1;
//	material->diffuse = 0.9;
//	material->specular = 0.9;
//	material->shininess = 200;
//	material->reflective = 0.0;
//	material->transparency = 0.0;
//	material->refractive_index = 1.0;
//	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
//		(*i)++;
//	//test
//	printf("data[%ld] = %c\n", *i, data[*i]);

//	if (data[*i] == 'M')
//	{
//		(*i)++;
//		parse_material(material, data, i, minirt);
//	}
//}

bool parse_cone(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_object *cone;
	float height;
	t_point t;

	(*i) += 2;
	cone = minirt->scene.shapes + idx;
	cone->type = CONE;
	t = parse_point(data, i);
	cone->translate = translation_mat(t.x, t.y, t.z);
	cone->orientation = parse_vector(data, i);
	is_normalised(&cone->orientation, *i, minirt);
	cone->radius = parse_float(data, i) / 2.0f;
	//
	cone->specs.min_y = parse_float(data, i);
	cone->specs.max_y = parse_float(data, i);
	height = cone->specs.max_y - cone->specs.min_y;
	//cone->specs.min_y = -height / 2.0f;
	//cone->specs.max_y = height / 2.0f;
	cone->specs.closed = false;
	cone->material.color = parse_color(data, i, minirt);
	set_material(&cone->material, data, i, minirt);
	cone->scale = scaling_mat(cone->radius, height, cone->radius);
	cone->rot = rt_extract_rot_vertical(cone->orientation);
	cone->inv_transform = mult_n_mat4d(3,
			&cone->rot, &cone->scale, &cone->translate);
	cone->inv_transform = inverse_mat4d(&cone->inv_transform);
	/*
		// test
	printf("shape[%ld], type = %d\n", idx, cone->type);// test
	//test
	printf("cone position = %f, %f, %f\n", (minirt->scene.shapes + idx)->trans.x, \
		(minirt->scene.shapes + idx)->trans.y, (minirt->scene.shapes + idx)->trans.z);
	// test
	printf("cone radius =  %f\n", (minirt->scene.shapes + idx)->radius);
	//test
	printf("cone color = %f, %f, %f\n", (minirt->scene.shapes + idx)->material.color.r, \
		(minirt->scene.shapes + idx)->material.color.g, (minirt->scene.shapes + idx)->material.color.b);
	*/
	return (true);
}
