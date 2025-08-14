/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshannak <wshannak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:24:04 by wshannak          #+#    #+#             */
/*   Updated: 2024/12/14 20:08:23 by wshannak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef RAINBOW_H
# define RAINBOW_H
// Libraries
# include <stdbool.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
// # include <fcntl.h>
# include <string.h>

//    Defines  //
// exit function
# define ESC_KEY 	65307 // Exit

// animation
# define UP_KEY 	65362 // Arrow up
# define DOWN_KEY 	65364 // Arrow down

// grid
# define GRID_TOGGLE    65430 // '4' key to toggle grid

// effects
# define EFFECT_1       49 // '1' key to enable effect 1
# define EFFECT_3       50 // '2' key to enable effect 3
# define HUE_INCREASE	51 // '3' key to increase hue
# define HUE_DECREASE	52 // '4' key to decrease hue
# define SATURATION_INCREASE	53 // '5' key to increase saturation
# define SATURATION_DECREASE	54 // '6' key to decrease saturation
# define VALUE_INCREASE	55 // '7' key to increase value
# define VALUE_DECREASE	56 // '8' key to decrease value

// object
# define OBJECT_CLEAR 65421 // 'ENTER' key to clear object mask

// zoom
# define ZOOM_IN	65451 // "+" key to zoom in
# define ZOOM_OUT	65453 // "-" key to zoom out
# define ZOOM_RESET	65450 // "*" key to reset zoom

// cube
# define X_INCREASE	65474 // 'F5' key to rotate cube on x axis
# define X_DECREASE	65475 // 'F6' key to rotate cube on x axis
# define Z_INCREASE	65476 // 'F7' key to rotate cube on z axis
# define Z_DECREASE	65477 // 'F8' key to rotate cube on z axis
# define MOVE_LEFT	65361 // 'Arrow left' key to move cube left
# define MOVE_RIGHT	65363 // 'Arrow right' key to move cube right
# define SPHERE_CIRCLE		65436 // '1' key to toggle sphere
# define SPHERE_ROTATE		65433 // '2' key to toggle sphere rotation
# define SCALE_UP	65429 // 7 key to scale up
# define SCALE_DOWN	65434 // 9 key to scale down
# define PROJECTION_MODE	65437 // 0 key to change projection mode
# define ANGLE_INCREASE 	65430 // '6' key to increase angle
# define ANGLE_DECREASE		65432 // '8' key to decrease angle

typedef struct s_data t_data;


// Button struct
struct s_data;
typedef struct {
	int x;       // X position
	int y;       // Y position
	int width;   // Button width
	int height;  // Button height
	const char *label_on;  // Label when active
	const char *label_off; // Label when inactive
	int *state;  // Pointer to the state variable (e.g., shape_toggle)
	void (*callback)(struct s_data *data);
} Button;

typedef enum {
    PROJECTION_PERSPECTIVE,
    PROJECTION_ORTHOGRAPHIC,
    PROJECTION_ISOMETRIC,
    PROJECTION_OBLIQUE,
    PROJECTION_AXONOMETRIC
} ProjectionMode;

// Cube control
typedef struct {
    float x, y, z;
} Vertex;

typedef struct {
    int x, y;
} Point2D;

extern Vertex cube[8];



typedef struct s_data
{
	// connection and window
	void	*connect; // connection
	void	*window; // window ref

	// image data
	void	*image; // image buffer
	char	*buffer; // pointer pixel data
	int	bpp; // byte per pixel
	int	linelen; //number of bytes in a row of pixels
	int	endian; // Endianess of the pixel

	// animation controls
	int	animating; // Animation state (1 = running, 0 = stopped)
	int	speed; // Frames to wait between updates (controls speed)
	int     frame_count; // Current frame count for timing

	// background control
	int	background_enabled; // 1 = enabled, 0 = disabled

	// grid control
	int	grid_enabled; // 1 = enabled, 0 = disabled

	// spiral control
	int	spiral_enabled; // 1 = enabled, 0 = disabled
	int	spiral_line; // 1 = enabled, 0 = disabled

	// effect controls
	float	effect_1; // 1 = enabled, 0 = disabled
	float	effect_3; // 1 = enabled, 0 = disabled
	float	hue; // hue value
	float	value; // value
	float	current_hue; // hue offset
	float	saturation; // saturation value

	// Screen size
	int	snx; // screen X
	int	sny; // screen Y

	// Object controls
	unsigned char	*object_mask; // object mask
	int	object_rainbow; // object color
	int	line_algorithm; // 0 = brensham, 1 = xiaolin-wu

	// Zoom controls
	float	zoom;

	// Middle mouse button
	int	right_mouse_button; // mouse right button state

	// shape control
	int	cube_toggle; // 1 = enabled, 0 = disabled
	int	shape_animation;
	float	angle_x;
	float	angle_y;
	float	angle_z;
	int	cube_rotate_x;
	int	cube_rotate_y;
	int	cube_rotate_z;
	float	x_value;
	float	z_value;
	float translate_x; // Global translation in X
	float translate_y; // Global translation in Y
	float translate_z; // Global translation in Z
	int center_x_enabled;
	int center_y_enabled;
	int center_z_enabled;
	float center_x; // Center of rotation in X
	float center_y; // Center of rotation in Y
	float center_z; // Center of rotation in Z
	int	sphere_toggle;
	Vertex *sphere;            // Pointer to sphere vertices
	Vertex *torus;             // Pointer to torus vertices
	int	torus_toggle;          // Torus toggle
	int	torus_vertex_count;    // Total number of vertices in the torus
   	int	sphere_vertex_count;   // Total number of vertices in the sphere
	int sphere_rig; // Sphere rigging toggle
	int sphere_circle;
	int sphere_rotate;
	int vertex_count;
	float	scale_cube;
	float	scale_sphere;
	float	scale_torus;
	Button *buttons;
	int button_count;
	ProjectionMode projection_mode;
	float	ang;

}	t_data;

// Function declarations
void	clear_object_mask(t_data *data);
void	apply_rainbow_to_objects(t_data *data);
int	animation_loop(t_data *data);

// reset.c
void initialize_data(t_data *data);
void reset_all(struct s_data *data);
// object.c
void	draw_solid_background(t_data *data, int color);
void	draw_solid_grid(t_data *data, int color);
void	 draw_spiral(t_data *data, int center_x, int center_y, float start_radius, float angle_increment, float radius_increment, int num_points);
void	draw_line(t_data *data, int x1, int y1, int x2, int y2);

// mouse.c
int 	mouse_press(int button, int x, int y, t_data *data);
int 	mouse_release(int button, int x, int y, t_data *data);
int 	mouse_move(int x, int y, t_data *data);
int	mouse_hook(int button, int x, int y, t_data *data);

// functions.c
void	hsv_to_rgb(float h, float s, float v, int *r, int *g, int *b);
void	pp(t_data *data, int x, int y, int color);
void	apply_zoom(t_data *data, int *x, int *y);
void	center_object(Vertex *vertices, int vertex_count, t_data *data);
// line.c
void	draw_line_bresenham(t_data *data, int x1, int y1, int x2, int y2);
void	set_pixel_with_rainbow(t_data *data, int x, int y, float hue);
void	draw_line_xiaolin(t_data *data, int x0, int y0, int x1, int y1);
void 	blend_pixel_with_rainbow(t_data *data, int x, int y, float intensity, float hue);
int	draw_dot (int x, int y, t_data *data);

 // handle.c
void	toggle(int *value, const char *label);
int	handle(int keycode, t_data *data);

 // cube.c
void	initialize_cube(Vertex *cube, t_data *data);
void	rotate_cube(Vertex *cube, int num_vertices, float angle_x, float angle_y, float angle_z);
// void	draw_cube(t_data *data, Vertex *cube, float angle_x, float angle_y, float angle_z, float zoom);
void	isometric_projection(float x, float y, float z, int *x2d, int *y2d, float angle);
void	draw_cube(t_data *data, Vertex *cube, float zoom);

// UI.c
void 	draw_buttons(t_data *data, Button *buttons, int button_count);
void	button_draw(t_data *data, int x_start, int y_start, int width, int height, int color);
void button_control(t_data *data, int x_start, int y_start, int width, int height, int color_on, int color_off, const char *label_on, const char *label_off, int *state);
void	button_draw_with_label(t_data *data, int x_start, int y_start, int width, int height, int color, const char *label_on, const char *label_off);

//sphere.c
void draw_sphere(t_data *data, Vertex *sphere, int vertex_count, int latitude_count, int longitude_count, float zoom);
void initialize_sphere(t_data *data, Vertex **sphere, int *vertex_count, float radius, int latitude_count, int longitude_count);

// donut.c
void initialize_torus(Vertex **torus, int *vertex_count, float R, float r, int major_segments, int minor_segments);
void draw_torus(t_data *data, Vertex *torus, int major_segments, int minor_segments, float zoom);

// project.c
void transform_vertex(t_data *data, Vertex *v);
Point2D	project(t_data *data, Vertex p, float zoom);
void rotate_vertex(t_data *data, Vertex *v, float angle_x, float angle_y, float angle_z);
void	draw_cord(t_data *data);

// main.c **keep me last**
int	main();


#endif

