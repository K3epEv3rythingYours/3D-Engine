# include <rainbow.h>

void draw_sphere(t_data *data, Vertex *sphere, int vertex_count, int latitude_count, int longitude_count, float zoom)
{
	Vertex transformed[vertex_count]; // Array to store transformed vertices
	Point2D projected[vertex_count]; // Array to store projected vertices

	int i = 0;
	while (i < vertex_count) {
		transformed[i] = sphere[i]; // Copy the original vertex
		rotate_vertex(data, &transformed[i], data->angle_x, data->angle_y, data->angle_z); // Rotate the vertex
		transform_vertex(data, &transformed[i]); // Apply global transformations
		projected[i] = project(data, transformed[i], zoom); // Project the vertex onto 2D space
		i++;
	}

	int lat = 0;
	while (lat < latitude_count) {
		int lon = 0;
		while (lon < longitude_count) {
			int current = lat * (longitude_count + 1) + lon; // Calculate the index of the current vertex
			int next_lon = current + 1; // Calculate the index of the next vertex in the same longitude
			int next_lat = current + (longitude_count + 1); // Calculate the index of the next vertex in the next latitude

			// Connect points within the same latitude
			if (lon < longitude_count) {
				draw_line(data, projected[current].x, projected[current].y,
						  projected[next_lon].x, projected[next_lon].y); // Draw a line between the current vertex and the next vertex in the same longitude
			}

			// Connect points to the next latitude
			if (lat < latitude_count - 1) {
				draw_line(data, projected[current].x, projected[current].y,
						  projected[next_lat].x, projected[next_lat].y); // Draw a line between the current vertex and the next vertex in the next latitude
			}

			lon++;
		}
		lat++;
	}
}


void initialize_sphere(t_data *data, Vertex **sphere, int *vertex_count, float radius, int latitude_count, int longitude_count)
{
	*vertex_count = (latitude_count + 1) * (longitude_count + 1); // Calculate the total number of vertices
	*sphere = malloc(*vertex_count * sizeof(Vertex)); // Allocate memory for the sphere vertices
	if (!*sphere) {
		fprintf(stderr, "Error: Unable to allocate memory for sphere vertices.\n");
		exit(1);
	}

	int index = 0;
	int lat = 0;
	while (lat <= latitude_count) {
		float theta = M_PI * lat / latitude_count; // Calculate the latitude angle
		int lon = 0;
		while (lon <= longitude_count) {
			float phi = data->sphere_rig * M_PI * lon / longitude_count; // Calculate the longitude angle
			(*sphere)[index++] = (Vertex){
				radius * sin(theta) * cos(phi), // Calculate the x-coordinate of the vertex
				radius * sin(theta) * sin(phi), // Calculate the y-coordinate of the vertex
				radius * cos(theta) // Calculate the z-coordinate of the vertex
			};
			lon++;
		}
		lat++;
	}
}



