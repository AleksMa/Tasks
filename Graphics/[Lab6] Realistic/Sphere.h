#pragma once
#include "Mesh.h"
#include "Cube.h"

class Sphere :
    public Mesh {
 public:
  Sphere(GLfloat r,
         GLfloat a,
         GLfloat b,
         GLfloat c,
         GLint points,
         GLint layers,
         const Vector &v);
  void draw() const;
  void rebuild();

  std::pair<GLfloat, GLfloat> get_x_interval() const;
  std::pair<GLfloat, GLfloat> get_y_interval() const;
  std::pair<GLfloat, GLfloat> get_z_interval() const;

  void set_texture(GLuint t);

  Vector get_position() const;
  void set_position(const Vector &v);

  GLint get_layers_count() const;
  void set_layers_count(GLint new_count);

  GLint get_points_count() const;
  void set_points_count(GLint new_count);

  GLfloat get_r() const;
  void set_r(GLfloat b);

  GLfloat get_a() const;
  void set_a(GLfloat a);

  GLfloat get_b() const;
  void set_b(GLfloat b);

  GLfloat get_c() const;
  void set_c(GLfloat c);

  ~Sphere();
 private:
  GLfloat r;
  GLfloat a;
  GLfloat b;
  GLfloat c;

  GLint points_count;
  GLint layers_count;

  Vector position;

  std::pair<GLfloat, GLfloat> x_interval;
  std::pair<GLfloat, GLfloat> y_interval;
  std::pair<GLfloat, GLfloat> z_interval;

  GLuint texture;
};

