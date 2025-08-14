/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshannak <wshannak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:03:18 by wshannak          #+#    #+#             */
/*   Updated: 2024/12/16 21:46:43 by wshannak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rainbow.h"

void clear_object_mask(t_data *data)
{
	memset(data->object_mask, 0, data->snx * data->sny);
}
void apply_rainbow_to_objects(t_data *data)
{
	int x;
	int y;
	int r;
	int g;
	int b;
	int color;
	float hue;

	y = 0;
	x = 0;
	while (y < data->sny)
	{
		x = 0;
		while (x < data->snx)
		{

			if (data->object_mask[y * data->snx + x] == 1) // Only apply to objects
			{
				// Use the global hue and position to calculate the dynamic hue
				hue = fmod(data->current_hue + (x + y) * data->effect_1, 360);
				hsv_to_rgb(hue, data->saturation, data->value, &r, &g, &b);
				color = (r << 16) | (g << 8) | b;
				pp(data, x, y, color);
			}
			x++;
		}
		y++;
	}
}

int	animation_loop(t_data *data)
{
	static float	hue_offset;
	int	combined_hue;
	static float	angle_x;
	static float	angle_y;
	static float	angle_z;

	mlx_do_sync(data->connect);
	if (data->image)
		mlx_destroy_image(data->connect, data->image);
	data->image = mlx_new_image(data->connect, data->snx, data->sny);
	data->buffer = mlx_get_data_addr(data->image, &data->bpp, &data->linelen, &data->endian);
	if (data->animating)
	{
		data->frame_count++;
		if (data->frame_count >= data->speed)
		{
			data->frame_count = 0;
			hue_offset = fmod(hue_offset + 2, 360); // Cycle the hue smoothly

			mlx_clear_window(data->connect, data->window);
			if (data->background_enabled)
				draw_solid_background(data, 0x000000);
			if (data->grid_enabled)
					draw_solid_grid(data, 0x00FF00);
			if (data->spiral_enabled)
				draw_spiral(data, data->snx / 2, data->sny / 2, 0, 0.1, 1, 1000);
			if (data->shape_animation)
			{
				data->angle_x += 0.005; // Smaller step for smoother rotation
				data->angle_y += 0.003;
				data->angle_z += 0.004;
			}
			if (data->cube_toggle)
				draw_cube(data, cube, data->scale_cube);
			if (data->sphere_toggle)
				draw_sphere(data, data->sphere, data->sphere_vertex_count, data->sphere_circle, data->sphere_rotate, data->scale_sphere);
			if (data->torus_toggle)
			{
				draw_torus(data, data->torus, 31, 30, data->scale_torus /2);
			}
			//draw_cord(data);
			if (data->object_rainbow) // keep me last to apply the rainbow effect
			{
				data->current_hue = fmod(data->hue + hue_offset, 360);
				apply_rainbow_to_objects(data);
			}
			mlx_put_image_to_window(data->connect, data->window, data->image, 0, 0);
			draw_buttons(data, data->buttons, data->button_count);
			mlx_do_sync(data->connect);
		}
	}
	return (0);
}

