# include "rainbow.h"

void	toggle(int *value, const char *label)
{
	*value = !*value;
	printf("%s toggled. Enabled: %d\n", label, *value);
}

int	handle(int keycode, t_data *data)
{
	if (keycode == EFFECT_1)
	{
		data->effect_1 += 0.01;
		if (data->effect_1 > 100)
			data->effect_1 = 100;
		printf("Effect 1 increased. Value: %f\n", data->effect_1);
	}
	else if (keycode == EFFECT_3)
	{
		data->effect_1 -= 0.01;
		if (data->effect_1 < 0)
			data->effect_1 = 0;
		printf("Effect 1 decreased. Value: %f\n", data->effect_1);
	}
	else if (keycode == HUE_INCREASE)
	{
		data->hue += 10;
		if (data->hue >= 360)
			data->hue -= 360;
		printf("Hue increased. Value: %f\n", data->hue);
	}
	else if (keycode == HUE_DECREASE)
	{
		data->hue -= 10;
		if (data->hue < 0)
			data->hue += 360;
		printf("Hue decreased. Value: %f\n", data->hue);
	}
	else if (keycode == SATURATION_INCREASE)
	{
		data->saturation += 0.01;
		if (data->saturation > 10)
			data->saturation = 10;
		printf("Saturation increased. Value: %f\n", data->saturation);
	}
	else if (keycode == SATURATION_DECREASE)
	{
		data->saturation -= 0.01;
		if (data->saturation < 0)
			data->saturation = 0;
		printf("Saturation decreased. Value: %f\n", data->saturation);
	}
	else if (keycode == VALUE_INCREASE)
	{
		data->value += 0.01;
		if (data->value > 1)
			data->value = 1;
		printf("Value increased. Value: %f\n", data->value);
	}
	else if (keycode == VALUE_DECREASE)
	{
		data->value -= 0.01;
		if (data->value < 0)
			data->value = 0;
		printf("Value decreased. Value: %f\n", data->value);
	}
	else if (keycode == UP_KEY)
	{
		data->speed += 15;
		if (data->speed > 5000)
			data->speed = 5000;
		printf("Animation speed increase. Frames: %d\n", data->speed);
	}
	else if (keycode == DOWN_KEY)
	{
		data->speed -= 15;
		if (data->speed < 1)
			data->speed = 1;
		printf("Animation speed decreased. Frames: %d\n", data->speed);
	}
	else if (keycode == ZOOM_IN)
	{
		data->zoom += 0.1;
		printf("Zoom in. Value: %f\n", data->zoom);
	}
	else if (keycode == ZOOM_OUT)
	{
		data->zoom -= 0.1;
		if (data->zoom < 0.1)
			data->zoom = 0.1;
		printf("Zoom out. Value: %f\n", data->zoom);
	}
	else if (keycode == ZOOM_RESET)
	{
		data->zoom = 1;
		data->x_value = 1;
		data->z_value = 1;
		initialize_cube(cube, data);
		printf("Zoom reset. Value: %f\n", data->zoom);
		printf("Cube reset. Value: %f\n", data->x_value);
		printf("Cube reset. Value: %f\n", data->z_value);
	}
	else if (keycode == OBJECT_CLEAR)
	{
		clear_object_mask(data);
		printf("Object mask cleared.\n");
	}
	else if (keycode == X_INCREASE)
	{
		data->x_value++;
		initialize_cube(cube, data);
		printf("X axis rotation increased. Value: %f\n", data->angle_x);
	}
	else if (keycode == X_DECREASE)
	{
		data->x_value--;
		initialize_cube(cube, data);
		printf("X axis rotation decreased. Value: %f\n", data->angle_x);
	}
	else if (keycode == Z_INCREASE)
	{
		data->z_value += 1;
		initialize_cube(cube, data);
		printf("Z axis rotation increased. Value: %f\n", data->angle_z);
	}
	else if (keycode == Z_DECREASE)
	{
		data->z_value -= 1;
		initialize_cube(cube, data);
		printf("Z axis rotation decreased. Value: %f\n", data->angle_z);
	}
	else if (keycode == MOVE_LEFT)
	{
		if (data->center_x_enabled)
			data->translate_x -= 0.1; // Move left on X axis
		if (data->center_y_enabled)
			data->translate_y -= 0.1; // Move down on Y axis
		if (data->center_z_enabled)
			data->translate_z -= 0.1; // Move backward on Z axis
		printf("Translation after MOVE_LEFT: (%f, %f, %f)\n",
			data->translate_x, data->translate_y, data->translate_z);
	}
	else if (keycode == MOVE_RIGHT)
	{
		if (data->center_x_enabled)
			data->translate_x += 0.1; // Move right on X axis
		if (data->center_y_enabled)
			data->translate_y += 0.1; // Move up on Y axis
		if (data->center_z_enabled)
			data->translate_z += 0.1; // Move forward on Z axis
		printf("Translation after MOVE_RIGHT: (%f, %f, %f)\n",
			data->translate_x, data->translate_y, data->translate_z);
		printf("Center after MOVE_RIGHT: (%f, %f, %f)\n", data->center_x, data->center_y, data->center_z);
	}
	else if (keycode == SPHERE_CIRCLE)
	{
		data->sphere_rig += 1;
		initialize_sphere(data, &data->sphere, &data->sphere_vertex_count, 1.0, 30, 30);
		printf("Sphere circle toggled. Value: %d\n", data->sphere_rig);
	}
	else if (keycode == SCALE_UP)
	{
		if (data->cube_toggle)
			data->scale_cube += 1;
		if (data->sphere_toggle)
			data->scale_sphere += 1;
		if (data->torus_toggle)
			data->scale_torus += 1;
	}
	else if (keycode == SCALE_DOWN)
	{
		if (data->cube_toggle)
			data->scale_cube -= 1;
		if (data->sphere_toggle)
			data->scale_sphere -= 1;
		if (data->torus_toggle)
			data->scale_torus -= 1;
	}
	else if (keycode == PROJECTION_MODE)
	{
		data->projection_mode = (data->projection_mode + 1) % 5; // Cycle through modes
		printf("Projection mode changed to: ");
		if (data->projection_mode == PROJECTION_PERSPECTIVE)
			printf("Perspective\n");
		else if (data->projection_mode == PROJECTION_ORTHOGRAPHIC)
			printf("Orthographic\n");
		else if (data->projection_mode == PROJECTION_ISOMETRIC)
			printf("Isometric\n");
		else if (data->projection_mode == PROJECTION_OBLIQUE)
			printf("Oblique\n");
		else if (data->projection_mode == PROJECTION_AXONOMETRIC)
			printf("Axonometric\n");
	}
	else if (keycode == ANGLE_INCREASE)
	{
		data->ang += 0.1;
		printf("Angle increased. Value: %f\n", data->ang);
	}
	else if (keycode == ANGLE_DECREASE)
	{
		data->ang -= 0.1;
		printf("Angle decreased. Value: %f\n", data->ang);
	}
	else if (keycode == ESC_KEY)
	{
		mlx_destroy_image(data->connect, data->image);
		mlx_destroy_window(data->connect, data->window);
		mlx_destroy_display(data->connect);
		free(data->connect);
		exit(0);
	}
	return (0);
}
