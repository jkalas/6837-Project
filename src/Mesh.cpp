#include "Mesh.h"

using namespace std;

void Mesh::load( const char* filename )
{
	// load the OBJ file here
    string line;
	ifstream meshFile(filename);

	if (meshFile.is_open()) {
	    while (getline(meshFile, line)) {
	        stringstream ss(line);

	        string s;

	        ss >> s;

	        if (s == "v") {
	        	Vector3f v;
	            ss >> v[0] >> v[1] >> v[2];

	            vertices.push_back(v);
	        } else if (s == "f") {
	            Tuple3u face;

	            ss >> face[0] >> face[1] >> face[2];	            
	            faces.push_back(face);
	        }
	    }
	}
}

void Mesh::draw()
{
	// Since these meshes don't have normals
	// be sure to generate a normal per triangle.
	// Notice that since we have per-triangle normals
	// rather than the analytical normals from
	// assignment 1, the appearance is "faceted".
    glBegin(GL_TRIANGLES);
	for (unsigned int j = 0; j < faces.size(); j++) { 
        Tuple3u face = faces[j];

        unsigned int a = face[0] + 1;
        unsigned int b = face[1] + 1;
        unsigned int c = face[2] + 1;

        Vector3f V = vertices[b - 1] - vertices[a - 1];
        Vector3f W = vertices[c - 1] - vertices[a - 1];

        Vector3f N = Vector3f::cross(V, W);

        glNormal3d(N[0], N[1], N[2]);
        glVertex3d(vertices[a - 1][0], vertices[a - 1][1], vertices[a - 1][2]);
        glVertex3d(vertices[b - 1][0], vertices[b - 1][1], vertices[b - 1][2]);
        glVertex3d(vertices[c - 1][0], vertices[c - 1][1], vertices[c - 1][2]);
    }
    glEnd();
}
