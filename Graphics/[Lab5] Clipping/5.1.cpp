#include "bits/stdc++.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>

//using namespace std;
using std::cout;
using std::endl;
using std::vector;
using std::set;
#define uint unsigned int

struct Vertex {
  Vertex() : x(0), y(0) {};
  Vertex(double x, double y) : x(x), y(y) {};
  double x;
  double y;
};

struct Edge {
  Edge(Vertex f, Vertex s) : first(f), second(s) {};
  double x() { return second.x - first.x; }
  double y() { return second.y - first.y; }
  Vertex first;
  Vertex second;
};

class Polygon {
 public:
  Polygon() { points = vector<Vertex>(0); }
  explicit Polygon(const vector<Vertex> &p) : points(p) {};

  const vector<Vertex> &getPoints() const { return points; };
  void setPoints(const vector<Vertex> &p) { points = p; };

  int size() const { return points.size(); }

  void add_vertex(double x, double y) {
    points.emplace_back(Vertex(x, y));
  }

 protected:
  vector<Vertex> points;
};

class ClippedPolygon {
 public:
  ClippedPolygon() { points = old_points = vector<Vertex>(0); }
  explicit ClippedPolygon(const vector<Vertex> &p) : points(p), old_points(p) {};

  const vector<Vertex> &getPoints() const { return points; };
  void setPoints(const vector<Vertex> &p) { points = p; };
  void swap_buffers() { points = old_points; }
  void load_buffer() { old_points = points; }

  int size() const { return points.size(); }

  void add_vertex(double x, double y) {
    points.emplace_back(Vertex(x, y));
  }

 protected:
  vector<Vertex> points, old_points;
};

bool is_clipping = false, no_to_clipping = false;
int order = 0;
int width = 800,
    height = 800;

// #define test

#ifdef test
ClippedPolygon object({Vertex{200, 300}, Vertex{400, 500}, Vertex{600, 400}});
Polygon clipper({Vertex{200, 300}, Vertex{200, 400}, Vertex{500, 400}, Vertex{500, 300}});
#endif

//ClippedPolygon object;
//set<int> partition;

#ifndef test
ClippedPolygon object;
Polygon clipper;
set<int> partition;
#endif

Vertex intersection(const Edge &A, const Edge &B) {
  double dxA = A.first.x - A.second.x;
  double dyA = A.first.y - A.second.y;
  double prodA = A.first.x * A.second.y - A.first.y * A.second.x;

  double dxB = B.first.x - B.second.x;
  double dyB = B.first.y - B.second.y;
  double prodB = B.first.x * B.second.y - B.first.y * B.second.x;

  double denom = dxA * dyB - dyA * dxB;

  return Vertex{(prodA * dxB - dxA * prodB) / denom,
                (prodA * dyB - dyA * prodB) / denom};
}

vector<Vertex> clip(const vector<Vertex> &vertices,
                    const Vertex &Ai, const Vertex &Aj) {
  vector<Vertex> tmp;
  for (int i = 0; i < vertices.size(); i++) {
    int j = (i + 1) % vertices.size();

    Vertex S = vertices[i];
    Vertex P = vertices[j];

    double iPos = (Aj.x - Ai.x) * (S.y - Ai.y) - (Aj.y - Ai.y) * (S.x - Ai.x);

    double kPos = (Aj.x - Ai.x) * (P.y - Ai.y) - (Aj.y - Ai.y) * (P.x - Ai.x);

    if (order > 0) {   // Обход против часовой стрелки - надо менять знаки
      iPos *= -1;
      kPos *= -1;
    }

    if (iPos < 0 && kPos < 0) {
      tmp.push_back(P);
    } else if (iPos >= 0 && kPos < 0) {
      tmp.push_back(intersection(Edge{Ai, Aj}, Edge{S, P}));
      tmp.push_back(P);
    } else if (iPos < 0 && kPos >= 0) {
      tmp.push_back(intersection(Edge{Ai, Aj}, Edge{S, P}));
    }
  }
  return tmp;
}

void sutherland_hodgman(ClippedPolygon &object,
                        const Polygon &clipper) {
  vector<Vertex> tmp(object.getPoints());
  for (int i = 0; i < clipper.size(); i++) {
    int k = (i + 1) % clipper.size();
    tmp = clip(tmp, clipper.getPoints()[i], clipper.getPoints()[k]);
  }
  object.setPoints(tmp);
}

double scolarProd(const Vertex &A, const Vertex &B) {
  return A.x * B.x + A.y * B.y;
}

const double eps = 1e-6;

double abs(const double &a){
  return a < 0 ? -a : a;
}

bool equal(const double &a, const double &b) {
  return abs(a - b) < eps;
}

bool isParallel(const Edge &A, const Edge &B) {
  double xA = A.second.x - A.first.x, yA = A.second.y - A.first.y;
  double xB = B.second.x - B.first.x, yB = B.second.y - B.first.y;

  Vertex normA = Vertex(-yA, xA), normB = Vertex(-yB, xB);

  double a_A = -yA, b_A = xA, a_B = -yB, b_B = xB;
  double c_A = -scolarProd({-yA, xA}, {A.first.x, A.first.y}),
      c_B = -scolarProd({-yB, xB}, {B.first.x, B.first.y});

  return equal(a_A / a_B, b_A / b_B) && equal(a_A / a_B, c_A / c_B);
}

GLvoid key_callback(GLFWwindow *window, GLint key, GLint scancode, GLint action, GLint mods) {
  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    switch (key) {
      case GLFW_KEY_ESCAPE:glfwSetWindowShouldClose(window, GL_TRUE);
        break;
      case GLFW_KEY_ENTER:is_clipping = !is_clipping;
        if (is_clipping) {
          object.load_buffer();
          sutherland_hodgman(object, clipper);

          partition.clear();
          auto temp = object.getPoints();
          for (int i = 0; i < temp.size() - 1; i++) {
            for (int j = i + 1; j < temp.size(); j++) {
              if (isParallel({temp[i], temp[i + 1]}, {temp[j % temp.size()], temp[(j + 1) % temp.size()]})) {
                partition.insert(i);
                partition.insert(j);
              }
              cout << isParallel({temp[i], temp[i + 1]}, {temp[j % temp.size()], temp[(j + 1) % temp.size()]})
                   << " " << i << "  " << j
                   << "  [(" << temp[i].x << ", " << temp[i].y << ") , (" << temp[i + 1].x << ", " << temp[i + 1].y
                   << ")]; "
                   << "  [(" << temp[j % temp.size()].x << ", " << temp[j % temp.size()].y << ") , ("
                   << temp[(j + 1) % temp.size()].x << ", " << temp[(j + 1) % temp.size()].y << ")]; " << endl;
            }
            cout << endl;
          }

        } else object.swap_buffers();
        break;
      case GLFW_KEY_SPACE:
        no_to_clipping = !no_to_clipping;
        break;
    }
  }
}

GLvoid mouse_button_callback(GLFWwindow *window, GLint button, GLint action, GLint mods) {
  if (action == GLFW_PRESS) {
    double x, y;
    switch (button) {
      case GLFW_MOUSE_BUTTON_LEFT:glfwGetCursorPos(window, &x, &y);
        object.add_vertex(static_cast<int>(x), height - static_cast<int>(y));
        cout << "BLUE: " << x << ", " << y << endl;
        break;
      case GLFW_MOUSE_BUTTON_RIGHT:glfwGetCursorPos(window, &x, &y);
        clipper.add_vertex(static_cast<int>(x), height - static_cast<int>(y));
        if (clipper.size() > 2 && !order) {
          int i = 0;
          vector<Vertex> tmp = clipper.getPoints();
          do {
            Edge e1(tmp[i], tmp[i + 1]), e2(tmp[i + 1], tmp[i + 2]);
            order = e1.x() * e2.y() - e1.y() * e2.x();
          } while (i && !order);
          cout << order << endl;
        }
        cout << "RED: " << x << ", " << y << endl;
        break;
    }
  }
}

void draw(const vector<Vertex> &points, GLenum type, bool partition_like_a_russian) {
  if (partition_like_a_russian) {
    auto iter = partition.begin();
    int i = *iter;
    iter++;
    while (iter != partition.end()) {
      glBegin(type);
      do {
        i++;
        glVertex2d(points[i % points.size()].x, points[i % points.size()].y);
      } while (((i % points.size()) != *iter) && (i % points.size()) != *partition.begin());
      glEnd();
      iter++;
    }

    glBegin(type);
    do {
      i++;
      glVertex2d(points[i % points.size()].x, points[i % points.size()].y);
    } while ((i % points.size()) != *partition.begin());
    glEnd();

    return;
  }
  glBegin(type);
  for (int i = 0; i < points.size(); ++i) {
    glVertex2d(points[i].x, points[i].y);
  }
  glEnd();
}

int main() {

  GLFWwindow *window;

  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  window = glfwCreateWindow(width, height, "Lab5", NULL, NULL);

  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);

  while (!glfwWindowShouldClose(window)) {

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);

    glViewport(0, 0, width, height);

    glClearColor(0.7, 1, 1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);

    glLineWidth(3);
    glColor3b(50, 0, 127);
    draw(object.getPoints(), /*is_clipping ? GL_LINE_LOOP : */GL_LINE_LOOP, is_clipping && !partition.empty());

    glColor3b(127, 0, 0);
    if (!no_to_clipping)
      draw(clipper.getPoints(), GL_LINE_LOOP, false);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

