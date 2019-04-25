#include "bits/stdc++.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>

//using namespace std;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::max;
using std::min;
#define uint unsigned int

struct Vertex {
  Vertex() : x(0), y(0) {};
  Vertex(double x, double y) : x(x), y(y) {};
  double x;
  double y;
};

struct Edge {
  Edge(Vertex f, Vertex s) : first(f), second(s) {};
  double x() const { return second.x - first.x; }
  double y() const { return second.y - first.y; }
  Vertex first;
  Vertex second;
};

class Polygon {
 public:
  Polygon() : on_tour(0) { points = vector<Vertex>(0); }
  //explicit Polygon(const vector<Vertex> &p) : points(p) {};

  const vector<Vertex> &getPoints() const { return points; };
  void setPoints(const vector<Vertex> &p) { points = p; };

  const int &get_on_tour() { return on_tour; };
  void set_on_tour(const int &t) { on_tour = t; };

  int size() const { return points.size(); }

  void add_vertex(double x, double y) {
    points.emplace_back(Vertex(x, y));
  }

  void draw(GLenum type) {
    glBegin(type);
    for (int i = 0; i < points.size(); ++i) {
      glVertex2d(points[i].x, points[i].y);
    }
    glEnd();
  }

 private:
  vector<Vertex> points;
  int on_tour;

};

class ClippedPolygon {
 public:
  ClippedPolygon() { points = old_points = vector<Vertex>(0); }
  //explicit ClippedPolygon(const vector<Vertex> &p) : points(p), old_points(p) {};

  const vector<Vertex> &getPoints() const { return points; };
  void setPoints(const vector<Vertex> &p) { points = p; };

  void add_vertex(double x, double y) {
    points.emplace_back(Vertex(x, y));
  }

  void swap_buffers() { points = old_points; }
  void load_buffer() { old_points = points; }

  int size() const { return points.size(); }

  void draw(GLenum type, bool partition_like_a_russian);

 private:
  vector<Vertex> points, old_points;
};

bool is_clipping = false, no_to_clipping = false;
int order = 0;
int width = 800,
    height = 800;

//#define debug

#ifdef debug
//ClippedPolygon object({Vertex{200, 300}, Vertex{400, 500}, Vertex{600, 400}});
Polygon clipper({Vertex{200, 200}, Vertex{200, 400}, Vertex{600, 400}, Vertex{600, 200}});
ClippedPolygon object;
set<int> partition;
#endif

//ClippedPolygon object;
//set<int> partition;

#ifndef debug
ClippedPolygon object;
Polygon clipper;
set<int> partition;
#endif

void ClippedPolygon::draw(GLenum type, bool partition_like_a_russian) {
  if (partition_like_a_russian && size() > 4 && !partition.empty()) {
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

double scalar_prod(const Vertex &A, const Vertex &B) {
  return A.x * B.x + A.y * B.y;
}

double vector_prod(const Edge &A, const Edge &B) {
  return A.x() * B.y() - A.y() * B.x();
}

const double eps = 1e-6;

double abs(const double &a) { return a < 0 ? -a : a; }

int normal(const double &a) { return a / abs(a); }

bool equal(const double &a, const double &b) {
  return abs(a - b) < eps;
}

bool isParallel(const Edge &A, const Edge &B) {
  double xA = A.second.x - A.first.x, yA = A.second.y - A.first.y;
  double xB = B.second.x - B.first.x, yB = B.second.y - B.first.y;

  Vertex normA = Vertex(-yA, xA), normB = Vertex(-yB, xB);

  double a_A = -yA, b_A = xA, a_B = -yB, b_B = xB;
  double c_A = -scalar_prod({-yA, xA}, {A.first.x, A.first.y}),
      c_B = -scalar_prod({-yB, xB}, {B.first.x, B.first.y});

  if ((a_A == 0 && a_B == 0 && equal(b_A / b_B, c_A / c_B)) || (b_A == 0 && b_B == 0 && equal(a_A / a_B, c_A / c_B)))
    return true;

  return equal(a_A / a_B, b_A / b_B) && equal(a_A / a_B, c_A / c_B);
}

bool innerLine(const Edge &A, const Edge &B) {

  double max_X_A = max(A.first.x, A.second.x), min_X_A = min(A.first.x, A.second.x),
      max_Y_A = max(A.first.y, A.second.y), min_Y_A = min(A.first.y, A.second.y),
      max_X_B = max(B.first.x, B.second.x), min_X_B = min(B.first.x, B.second.x),
      max_Y_B = max(B.first.y, B.second.y), min_Y_B = min(B.first.y, B.second.y);

  return (A.first.x <= max_X_B && A.first.x >= min_X_B &&
      A.first.y <= max_Y_B && A.first.y >= min_Y_B &&
      A.second.x <= max_X_B && A.second.x >= min_X_B &&
      A.second.y <= max_Y_B && A.second.y >= min_Y_B) ||
      (B.first.x <= max_X_A && B.first.x >= min_X_A &&
          B.first.y <= max_Y_A && B.first.y >= min_Y_A &&
          A.second.x <= max_X_A && B.second.x >= min_X_A &&
          B.second.y <= max_Y_A && B.second.y >= min_Y_A);

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
              if (isParallel({temp[i], temp[i + 1]}, {temp[j % temp.size()], temp[(j + 1) % temp.size()]})
                  && innerLine({temp[i], temp[i + 1]}, {temp[j % temp.size()], temp[(j + 1) % temp.size()]})) {
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
      case GLFW_KEY_SPACE:no_to_clipping = !no_to_clipping;
        break;
    }
  }
}

float kW = 1, kH = 1;

GLvoid mouse_button_callback(GLFWwindow *window, GLint button, GLint action, GLint mods) {
  if (action == GLFW_PRESS) {
    double x, y;
    switch (button) {
      case GLFW_MOUSE_BUTTON_LEFT:glfwGetCursorPos(window, &x, &y);
        object.add_vertex(static_cast<int>(x) / kW, height / kH - static_cast<int>(y) / kH);
        cout << "BLUE: " << x << ", " << y << endl;
        break;
      case GLFW_MOUSE_BUTTON_RIGHT:glfwGetCursorPos(window, &x, &y);
        if (clipper.size() <= 2 || !order) {
          clipper.add_vertex(static_cast<int>(x) / kW, height / kH - static_cast<int>(y) / kH);
          if (clipper.size() > 2) {
            int i = 0;
            vector<Vertex> tmp = clipper.getPoints();
            do {
              Edge e1(tmp[i], tmp[i + 1]), e2(tmp[i + 1], tmp[i + 2]);
              order = e1.x() * e2.y() - e1.y() * e2.x();
            } while (i && !order);
            clipper.set_on_tour(order / abs(order));
            cout << order / abs(order) << endl;
          }
        } else {
          double ord1 = 0, ord2 = 0, ord3 = 0;
          vector<Vertex> tmp = clipper.getPoints();
          Edge e1(tmp[clipper.size() - 2], tmp[clipper.size() - 1]),
               e2(tmp[clipper.size() - 1], {static_cast<int>(x) / kW, height / kH - static_cast<int>(y) / kH}),
               e3({static_cast<int>(x) / kW, height / kH - static_cast<int>(y) / kH}, tmp[0]),
               e4(tmp[0], tmp[1]);
          ord1 = vector_prod(e1, e2);
          ord2 = vector_prod(e3, e4);
          ord3 = vector_prod(e2, e3);
          if(normal(ord1) == clipper.get_on_tour() &&
             normal(ord2) == clipper.get_on_tour() &&
             normal(ord3) == clipper.get_on_tour()){
            clipper.add_vertex(static_cast<int>(x) / kW, height / kH - static_cast<int>(y) / kH);
          }
          cout << ord1 / abs(ord1) << endl;
        }

        cout << "RED: " << x << ", " << y << endl;
        break;
    }
  }
}

void buffer_callback(GLFWwindow *window, int w, int h) {
  int oldW = width, oldH = height;
  glfwGetFramebufferSize(window, &width, &height);
  kW *= (float) width / oldW;
  kH *= (float) height / oldH;
  glViewport(0, 0, width, height);
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
  glfwSetFramebufferSizeCallback(window, buffer_callback);

  glViewport(0, 0, width, height);

  while (!glfwWindowShouldClose(window)) {

    //glViewport(0, 0, width, height);

    glClearColor(0.7, 1, 1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(kW, kH, 1);

    glLineWidth(3);
    glColor3b(50, 0, 127);
    object.draw(GL_LINE_LOOP, is_clipping);

    glColor3b(127, 0, 0);
    if (!no_to_clipping)
      clipper.draw(GL_LINE_LOOP);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
