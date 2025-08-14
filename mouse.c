# include "rainbow.h"

int mouse_press(int button, int x, int y, t_data *data)
{
    static int last_x = -1;
    static int last_y = -1;

    printf("Mouse press detected at (%d, %d) with button %d\n", x, y, button);
    if (data->buttons == NULL || data->button_count <= 0)
    {
        printf("Error: Buttons array not initialized properly.\n");
        return (1);
    }
    if (button == 1)
    { // Left mouse button
        for (int i = 0; i < data->button_count; i++)
        {
            // Check if the click is within the bounds of a button
            if (x >= data->buttons[i].x && x <= data->buttons[i].x + data->buttons[i].width &&
                y >= data->buttons[i].y && y <= data->buttons[i].y + data->buttons[i].height) {

                // Check and call the callback if it exists
                if (data->buttons[i].callback) {
                    printf("Executing callback for button %s\n", data->buttons[i].label_on);
                    data->buttons[i].callback(data);
                    return (0);
                }

                // Check and toggle state if it exists
                if (data->buttons[i].state) {
                    printf("Toggling state for button %s\n", data->buttons[i].label_on);
                    *(data->buttons[i].state) = !*(data->buttons[i].state);
                    return (0);
                }

                printf("No callback or state for button %s\n", data->buttons[i].label_on);
            }
        }

        // If not clicking a button, draw and connect lines
        if (last_x != -1 && last_y != -1)
        {
            draw_line(data, last_x, last_y, x, y); // Connect the line
        }
        draw_dot(x, y, data); // Draw a dot at the current position

        // Update the last coordinates
        last_x = x;
        last_y = y;
    }
    else if (button == 2)
    { // Reset last coordinates on middle mouse button
        last_x = -1;
        last_y = -1;
    }
    else if (button == 3)
    { // Right mouse button for free drawing
        data->right_mouse_button = 1;
        draw_dot(x, y, data); // Start drawing a dot
    }
    return (0);
}





int mouse_release(int button, int x, int y, t_data *data)
{
	if (button == 3)
		data->right_mouse_button = 0;
	return (0);
}

int mouse_move(int x, int y, t_data *data)
{
	if (data->right_mouse_button)
	{
		pp(data, x, y, 0xFFFFFF);
	}
	return (0);
}

int mouse_hook(int button, int x, int y, t_data *data) {
    if (button == 1) { // Left mouse button
        for (int i = 0; i < data->button_count; i++){
            if (x >= data->buttons[i].x && x <= data->buttons[i].x + data->buttons[i].width &&
                y >= data->buttons[i].y && y <= data->buttons[i].y + data->buttons[i].height) {
                // Toggle button state
                *(data->buttons[i].state) = !*(data->buttons[i].state);
                printf("Button '%s' toggled. New state: %s\n",
                       *(data->buttons[i].state) ? data->buttons[i].label_on : data->buttons[i].label_off,
                       *(data->buttons[i].state) ? "ON" : "OFF");
                return (0); // Stop further processing if a button is clicked
            }
        }
    }
    return (0);
}


