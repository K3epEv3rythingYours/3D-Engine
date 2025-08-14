# include "rainbow.h"

// The "color wheel" angle (0-360 degrees), where 0 = red, 120 = green, and 240 = blue.
void	hsv_to_rgb(float h, float s, float v, int *r, int *g, int *b)
{
	float	c;
	float	x;
	float	m;
	float	r_prime;
	float	g_prime;
	float	b_prime;

	c = v * s; // value * saturation | Chroma control = difference between brightesset and darkest color;
	x = c * (1 - fabs(fmod(h / 60.0, 2) - 1)); // fabs to calculate float absolute value | fmod to caluate float remainder (mod) | second color contirubtion
	m = v - c; // the amount to add to match the brightness
	r_prime = 0;
	g_prime = 0;
	b_prime = 0;
	if (h >= 0 && h < 60)
	{
		r_prime = c;
		g_prime = x;
	}
	else if (h >= 60 && h < 120)
	{
		r_prime = x;
		g_prime = c;
	}
	else if (h >= 120 && h < 180)
	{
		g_prime = c;
		b_prime = x;
	}
	else if (h >= 180 && h < 240)
	{
		g_prime = x;
		b_prime = c;
	}
	else if (h >= 240 && h < 300)
	{
		r_prime = x;
		b_prime = c;
	}
	else
	{
		r_prime = c;
		b_prime = x;
	}
	*r = (r_prime + m) * 255;
	*g = (g_prime + m) * 255;
	*b = (b_prime + m) * 255;
}
void apply_zoom(t_data *data, int *x, int *y)
{
    *x = (*x - data->snx / 2) * data->zoom + data->snx / 2;
    *y = (*y - data->sny / 2) * data->zoom + data->sny / 2;
}

void pp(t_data *data, int x, int y, int color)
{
	int offset;

	// Apply zoom only to objects (when object_rainbow is enabled)
	if (data->object_rainbow)
	{
		x = (int)(x * data->zoom);
		y = (int)(y * data->zoom);
	}
	// Ensure within bounds
	if (x < 0 || x >= data->snx || y < 0 || y >= data->sny)
		return;

	// Calculate the pixel offset
	offset = (y * data->linelen) + (x * (data->bpp / 8));

	// Set the pixel color in the image buffer
	*(unsigned int *)(data->buffer + offset) = color;

	// Mark this pixel as part of an object
	data->object_mask[y * data->snx + x] = 1;
}
