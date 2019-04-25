#include "bits/stdc++.h"
#include <GLFW/glfw3.h>

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::max;
using std::min;

/// SOME CLASSES & STRUCTS

struct vertex {
  vertex() : x(0), y(0) {};
  vertex(double x, double y) : x(x), y(y) {};
  double x;
  double y;
};

struct edge {
  edge(vertex f, vertex s) : first(f), second(s) {};
  double x() const { return second.x - first.x; }
  double y() const { return second.y - first.y; }
  vertex first;
  vertex second;
};

class polygon {
 public:
  polygon() : on_tour(0) { points = vector<vertex>(0); }
  //explicit polygon(const vector<vertex> &p) : points(p) {};

  const vector<vertex> &get_points() const { return points; };
  void set_points(const vector<vertex> &p) { points = p; };

  const int &get_on_tour() { return on_tour; };
  void set_on_tour(const int &t) { on_tour = t; };

  int size() const { return points.size(); }

  void add_vertex(double x, double y) {
    points.emplace_back(vertex(x, y));
  }

  void draw(GLenum type) {
    glBegin(type);
    for (int i = 0; i < points.size(); ++i) {
      glVertex2d(points[i].x, points[i].y);
    }
    glEnd();
  }

 private:
  vector<vertex> points;
  int on_tour;              // Направление обхода
};

class clipped_polygon {
 public:
  clipped_polygon() { points = old_points = vector<vertex>(0); }
  //explicit clipped_polygon(const vector<vertex> &p) : points(p), old_points(p) {};

  const vector<vertex> &get_points() const { return points; };
  void set_points(const vector<vertex> &p) { points = p; };

  void add_vertex(double x, double y) {
    points.emplace_back(vertex(x, y));
  }

  void swap_buffers() { points = old_points; }
  void load_buffer() { old_points = points; }

  int size() const { return points.size(); }

  void draw(GLenum type, bool partition_like_a_russian);

 private:
  vector<vertex> points, old_points;
};

bool is_clipping = false, no_to_clipping = false;
int width = 800,
    height = 800;
double kW = 1, kH = 1;

clipped_polygon object;
polygon clipper;
set<int> partition;

void clipped_polygon::draw(GLenum type, bool partition_like_a_russian) {
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

// SOME USEFUL FUNCS

const double eps = 1e-6;

double abs(const double &a) { return a < 0 ? -a : a; }

int normal(const double &a) { return a / abs(a); }

bool equal(const double &a, const double &b) { return abs(a - b) < eps; }

// Скалярное произведение отрезков с началом в 0 и концами в точках А и В.
double scalar_prod(const vertex &A, const vertex &B) { return A.x * B.x + A.y * B.y; }

// Векторное произведение отрезков с началом в 0 и концами в точках А и В.
double vector_prod(const vertex &A, const vertex &B) { return A.x * B.y - A.y * B.x; }

// Векторное произведение отрезков (векторов) А и В
double vector_prod(const edge &A, const edge &B) { return A.x() * B.y() - A.y() * B.x(); }

// Определяет точку пересечения отрезков А и В (вернее, прямых, их содержащих)
// Вызывается только тогда, когда прямые не параллельны
vertex intersection(const edge &A, const edge &B) {
  double dxA = A.first.x - A.second.x;
  double dyA = A.first.y - A.second.y;
  double prodA = vector_prod(A.first, A.second);

  double dxB = B.first.x - B.second.x;
  double dyB = B.first.y - B.second.y;
  double prodB = vector_prod(B.first, B.second);

  double denom = dxA * dyB - dyA * dxB;

  return vertex{(prodA * dxB - dxA * prodB) / denom,
                (prodA * dyB - dyA * prodB) / denom};
}

// Проверяет совпадение прямых, лежащих на отрезках А и В.

bool isParallel(const edge &A, const edge &B) {
  vertex normA = vertex(-A.y(), A.x()),         // Нормали к отрезкам
         normB = vertex(-A.y(), B.x());         // Вообще не используются, только для наглядности

  double a_A = -A.y(), b_A = A.x(), a_B = -B.y(), b_B = B.x();          // Коэффициенты общего уравнения прямых
  double c_A = -scalar_prod({-A.y(), A.x()}, {A.first.x, A.first.y}),   // Коэффициенты С - просто подставляем
      c_B = -scalar_prod({-B.y(), B.x()}, {B.first.x, B.first.y});      // начальную точку в уравнение к коэффициентами А и В

  if ((a_A == 0 && a_B == 0 && equal(b_A / b_B, c_A / c_B)) || (b_A == 0 && b_B == 0 && equal(a_A / a_B, c_A / c_B)))
    return true;        // Если параллельны осям

  return equal(a_A / a_B, b_A / b_B) && equal(a_A / a_B, c_A / c_B);      // Иначе пропорциональны коэффициенты
}

 /*
  * Определяет, лежит ли один из отрезков А, В внутри другого из них.
  * Проверяет, лежат ли точки одного отрезка в прямоугольнике, образованном максимальными и минимальными вершинами другого
  * Это достаточное условие, т. к. перед вызовом этой функции проверяется совпадение прямых на этих отрезках
  */
bool inner_line(const edge &A, const edge &B) {
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
          B.second.x <= max_X_A && B.second.x >= min_X_A &&
          B.second.y <= max_Y_A && B.second.y >= min_Y_A);

}

/// SUTHERLAND-HODGMAN ALG

// Итеративная функция алгоритма Сазерленда-Ходжмэна (по ребрам отсекателя)
vector<vertex> clip(const vector<vertex> &vertices,
                    const vertex &Ai, const vertex &Aj) {
  vector<vertex> tmp;
  for (int i = 0; i < vertices.size(); i++) {
    int j = (i + 1) % vertices.size();

    vertex S = vertices[i];
    vertex P = vertices[j];

    double iPos = (Aj.x - Ai.x) * (S.y - Ai.y) - (Aj.y - Ai.y) * (S.x - Ai.x);

    double kPos = (Aj.x - Ai.x) * (P.y - Ai.y) - (Aj.y - Ai.y) * (P.x - Ai.x);

    if (clipper.get_on_tour() > 0) {   // Обход против часовой стрелки - надо менять знаки
      iPos *= -1;
      kPos *= -1;
    }

    if (iPos < 0 && kPos < 0) {
      tmp.push_back(P);
    } else if (iPos >= 0 && kPos < 0) {
      tmp.push_back(intersection(edge{Ai, Aj}, edge{S, P}));
      tmp.push_back(P);
    } else if (iPos < 0 && kPos >= 0) {
      tmp.push_back(intersection(edge{Ai, Aj}, edge{S, P}));
    }
  }
  return tmp;
}

// Main-функция алгоритма Сазерленда-Ходжмэна
void sutherland_hodgman(clipped_polygon &object,
                        const polygon &clipper) {
  vector<vertex> tmp(object.get_points());
  for (int i = 0; i < clipper.size(); i++) {
    int k = (i + 1) % clipper.size();
    tmp = clip(tmp, clipper.get_points()[i], clipper.get_points()[k]);
  }
  object.set_points(tmp);
}


/// CALLBACKS


GLvoid key_callback(GLFWwindow *window, GLint key, GLint scancode, GLint action, GLint mods) {
  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    switch (key) {
      case GLFW_KEY_ESCAPE:glfwSetWindowShouldClose(window, GL_TRUE);
        break;
      case GLFW_KEY_ENTER:is_clipping = !is_clipping;
        if (is_clipping) {         // Разбиваем на отдельные области во избежание ложных ребер
          partition.clear();
          auto temp = object.get_points();
          for (int i = 0; i < temp.size() - 1; i++) {
            for (int j = i + 1; j < temp.size(); j++) {
              if (isParallel({temp[i], temp[i + 1]}, {temp[j % temp.size()], temp[(j + 1) % temp.size()]})
                  && inner_line({temp[i], temp[i + 1]}, {temp[j % temp.size()], temp[(j + 1) % temp.size()]})) {
                partition.insert(i);
                partition.insert(j);
              }
            }
          }
          object.load_buffer();
          sutherland_hodgman(object, clipper);
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
        object.add_vertex(static_cast<int>(x) / kW, height / kH - static_cast<int>(y) / kH);
        break;
      case GLFW_MOUSE_BUTTON_RIGHT:glfwGetCursorPos(window, &x, &y);
        if (clipper.size() <= 2 || !clipper.get_on_tour()) {          // Меньше трех точек или не определен обход - добавляем вершину
          clipper.add_vertex(static_cast<int>(x) / kW, height / kH - static_cast<int>(y) / kH);
          if (clipper.size() > 2) {                                   // Обход не опредеден - определяем его
            int i = 0;
            vector<vertex> tmp = clipper.get_points();
            do {
              edge e1(tmp[i % tmp.size()], tmp[(i + 1)  % tmp.size()]),
                   e2(tmp[(i + 1)  % tmp.size()], tmp[(i + 2)  % tmp.size()]);
              clipper.set_on_tour(normal(vector_prod(e1, e2)));
            } while (!clipper.get_on_tour());
          }
        } else {                                      // В противном случае добавляем точку (и инцидентные ей ребра) только тогда,
          double ord1 = 0, ord2 = 0, ord3 = 0;        // когда при этом не нарушается выпуклость отсекателя
          vector<vertex> tmp = clipper.get_points();
          edge e1(tmp[clipper.size() - 2], tmp[clipper.size() - 1]),
              e2(tmp[clipper.size() - 1], {static_cast<int>(x) / kW, height / kH - static_cast<int>(y) / kH}),
              e3({static_cast<int>(x) / kW, height / kH - static_cast<int>(y) / kH}, tmp[0]),
              e4(tmp[0], tmp[1]);
          ord1 = vector_prod(e1, e2);
          ord2 = vector_prod(e3, e4);
          ord3 = vector_prod(e2, e3);
          if (normal(ord1) == clipper.get_on_tour() &&
              normal(ord2) == clipper.get_on_tour() &&
              normal(ord3) == clipper.get_on_tour()) {
            clipper.add_vertex(static_cast<int>(x) / kW, height / kH - static_cast<int>(y) / kH);
          }
        }
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

    glClearColor(0.7, 1, 1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(kW, kH, 1);

    glLineWidth(3);
    glColor3b(0, 0, 127);
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
