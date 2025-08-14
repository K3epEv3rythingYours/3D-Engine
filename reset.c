# include "rainbow.h"

void initialize_data(t_data *data)
{
	// Initialize MLX and graphics resources
	data->connect = mlx_init();
	data->snx = 1920;
	data->sny = 1080;
	data->window = mlx_new_window(data->connect, data->snx, data->sny, "42 FDF");
	data->image = mlx_new_image(data->connect, data->snx, data->sny);
	data->buffer = mlx_get_data_addr(data->image, &data->bpp, &data->linelen, &data->endian);

	// Object mask
	data->object_mask = calloc(data->snx * data->sny, sizeof(unsigned char));
	data->object_rainbow = 0;
	data->line_algorithm = 0;

	// Animation control
	data->animating = 1;
	data->speed = 10;
	data->frame_count = 1;
	data->effect_1 = 0.05;
	data->hue = 0;
	data->current_hue = 0;
	data->saturation = 1;
	data->value = 1;

	// Background control
	data->background_enabled = 0;

	// Grid control
	data->grid_enabled = 0;

	// Spiral control
	data->spiral_enabled = 0;
	data->spiral_line = 0;

	// Zoom control
	data->zoom = 1;

	// Mouse right button
	data->right_mouse_button = 0;

	// Shape control
	data->cube_toggle = 0;
	data->shape_animation = 1;
	data->angle_x = 0.0;
	data->angle_y = 5.0;
	data->angle_z = 0.0;
	data->cube_rotate_x = 0;
	data->cube_rotate_y = 0;
	data->cube_rotate_z = 0;
	data->x_value = 1;
	data->z_value = 1;
	data->translate_x = 0.0;
	data->translate_y = 0.0;
	data->translate_z = 0.0;
	data->scale_cube = 100.0;
	data->scale_sphere = 100.0;
	data->scale_torus = 100.0;

	data->center_x = 0.0;
	data->center_y = 0.0;
	data->center_z = 0.0;

	data->center_x_enabled = 0;
	data->center_y_enabled = 0;
	data->center_z_enabled = 0;
	data->sphere_toggle = 0;
	data->sphere_circle = 30;
	data->sphere_rotate = 30;
	data->sphere_rig = 5;
	data->torus_toggle = 0;
	data->projection_mode = PROJECTION_ISOMETRIC;

	initialize_torus(&data->torus, &data->torus_vertex_count, 5.0, 2.3, 30, 30);
	initialize_sphere(data, &data->sphere, &data->sphere_vertex_count, 1.0, 30, 30);
	initialize_cube(cube, data);

}

void	reset_all(struct s_data *data)
{
	data->zoom = 1;
	data->x_value = 1;
	data->z_value = 1;
	data->angle_x = 0;
	data->angle_y = 0;
	data->angle_z = 0;
	data->background_enabled = 0;
	data->cube_toggle = 0;
	data->shape_animation = 1;
}
