#include "rainbow.h"

// Function to draw buttons
void draw_buttons(t_data *data, Button *buttons, int button_count)
{
	int	color;
	int	i;

	i = 0;
	while (i < button_count)
	{
		// Determine button color based on its specific state
		if (*(buttons[i].state))
			color = 0x00FF00;
		else
			color = 0x555555;
		// Draw button background
		button_draw(data, buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height, color);
		// Draw button label with the specific button's state
		button_control(data, buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height,
			0x000000, 0xFFFFFF, buttons[i].label_on, buttons[i].label_off, buttons[i].state);
		i++;
	}
}


// Function to draw a button
void button_draw(t_data *data, int x_start, int y_start, int width, int height, int color) {
	int	offset;
	int	y;
	int	x;

	y = y_start;
	x = x_start;
	while (x < x_start + width)
	{
		y = y_start;
		while (y < y_start + height)
		{
			offset = (y * data->linelen) + (x * (data->bpp / 8));
			*(unsigned int *)(data->buffer + offset) = color;
			data->object_mask[y * data->snx + x] = 0;
			y++;
		}
		x++;
	}
}

// Function to control a button
void button_control(t_data *data, int x_start, int y_start, int width, int height, int color_on, int color_off, const char *label_on, const char *label_off, int *state)
{
	const char	*label;
	int	label_color;
	int	label_width;
	int	label_x;
	int	label_y;

	if (*state)
	{
		label = label_on;
		label_color = color_on;
	}
	else
	{
		label = label_off;
		label_color = color_off;
	}
	label_width = strlen(label) * 8;
	label_x = x_start + (width - label_width + 10) / 2;
	label_y = y_start + (height + 5) / 2;

    mlx_string_put(data->connect, data->window, label_x, label_y, label_color, (char *)label); // Draw the label
}

