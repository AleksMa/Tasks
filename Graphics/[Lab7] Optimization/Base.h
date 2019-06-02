#pragma once
#include <GLFW/glfw3.h>
#include <vector>

struct Point
{
	GLuint normalIndex;
	GLfloat x, y, z;
	Point(GLfloat x, GLfloat y) : x(x), y(y), z(0.f), normalIndex(-1) {};
	Point(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z), normalIndex(-1) {};
};

struct Vector
{
	GLfloat x, y, z;
	Vector(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {};
};

struct Vertex {
	GLint textureCoordIndex;
	GLint pointIndex;
	Vertex(GLint p) : pointIndex(p), textureCoordIndex(-1) {};
	Vertex(GLint p, GLint c) : pointIndex(p), textureCoordIndex(c) {};
};

Vector GetNormal(const std::vector<Point> &);