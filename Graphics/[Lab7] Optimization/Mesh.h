#pragma once

#include <vector>
#include "Base.h"
#include "Polygon.h"

class Mesh
{
public:
	Mesh();

	void set_texture_mode(GLboolean m);
	void draw() const;
	~Mesh();
protected:
	GLboolean use_textures;

	std::vector<Point> texture_coord;
	std::vector<Point> vertices;
	std::vector<Vector> normals;
	std::vector<Polygon> faces;
};

