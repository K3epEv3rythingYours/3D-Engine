#include "rainbow.h"

int	draw_dot (int x, int y, t_data *data)
{
	int	color;

	color = 0xFFFFFF;
	pp(data, x, y, color);
	return (0);
}

// Blend a pixel with fractional intensity and apply the rainbow hue
void blend_pixel_with_rainbow(t_data *data, int x, int y, float intensity, float hue) {
    if (!data || !data->buffer || x < 0 || x >= data->snx || y < 0 || y >= data->sny)
        return;

    // Apply zoom to coordinates
    x = (int)(x * data->zoom);
    y = (int)(y * data->zoom);

    if (x >= 0 && x < data->snx && y >= 0 && y < data->sny) {
        int r, g, b, blended_color, bg_r, bg_g, bg_b, offset;

        // Convert HSV to RGB
        hsv_to_rgb(hue, data->saturation, data->value, &r, &g, &b);

        offset = (y * data->linelen) + (x * (data->bpp / 8));
        bg_r = ((*(unsigned int *)(data->buffer + offset)) >> 16) & 0xFF;
        bg_g = ((*(unsigned int *)(data->buffer + offset)) >> 8) & 0xFF;
        bg_b = (*(unsigned int *)(data->buffer + offset)) & 0xFF;

        // Blend the pixel with intensity
        r = (int)(r * intensity + bg_r * (1 - intensity));
        g = (int)(g * intensity + bg_g * (1 - intensity));
        b = (int)(b * intensity + bg_b * (1 - intensity));

        blended_color = (r << 16) | (g << 8) | b;
        *(unsigned int *)(data->buffer + offset) = blended_color;
    }
}

// Xiaolin Wu's Line Algorithm
void draw_line_xiaolin(t_data *data, int x0, int y0, int x1, int y1)
{
	int steep;
	float gradient;
	float intery;
	int y;
	int xend;
	float dx;
	float dy;
	float hue;
	float hue_increment;
	int	temp;

	y += 0;
	if (data->object_rainbow == 1) // Only apply to objects
	{
		apply_zoom(data, &x0, &y0);
		apply_zoom(data, &x1, &y1);
	}
	steep = fabs(y1 - y0) > fabs(x1 - x0);
	if (steep)
	{
		// Swap x and y for steep lines
		temp = x0;
		x0 = y0;
		y0 = temp;
		temp = x1;
		x1 = y1;
		y1 = temp;
	}
	if (x0 > x1)
	{
		// Swap endpoints
		temp = x0;
		x0 = x1;
		x1 = temp;
		temp = y0;
		y0 = y1;
		y1 = temp;
	}
	dx = x1 - x0;
	dy = y1 - y0;
	if (dx == 0)
	{
		if (y1 > y0)
			gradient = 1;
		else
			gradient = -1;
	}
	else
		gradient = dy / dx;
	hue = data->current_hue; // Start hue
	hue_increment = data->effect_1; // Adjust hue increment for rainbow spread
	// Handle first endpoint
	xend = round(x0);
	y = y0 + gradient * (xend - x0);
	intery = y0 + gradient * (xend - x0); // First y-intercept
	while (xend < x1)
	{
		// Apply rainbow hue dynamically
		hue = fmod(hue + hue_increment, 360);
		if (steep)
		{
			// Plot y,x for steep lines
			blend_pixel_with_rainbow(data, (int)intery, xend, 1 - (intery - floor(intery)), hue);
			blend_pixel_with_rainbow(data, (int)intery + 1, xend, intery - floor(intery), hue);
		}
		else
		{
			// Plot x,y for non-steep lines
			blend_pixel_with_rainbow(data, xend, (int)intery, 1 - (intery - floor(intery)), hue);
			blend_pixel_with_rainbow(data, xend, (int)intery + 1, intery - floor(intery), hue);
		}
		intery += gradient; // Increment y-intercept
		xend++;
	}
}

void set_pixel_with_rainbow(t_data *data, int x, int y, float hue) {
    if (!data || !data->buffer)
        return;

    // Apply zoom to coordinates
    x = (int)(x * data->zoom);
    y = (int)(y * data->zoom);

    if (x >= 0 && x < data->snx && y >= 0 && y < data->sny) {
        int r, g, b, color;

        // Convert hue to RGB
        hsv_to_rgb(hue, data->saturation, data->value, &r, &g, &b);

        // Combine RGB into a single integer color
        color = (r << 16) | (g << 8) | b;

        // Set the pixel
        int offset = (y * data->linelen) + (x * (data->bpp / 8));
        *(unsigned int *)(data->buffer + offset) = color;
    }
}

void draw_line_bresenham(t_data *data, int x1, int y1, int x2, int y2)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;
	float hue;
	float hue_increment;

	if (data->object_rainbow == 1) // Only apply to objects
	{
		apply_zoom(data, &x1, &y1);
		apply_zoom(data, &x2, &y2);
	}
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	if (x1 < x2)
		sx = 1;
	else
		sx = -1;
	if (y1 < y2)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	hue = data->current_hue; // Start hue
	hue_increment = data->effect_1; // Adjust hue increment for rainbow spread
	while (1)
	{
		// Set the pixel with the current rainbow hue
		set_pixel_with_rainbow(data, x1, y1, hue);

		// Update hue dynamically for the rainbow effect
		hue = fmod(hue + hue_increment, 360);

		// Check if the end point is reached
		if (x1 == x2 && y1 == y2)
		break;

		// Update error and positions
		e2 = 2 * err;
		if (e2 > -dy)
		{
		err -= dy;
		x1 += sx;
		}
		if (e2 < dx)
		{
		err += dx;
		y1 += sy;
		}
	}
}

void	draw_line(t_data *data, int x0, int y0, int x1, int y1)
{
	if (data->line_algorithm == 0)
		draw_line_bresenham(data, x0, y0, x1, y1);
	else
		draw_line_xiaolin(data, x0, y0, x1, y1);
}
