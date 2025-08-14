# include "rainbow.h"

Vertex cube[8];

void initialize_cube(Vertex *cube, t_data *data)
{
	float front_z;
	float back_z;

	front_z = data->x_value;
	back_z = -data->z_value;
	cube[0] = (Vertex){-1,  1,  front_z};
	cube[1] = (Vertex){ 1,  1,  front_z};
	cube[2] = (Vertex){ 1, -1,  front_z};
	cube[3] = (Vertex){-1, -1,  front_z};
	cube[4] = (Vertex){-1,  1,  back_z};
	cube[5] = (Vertex){ 1,  1,  back_z};
	cube[6] = (Vertex){ 1, -1,  back_z};
	cube[7] = (Vertex){-1, -1,  back_z};
}


void draw_cube(t_data *data, Vertex *cube, float zoom)
{
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };
    Vertex transformed[8];
    Point2D projected[8];

    for (int i = 0; i < 8; i++) {
        transformed[i] = cube[i];
        transform_vertex(data, &transformed[i]);
        projected[i] = project(data, transformed[i], zoom);
    }

    for (int i = 0; i < 12; i++) {
        draw_line(data, projected[edges[i][0]].x, projected[edges[i][0]].y,
                  projected[edges[i][1]].x, projected[edges[i][1]].y);
    }
}



