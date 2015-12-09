#ifndef MESH_H
#define MESH_H

#include <vector>
#include <vecmath.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "extra.h"
#include "tuple.h"

typedef tuple< unsigned, 3 > Tuple3u;

struct Mesh
{
	// list of vertices from the OBJ file
	// in the "bind pose"
	std::vector< Vector3f > vertices;

	// each face has 3 indices
	// referencing 3 vertices
	std::vector< Tuple3u > faces;

	// 2.1.1. load() should populate bindVertices, currentVertices, and faces
	void load(const char *filename);

	// 2.1.2. draw the current mesh.
	void draw();
};

#endif
