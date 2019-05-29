#pragma once
#include <GLFW/glfw3.h>
#include <vector>

struct Point
{
	GLuint normalIndex;
	GLfloat x, y, z;
	Point(GLfloat xx, GLfloat yy) : x(xx), y(yy), z(0.f), normalIndex(-1) {};
	Point(GLfloat xx, GLfloat yy, GLfloat zz) : x(xx), y(yy), z(zz), normalIndex(-1) {};
};

struct Vector
{
	GLfloat x, y, z;
	Vector(GLfloat xx, GLfloat yy, GLfloat zz) : x(xx), y(yy), z(zz) {};
};

struct Vertex {
	GLint textureCoordIndex;
	GLint pointIndex;
	Vertex(GLint p) : pointIndex(p), textureCoordIndex(-1) {};
	Vertex(GLint p, GLint c) : pointIndex(p), textureCoordIndex(c) {};
};

Vector GetNormal(const std::vector<Point> &);