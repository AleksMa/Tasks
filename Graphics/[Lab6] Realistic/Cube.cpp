#include "Cube.h"


Cube::Cube(GLfloat aa, GLfloat bb, GLfloat cc)
	: a(aa), b(bb), c(cc) {}

void Cube::draw()
{
	GLfloat m_amb[] = {
		0.35,
		0.35,
		0.35
	};
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);

	GLfloat m_diff[] = {
		0.4,
		0.4,
		0.4
	};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);

	GLfloat m_spec[] = {
		0.774597,
		0.774597,
		0.774597
	};
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT, GL_SHININESS, .6f * 128.f);

	glBindTexture(GL_TEXTURE_2D, texture);
	Mesh::draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Cube::rebuild()
{
	this->vertices.clear();
	this->normals.clear();
	this->faces.clear();
	this->texture_coord.clear();
	
	//texture:
	this->texture_coord.push_back(Point(0.f, 0.f));
	this->texture_coord.push_back(Point(0.f, 1.f));
	this->texture_coord.push_back(Point(1.f, 1.f));
	this->texture_coord.push_back(Point(1.f, 0.f));


	
	this->vertices.push_back(Point(a / 2, -c / 2, b / 2));
	this->vertices.push_back(Point(-a / 2, -c / 2, b / 2));
	this->vertices.push_back(Point(-a / 2, -c / 2, -b / 2));
	this->vertices.push_back(Point(a / 2, -c / 2, -b / 2));

	this->vertices.push_back(Point(a / 2, c / 2, b / 2));
	this->vertices.push_back(Point(-a / 2, c / 2, b / 2));
	this->vertices.push_back(Point(-a / 2, c / 2, -b / 2));
	this->vertices.push_back(Point(a / 2, c / 2, -b / 2));

	this->faces.push_back(Polygon(std::vector<Vertex>( // bottom
		{ Vertex(0, 3),  Vertex(1, 0), Vertex(2, 1), Vertex(3, 2) }), this->normals.size())); 
	this->normals.push_back(Vector(0, 1, 0));

	//this->faces.push_back(Polygon(std::vector<Vertex>( // front
	//	{ Vertex(0),  Vertex(4), Vertex(5), Vertex(1) }), this->normals.size()));
	//this->normals.push_back(Vector(0, 0, -1));

//	this->faces.push_back(Polygon(std::vector<Vertex>( //left
//		{ Vertex(1),  Vertex(5), Vertex(6), Vertex(2) }), this->normals.size())); // ����� �������, ������� ��� �� ���������
//	this->normals.push_back(Vector(-1, 0, 0));

	this->faces.push_back(Polygon(std::vector<Vertex>( //back
		{ Vertex(2, 0),  Vertex(6, 1), Vertex(7, 2), Vertex(3, 3) }), this->normals.size())); // ����� �������, ������� ��� �� ���������
	this->normals.push_back(Vector(0, 0, 1));

	this->faces.push_back(Polygon(std::vector<Vertex>( //right
		{ Vertex(0, 0),  Vertex(3, 3), Vertex(7, 2), Vertex(4, 1) }), this->normals.size())); // ����� �������, ������� ��� �� ���������
	this->normals.push_back(Vector(-1, 0, 0));

	//this->faces.push_back(Polygon(std::vector<Vertex>( //top
	//	{ Vertex(4),  Vertex(7), Vertex(6), Vertex(5) }), this->normals.size())); // ����� �������, ������� ��� �� ���������
	//this->normals.push_back(Vector(0, 1, 0));

	std::vector<Vector> vertex_normals;
	for (Polygon &face : this->faces) {
		for (Vertex &vert : face.indices) {
			if (this->vertices[vert.pointIndex].normalIndex == -1) {
				this->vertices[vert.pointIndex].normalIndex = vertex_normals.size();
				vertex_normals.push_back(this->normals[face.normIndex]);
			} else {
				vertex_normals[this->vertices[vert.pointIndex].normalIndex].x += this->normals[face.normIndex].x;
				vertex_normals[this->vertices[vert.pointIndex].normalIndex].y += this->normals[face.normIndex].y;
				vertex_normals[this->vertices[vert.pointIndex].normalIndex].z += this->normals[face.normIndex].z;
			}
		}
	}

	this->normals.clear();
	this->normals = vertex_normals;
}

void Cube::set_texture(GLuint t)
{
	texture = t;
}

std::pair<GLfloat, GLfloat> Cube::get_x_interval() const
{
	return std::pair<GLfloat, GLfloat>(-a / 2, a / 2);
}

std::pair<GLfloat, GLfloat> Cube::get_y_interval() const
{
	return std::pair<GLfloat, GLfloat>(-c / 2, c / 2);
}

std::pair<GLfloat, GLfloat> Cube::get_z_interval() const
{
	return std::pair<GLfloat, GLfloat>(-b / 2, b / 2);
}

Cube::~Cube()
{
}
