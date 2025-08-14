# include "rainbow.h"
void initialize_torus(Vertex **torus, int *vertex_count, float R, float r, int major_segments, int minor_segments) {
	*vertex_count = (major_segments + 1) * (minor_segments + 1);
	*torus = malloc(*vertex_count * sizeof(Vertex));

	int index = 0;
	int i = 0;
	while (i <= major_segments) {
		float theta = 2 * M_PI * i / major_segments;
		int j = 0;
		while (j <= minor_segments) {
			float phi = 2 * M_PI * j / minor_segments;
			(*torus)[index++] = (Vertex){
				(R + r * cos(phi)) * cos(theta),
				(R + r * cos(phi)) * sin(theta),
				r * sin(phi)
			};
			j++;
		}
		i++;
	}
}

void draw_torus(t_data *data, Vertex *torus, int major_segments, int minor_segments, float zoom)
{
	Vertex transformed[data->torus_vertex_count];
	Point2D projected[data->torus_vertex_count];

	int i = 0;
	while (i < data->torus_vertex_count) {
		transformed[i] = torus[i];
		transform_vertex(data, &transformed[i]);
		projected[i] = project(data, transformed[i], zoom);
		i++;
	}
	i = 0;
	// Draw lines to connect vertices
	while (i < major_segments) {
		int j = 0;
		while (j < minor_segments) {
			int current = i * (minor_segments + 1) + j;
			int next_minor = current + 1;
			int next_major = current + (minor_segments + 1);

			// Connect within the same minor circle
			draw_line(data, projected[current].x, projected[current].y,
					  projected[next_minor].x, projected[next_minor].y);

			// Connect to the next major circle
			if (i < major_segments - 1) {
				draw_line(data, projected[current].x, projected[current].y,
						  projected[next_major].x, projected[next_major].y);
			}
			j++;
		}
		i++;
	}
}
