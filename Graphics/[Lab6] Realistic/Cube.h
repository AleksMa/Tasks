#pragma once
#include "Mesh.h"
class Cube :
	public Mesh
{
public:
	Cube(GLfloat aa, GLfloat bb, GLfloat cc);

	void draw();
	void rebuild();

	void set_texture(GLuint t);
	
	std::pair<GLfloat, GLfloat> get_x_interval() const;
	std::pair<GLfloat, GLfloat> get_y_interval() const;
	std::pair<GLfloat, GLfloat> get_z_interval() const;

	~Cube();
private:
	GLfloat a;
	GLfloat b;
	GLfloat c;

	GLuint texture;
};

