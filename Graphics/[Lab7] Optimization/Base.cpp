#include "Base.h"

Vector GetNormal(const std::vector<Point> &polygon) {
	GLfloat mx = 0;
	GLfloat my = 0;
	GLfloat mz = 0;

	for (GLuint i = 0; i < polygon.size(); i++) {
		GLuint next_i = (i + 1) % polygon.size();
		mx += (polygon[i].y - polygon[next_i].y) * (polygon[i].z + polygon[next_i].z);
		my += (polygon[i].z - polygon[next_i].z) * (polygon[i].x + polygon[next_i].x);
		mz += (polygon[i].x - polygon[next_i].x) * (polygon[i].y + polygon[next_i].y);
	}

	return Vector(mx, my, mz);
}