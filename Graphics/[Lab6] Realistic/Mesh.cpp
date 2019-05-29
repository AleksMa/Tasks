#include "Mesh.h"
#include <iostream>

Mesh::Mesh() : use_textures(true) {}

void Mesh::set_texture_mode(GLboolean m) {
	use_textures = m;
}

void Mesh::draw() const {
	for (const Polygon &face : faces) {
		glBegin(GL_POLYGON);
		for (const Vertex &vert : face.indices) {
			//std::cout << "x: " << vert.normal.x << "y: " << vert.normal.y << "z: " << vert.normal.z;
			if (use_textures) {
				if (vert.textureCoordIndex != -1) {
					glTexCoord2f(texture_coord[vert.textureCoordIndex].x, texture_coord[vert.textureCoordIndex].y);
				}
			}

			glNormal3f(normals[vertices[vert.pointIndex].normalIndex].x,
				normals[vertices[vert.pointIndex].normalIndex].y,
				normals[vertices[vert.pointIndex].normalIndex].z);
			glVertex3f(vertices[vert.pointIndex].x, vertices[vert.pointIndex].y, vertices[vert.pointIndex].z);
		}
		glEnd();
	}
}

Mesh::~Mesh(){}
