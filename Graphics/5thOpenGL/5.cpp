#include "bits/stdc++.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>

//using namespace std;
using std::cout;
using std::endl;
using std::vector;
#define uint unsigned int

struct Vertex {
  Vertex() : x(0), y(0) {};
  Vertex(int x, int y) : x(x), y(y) {};
  int x;
  int y;
};

struct Edge {
  Edge(Vertex f, Vertex s) : first(f), second(s) {};
  int x() { return second.x - first.x; }
  int y() { return second.y - first.y; }
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

  void add_vertex(int x, int y) {
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

  void add_vertex(int x, int y) {
    points.emplace_back(Vertex(x, y));
  }

 protected:
  vector<Vertex> points, old_points;
};

bool isClipping = false;
int order = 0;
int width = 800,
    height = 800;

//#define test

#ifdef test
ClippedPolygon object({Vertex{200, 300}, Vertex{400, 500}, Vertex{600, 400}});
Polygon clipper({Vertex{300, 300}, Vertex{300, 400}, Vertex{400, 400}, Vertex{400, 300}});
#endif

#ifndef test
ClippedPolygon object;
Polygon clipper;
#endif

Vertex intersection(const Edge &A, const Edge &B) {
  int dxA = A.first.x - A.second.x;
  int dyA = A.first.y - A.second.y;
  int prodA = A.first.x * A.second.y - A.first.y * A.second.x;

  int dxB = B.first.x - B.second.x;
  int dyB = B.first.y - B.second.y;
  int prodB = B.first.x * B.second.y - B.first.y * B.second.x;

  int denom = dxA * dyB - dyA * dxB;

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

    int iPos = (Aj.x - Ai.x) * (S.y - Ai.y) - (Aj.y - Ai.y) * (S.x - Ai.x);

    int kPos = (Aj.x - Ai.x) * (P.y - Ai.y) - (Aj.y - Ai.y) * (P.x - Ai.x);

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

GLvoid key_callback(GLFWwindow *window, GLint key, GLint scancode, GLint action, GLint mods) {
  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    switch (key) {
      case GLFW_KEY_ESCAPE:glfwSetWindowShouldClose(window, GL_TRUE);
        break;
      case GLFW_KEY_ENTER:isClipping = !isClipping;
        if (isClipping) {
          object.load_buffer();
          sutherland_hodgman(object, clipper);
        } else object.swap_buffers();
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

void draw(const vector<Vertex> &points) {
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < points.size(); ++i) {
    glVertex2i(points[i].x, points[i].y);
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

    GLint w, h;
    glfwGetFramebufferSize(window, &w, &h);

    glViewport(0, 0, width, height);

    glClearColor(0.7, 1, 1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);

    glLineWidth(2);
    glColor3b(50, 0, 127);
    draw(object.getPoints());

    glLineWidth(3);
    glColor3b(127, 0, 0);
    draw(clipper.getPoints());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
