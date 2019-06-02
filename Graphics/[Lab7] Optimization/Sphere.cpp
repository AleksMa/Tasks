#include "Sphere.h"
#include "bits/stdc++.h"

const float PI = 3.14159265;

Sphere::Sphere(GLfloat r,
               GLfloat a,
               GLfloat b,
               GLfloat c,
               GLint points,
               GLint layers,
               const Vector &v)
    : position(v) {

  set_r(r);
  set_a(a);
  set_b(b);
  set_c(c);
  set_points_count(points);
  set_layers_count(layers);
}

void Sphere::draw() const {
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(position.x, position.y, position.z);

#ifdef LIGHT

  GLfloat m_amb[] = {
      0.8, 0.9, 0.8
  };
  glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);

  GLfloat m_diff[] = {
      0.8, 0.9, 0.8
  };
  glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);

  GLfloat m_spec[] = {
      0.8, 0.9, 0.8
  };
  glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);

  glMaterialf(GL_FRONT, GL_SHININESS, 100);

#endif

  glBindTexture(GL_TEXTURE_2D, texture);
  Mesh::draw();
  glBindTexture(GL_TEXTURE_2D, 0);

  glPopMatrix();
}

void setMax(GLfloat &maX, GLfloat &maY, GLfloat &maZ, GLfloat x, GLfloat y, GLfloat z) {
  if (x > maX)
    maX = x;
  if (y > maY)
    maY = y;
  if (z > maZ)
    maZ = z;
}

void setMin(GLfloat &maX, GLfloat &maY, GLfloat &maZ, GLfloat x, GLfloat y, GLfloat z) {
  if (x < maX)
    maX = x;
  if (y < maY)
    maY = y;
  if (z < maZ)
    maZ = z;
}

void Sphere::rebuild() {
  this->vertices.clear();
  this->normals.clear();
  this->faces.clear();
  this->texture_coord.clear();

  this->texture_coord.push_back(Point(0.f, 0.f));
  this->texture_coord.push_back(Point(0.f, 1.f));
  this->texture_coord.push_back(Point(1.f, 1.f));
  this->texture_coord.push_back(Point(1.f, 0.f));

  GLfloat max_x = -1000;
  GLfloat max_y = -1000;
  GLfloat max_z = -1000;

  GLfloat min_x = 1000;
  GLfloat min_y = 1000;
  GLfloat min_z = 1000;

  this->vertices.push_back(Point(0.f, b * r, 0.f));

  setMax(max_x, max_y, max_z, 0.f, b * r, 0.f);
  setMin(min_x, min_y, min_z, 0.f, b * r, 0.f);

  for (int i = layers_count - 1; i >= 0; i--) {
    GLfloat y = r * i / layers_count;
    GLfloat radius = sqrt(static_cast<GLfloat>(r * r) - (y * y));
    for (int j = 0; j < points_count; j++) {
      this->vertices.push_back(Point(a * radius * cos(j * PI * 2 / points_count),
                                     b * y,
                                     c * radius * sin(j * PI * 2 / points_count)));
      //vertices.push_back(Point(radius * cos(j * pi * 2 / M), - radius / M * i, radius * sin(j * pi * 2 / M)));

      setMax(max_x,
             max_y,
             max_z,
             a * radius * cos(j * PI * 2 / points_count),
             b * y,
             c * radius * sin(j * PI * 2 / points_count));
      setMin(min_x,
             min_y,
             min_z,
             a * radius * cos(j * PI * 2 / points_count),
             b * y,
             c * radius * sin(j * PI * 2 / points_count));

    }
  }

  for (int i = 0; i < layers_count; i++) {
    GLfloat y = r * i / layers_count;
    GLfloat radius = sqrt(static_cast<GLfloat>(r * r) - (y * y));
    for (int j = 0; j < points_count; j++) {
      this->vertices.push_back(Point(a * radius * cos(j * PI * 2 / points_count),
                                     b * -y,
                                     c * radius * sin(j * PI * 2 / points_count)));

      setMax(max_x,
             max_y,
             max_z,
             a * radius * cos(j * PI * 2 / points_count),
             b * -y,
             c * radius * sin(j * PI * 2 / points_count));
      setMin(min_x,
             min_y,
             min_z,
             a * radius * cos(j * PI * 2 / points_count),
             b * -y,
             c * radius * sin(j * PI * 2 / points_count));

    }
  }

  this->vertices.push_back(Point(0.f, -b * r, 0.f));

  setMax(max_x, max_y, max_z, 0.f, b * r, 0.f);
  setMin(min_x, min_y, min_z, 0.f, -b * r, 0.f);

  for (int i = 0; i < points_count; i++) {
    GLint A = 0;
    GLint B = i + 1;
    GLint C = (i == points_count - 1 ? 1 : i + 2);

    Point p = vertices[0];
    Point p1 = vertices[i + 1], p2 = vertices[(i == points_count - 1 ? 1 : i + 2)];
    this->faces.push_back(Polygon(std::vector<Vertex>(
        {Vertex(A, 0), Vertex(B, 3),
         Vertex(C, 2)}), this->normals.size()));

    this->normals.push_back(GetNormal({
                                          this->vertices[A],
                                          this->vertices[B],
                                          this->vertices[B],
                                      }));
  }

  for (int i = 0; i < 2 * layers_count - 1; i++) {
    for (int j = 0; j < points_count; j++) {

      //      Из Лаб3 - чтобы не запутаться :(

      Point p1 = vertices[points_count * i + j + 1],
          p2 = vertices[(j == points_count - 1 ? points_count * i + 1 : points_count * i + j + 2)];
      Point p3 = vertices[points_count * (i + 1) + j + 1],
          p4 = vertices[(j == points_count - 1 ? points_count * (i + 1) + 1 : points_count * (i + 1) + j + 2)];

      this->faces.push_back(Polygon(std::vector<Vertex>(
          {Vertex(points_count * i + j + 1, 0), Vertex(points_count * (i + 1) + j + 1, 2),
           Vertex((j == points_count - 1 ? points_count * i + 1 : points_count * i + j + 2), 3)}),
                                    this->normals.size()));

      this->normals.push_back(GetNormal({
                                            this->vertices[points_count * i + j + 1],
                                            this->vertices[points_count * (i + 1) + j + 1],
                                            this->vertices[(j == points_count - 1 ? points_count * i + 1 :
                                                            points_count * i + j + 2)],
                                        }));

//      glVertex3f(p1.x + x, p1.y + y, p1.z + z);
//      glVertex3f(p3.x + x, p3.y + y, p3.z + z);
//      glVertex3f(p2.x + x, p2.y + y, p2.z + z);


      this->faces.push_back(Polygon(std::vector<Vertex>(
          {Vertex(points_count * (i + 1) + j + 1, 2),
           Vertex((j == points_count - 1 ? points_count * (i + 1) + 1 : points_count * (i + 1) + j + 2), 1),
           Vertex((j == points_count - 1 ? points_count * i + 1 : points_count * i + j + 2), 3)}),
                                    this->normals.size()));

      this->normals.push_back(GetNormal({
                                            this->vertices[points_count * (i + 1) + j + 1],
                                            this->vertices[points_count * i + j + 1],
                                            this->vertices[(j == points_count - 1 ? points_count * (i + 1) + 1 :
                                                            points_count * (i + 1) + j + 2)],
                                        }));


//      glVertex3f(p3.x + x, p3.y + y, p3.z + z);
//      glVertex3f(p4.x + x, p4.y + y, p4.z + z);
//      glVertex3f(p2.x + x, p2.y + y, p2.z + z);

    }
  }

  for (int i = 0; i < points_count; i++) {
    Point p = vertices[vertices.size() - 1];
    Point p1 = vertices[points_count * (2 * layers_count - 1) + i + 1],
        p2 = vertices[(i == points_count - 1 ? points_count * (2 * layers_count - 1) + 1 :
                       points_count * (2 * layers_count - 1) + i + 2)];

    this->faces.push_back(Polygon(std::vector<Vertex>(
        {Vertex(vertices.size() - 1, 0), Vertex(points_count * (2 * layers_count - 1) + i + 1, 1),
         Vertex((i == points_count - 1 ? points_count * (2 * layers_count - 1) + 1 :
                 points_count * (2 * layers_count - 1) + i + 2), 3)}),
                                  this->normals.size()));

    this->normals.push_back(GetNormal({
                                          this->vertices[vertices.size() - 1],
                                          this->vertices[points_count * (2 * layers_count - 1) + i + 1],
                                          this->vertices[(i == points_count - 1 ? points_count * (2 * layers_count - 1)
                                              + 1 : points_count * (2 * layers_count - 1) + i + 2)],
                                      }));

  }

  std::vector<Vector> vertex_normals;
  for (Polygon &face : this->faces) {
    for (Vertex &v : face.indices) {
      if (this->vertices[v.pointIndex].normalIndex == -1) {
        this->vertices[v.pointIndex].normalIndex = vertex_normals.size();
        vertex_normals.push_back(this->normals[face.normIndex]);
      } else {
        vertex_normals[this->vertices[v.pointIndex].normalIndex].x += this->normals[face.normIndex].x;
        vertex_normals[this->vertices[v.pointIndex].normalIndex].y += this->normals[face.normIndex].y;
        vertex_normals[this->vertices[v.pointIndex].normalIndex].z += this->normals[face.normIndex].z;
      }
    }
  }

  this->normals.clear();
  this->normals = vertex_normals;

  this->x_interval = {min_x, max_x};
  this->y_interval = {min_y, max_y};
  this->z_interval = {min_z, max_z};

}

std::pair<GLfloat, GLfloat> Sphere::get_x_interval() const {
  return x_interval;
}

std::pair<GLfloat, GLfloat> Sphere::get_y_interval() const {
  return y_interval;
}

std::pair<GLfloat, GLfloat> Sphere::get_z_interval() const {
  return z_interval;
}

void Sphere::set_texture(GLuint t) {
  texture = t;
}

Vector Sphere::get_position() const {
  return position;
}

void Sphere::set_position(const Vector &v) {
  position = v;
}

GLint Sphere::get_points_count() const {
  return points_count;
}

void Sphere::set_points_count(GLint new_count) {
  points_count = new_count;
}

GLint Sphere::get_layers_count() const {
  return layers_count;
}

void Sphere::set_layers_count(GLint new_count) {
  layers_count = new_count;
}

GLfloat Sphere::get_r() const {
  return r;
}

void Sphere::set_r(GLfloat new_r) {
  r = new_r;
}

GLfloat Sphere::get_a() const {
  return a;
}

void Sphere::set_a(GLfloat new_a) {
  a = new_a;
}

GLfloat Sphere::get_b() const {
  return b;
}

void Sphere::set_b(GLfloat new_b) {
  b = new_b;
}

GLfloat Sphere::get_c() const {
  return c;
}

void Sphere::set_c(GLfloat new_c) {
  c = new_c;
}

Sphere::~Sphere() {
}
