# include "rainbow.h"
void	draw_solid_background(t_data *data, int color)
{
	int	x;
	int	y;
	int	offset;

	x = 0;
	while (x < data->snx)
	{
		y = 0;
		while (y < data->sny)
		{
			offset = (y * data->linelen) + (x * (data->bpp / 8));
			*(unsigned int *)(data->buffer + offset) = color;
			data->object_mask[y * data->snx + x] = 0;
			y++;
		}
		x++;
	}
}
void	draw_solid_grid(t_data *data, int color)
{
	int	x;
	int	y;
	int	grid_density;

	x = 0;
	grid_density = 10;
	while (x < data->snx)
	{
		y = 0;
		while (y < data->sny)
		{
			if (x % grid_density == 0 || y % grid_density == 0)
			{
				pp(data, x, y, color);
			}
			y++;
		}
		x++;
	}
}
void draw_spiral(t_data *data, int center_x, int center_y, float start_radius, float angle_increment, float radius_increment, int num_points)
{
	float angle;
	float radius;
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	i;

	i = 0;
	angle = 0;
	radius = start_radius;
	x1 = center_x + (int)(radius * cos(angle));
	y1 = center_y + (int)(radius * sin(angle));
	while (i < num_points)
	{
		angle += angle_increment;
		radius += radius_increment;
		x2 = center_x + (int)(radius * cos(angle));
		y2 = center_y + (int)(radius * sin(angle));
		if (data->spiral_line)
			draw_line(data, x1, y1, x2, y2);
		else
			pp(data, x1, y1, 0xFFFFFF);
		x1 = x2;
		y1 = y2;
		i++;
	}
}
