#pragma once
#include <vector>
#include "Primary.h"
#include <GLFW/glfw3.h>

class Polygon {
public:
	GLint normIndex;
	std::vector<Vertex> indices;
	Polygon(std::vector<Vertex> indx, GLint n) : indices(indx), normIndex(n) {};
};