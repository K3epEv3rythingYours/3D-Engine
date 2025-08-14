# include "rainbow.h"

int main()
{
    t_data data; // Data structure declaration
    // Initialize the data structure
    initialize_data(&data);

    // Define buttons
    Button buttons[] = {
        {1, 0, 100, 20, "CUBE ON", "CUBE OFF", &data.cube_toggle, NULL},
        {1, 25, 100, 20, "SPHERE ON", "SPHERE OFF", &data.sphere_toggle, NULL},
        {1, 50, 100, 20, "TORUS ON", "TORUS OFF", &data.torus_toggle, NULL},
        {110, 0, 100, 20, "GRID ON", "GRID OFF", &data.grid_enabled, NULL},
        {220, 0, 100, 20, "CLEAR ON", "CLEAR OFF", &data.background_enabled, NULL},
        {330, 0, 100, 20, "SPIRAL ON", "SPIRAL OFF", &data.spiral_enabled, NULL},
        {440, 0, 100, 20, "SPIRAL LINE", "SPIRAL LINE", &data.spiral_line, NULL},
        {550, 0, 100, 20, "RAINBOW ON", "RAINBOW OFF", &data.object_rainbow, NULL},
        {660, 0, 100, 20, "RIG ON", "RIG OFF", &data.shape_animation, NULL},
        {770, 0, 100, 20, "Xiaolin-Wu", "Brensham", &data.line_algorithm, NULL},
        {880, 0, 100, 20, "X Enabled", "X Disalbed", &data.center_x_enabled, NULL},
        {880, 25, 100, 20, "Y Enabled", "Y Disalbed", &data.center_y_enabled, NULL},
        {880, 50, 100, 20, "Z Enabled", "Z Disalbed", &data.center_z_enabled, NULL},
        {1320, 0, 100, 20, "SHAPE X", "SHAPE X", &data.cube_rotate_x, NULL},
        {1430, 0, 100, 20, "SHAPE Y", "SHAPE Y", &data.cube_rotate_y, NULL},
        {1540, 0, 100, 20, "SHAPE Z", "SHAPE Z", &data.cube_rotate_z, NULL},
        // Add more buttons here as needed
    };
    data.buttons = buttons;
    data.button_count = sizeof(buttons) / sizeof(Button);
    mlx_hook(data.window, 2, 1L << 0, handle, &data);
    mlx_hook(data.window, 4, 1L << 2, mouse_press, &data);
    mlx_hook(data.window, 5, 1L << 3, mouse_release, &data);
    mlx_hook(data.window, 6, 1L << 6, mouse_move, &data);
    mlx_loop_hook(data.connect, animation_loop, &data);

    // Start the MLX loop
    mlx_loop(data.connect);
    return 0;
}


