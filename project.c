# include "rainbow.h"

Point2D project(t_data *data, Vertex p, float zoom)
{
	Point2D projected;
	float angle = M_PI / 6; // 30 degrees for isometric/axonometric
	float scale = zoom;     // Scale based on zoom
	float shear = 0.5;      // Shear factor for oblique projection

	if (data->projection_mode == PROJECTION_PERSPECTIVE) {
		float near_plane = 1;
		float far_plane = 20.0;
		float perspective_scale = (near_plane * far_plane) / (far_plane - p.z);
		projected.x = (int)(p.x * perspective_scale * zoom + data->snx / 2);
		projected.y = (int)(p.y * perspective_scale * zoom + data->sny / 2);
	}
	else if (data->projection_mode == PROJECTION_ORTHOGRAPHIC) {
		projected.x = (int)(p.x * zoom + data->snx / 2);
		projected.y = (int)(p.y * zoom + data->sny / 2);
	}
	else if (data->projection_mode == PROJECTION_ISOMETRIC) {
		projected.x = (int)(((p.x - p.y) * cos(angle) * scale) + data->snx / 2);
		projected.y = (int)(((p.x + p.y) * sin(angle) * scale - p.z * scale) + data->sny / 2);
	}
	else if (data->projection_mode == PROJECTION_OBLIQUE) {
		projected.x = (int)((p.x + shear * p.z) * zoom + data->snx / 2);
		projected.y = (int)((p.y + shear * p.z) * zoom + data->sny / 2);
	}
	else if (data->projection_mode == PROJECTION_AXONOMETRIC) {
		projected.x = (int)((p.x * cos(angle) - p.y * sin(angle)) * scale + data->snx / 2);
		projected.y = (int)((p.x * sin(angle) + p.y * cos(angle) - p.z * scale) + data->sny / 2);
	}

	return projected;
}


void	transform_vertex(t_data *data, Vertex *v)
{
	// Apply global translation
	v->x += data->translate_x;
	v->y += data->translate_y;
	v->z += data->translate_z;

	// Step 1: Translate to rotation center
	v->x -= data->center_x;
	v->y -= data->center_y;
	v->z -= data->center_z;

	// Step 2: Apply rotation
	rotate_vertex(data, v, data->angle_x, data->angle_y, data->angle_z);

	// Step 3: Translate back to the rotation center
	v->x += data->center_x;
	v->y += data->center_y;
	v->z += data->center_z;
}


void	rotate_vertex(t_data *data, Vertex *v, float angle_x, float angle_y, float angle_z)
{
	double x;
	double y;
	double z;
	double temp_x;
	double temp_y;
	double temp_z;

	x = v->x;
	y = v->y;
	z = v->z;
	if (data->cube_rotate_x)
	{
		temp_y = y * cos(angle_x) - z * sin(angle_x);
		temp_z = y * sin(angle_x) + z * cos(angle_x);
		y = temp_y;
		z = temp_z;
	}
	if (data->cube_rotate_y)
	{
		temp_x = x * cos(angle_y) + z * sin(angle_y);
		z = -x * sin(angle_y) + z * cos(angle_y);
		x = temp_x;
	}
	if (data->cube_rotate_z)
	{
		temp_x = x * cos(angle_z) - y * sin(angle_z);
		y = x * sin(angle_z) + y * cos(angle_z);
		x = temp_x;
	}
	v->x = x;
	v->y = y;
	v->z = z;
}

void	draw_cord(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = data->sny / 2;
	while (x < data->snx)
	{
		pp(data, x, y, 0xFF0000);
		x++;
	}
	x = data->snx / 2;
	y = 0;
	while (y < data->sny)
	{
		pp(data, x, y, 0x00FF00);
		y++;
	}
}
