#include <GLFW/glfw3.h>
#include <math.h>
#include "bits/stdc++.h"

using namespace std;
#define uint unsigned int

const double d = 1e-6;
const uint bgcolor = 0xA0FFFFFF, maincolor = 0x00FF00FF;

struct Edge {
  int x0, y0, x1, y1;
  int x_h;
  double tg;
  Edge(int x0, int y0, int x1, int y1) : x0(x0), y0(y0), x1(x1), y1(y1) {}

  void resized(float kW, float kH) {
    x0 *= kW;
    x1 *= kW;
    y0 *= kH;
    y1 *= kH;
    x_h *= kW;
    int dx = x1 - x0;
    int dy = -y1 + y0;
    double k = double(dy) / dx;
    tg = k;
  }

  bool operator==(const Edge &edge) const {
    return x0 == edge.x0 &&
        x1 == edge.x1 &&
        y0 == edge.y0 &&
        y1 == edge.y1 &&
        x_h == edge.x_h &&
        tg == edge.tg;
  }
};

struct Vertex {
  int x, y;
  vector<Edge> incidentEdges;
  Vertex(int x, int y) : x(x), y(y) {}

  void resized(float kW, float kH) {
    x *= kW;
    y *= kH;
    for (int i = 0; i < incidentEdges.size(); i++) {
      incidentEdges[i].resized(kW, kH);
    }
  }

  bool operator<(const Vertex &point) const {
    return y < point.y;
  }
};

bool fl = false, filter = false;
int width = 800,
    height = 800;

vector<uint> Pixels(height * width, bgcolor), oldPixels(height * width, bgcolor);
vector<Vertex> V;
vector<Edge> E;

uint verticesCount = 0;
uint color = 0;

void drawFilled(GLFWwindow *window) {
  glfwGetFramebufferSize(window, &width, &height);

  vector<Edge> CAP;
  vector<Vertex> sortedVertices = V;
  sort(sortedVertices.begin(), sortedVertices.end());
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      Pixels[(height - i - 1) * width + j] = bgcolor;
      oldPixels[(height - i - 1) * width + j] = bgcolor;
    }
  }
  for (int i = 0; i < verticesCount; i++) {
    Pixels[(height - sortedVertices[i].y - 1) * width + sortedVertices[i].x] = color;
    oldPixels[(height - sortedVertices[i].y - 1) * width + sortedVertices[i].x] = color;
    if (i < verticesCount - 1) {
      for (int j = 0; j < sortedVertices[i].incidentEdges.size(); j++) {
        Edge &e = sortedVertices[i].incidentEdges[j];
        auto f = find(CAP.begin(), CAP.end(), e);
        if (f != CAP.end()) {
          CAP.erase(f);
        } else {
          if (abs(e.tg) < d) {
            for (int w = min(e.x0, e.x1); w <= max(e.x0, e.x1); w++) {
              Pixels[(height - sortedVertices[i].y - 1) * width + w] = color;
              oldPixels[(height - sortedVertices[i].y - 1) * width + w] = color;
            }
          } else {
            CAP.push_back(e);
          }
        }
      }
      int y_cur = sortedVertices[i].y;
      while (y_cur < sortedVertices[i + 1].y) {
        vector<int> xs;
        for (int j = 0; j < CAP.size(); j++) {
          int y_min = min(CAP[j].y0, CAP[j].y1);
          int cur_x = CAP[j].x_h - abs(y_cur - y_min) * 1.0 / CAP[j].tg;
          xs.push_back(cur_x);
        }
        //if (xs.size() % 2 == 1)
        //  xs.pop_back();
        sort(xs.begin(), xs.end());
        for (int j = 0; j < xs.size(); j += 2) {
          for (int k = xs[j]; k <= xs[j + 1]; k++) {
            Pixels[(height - y_cur - 1) * width + k] = color;
            oldPixels[(height - y_cur - 1) * width + k] = color;
          }
        }
        y_cur++;
      }
    }
  }
}

void drawUnfilled(GLFWwindow *window) {
  glfwGetFramebufferSize(window, &width, &height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      Pixels[(height - i - 1) * width + j] = bgcolor;
      oldPixels[(height - i - 1) * width + j] = bgcolor;
    }
  }
  for (int i = 0; i < E.size(); i++) {
    int x0 = E[i].x0,
        y0 = E[i].y0,
        x1 = E[i].x1,
        y1 = E[i].y1;
    int dx = abs(x1 - x0),
        sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0),
        sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
      Pixels[(height - y0 - 1) * width + x0] = color;
      oldPixels[(height - y0 - 1) * width + x0] = color;
      if (x0 == x1 && y0 == y1) {
        break;
      }
      e2 = 2 * err;
      if (e2 >= dy) {
        err += dy;
        x0 += sx;
      }
      if (e2 <= dx) {
        err += dx;
        y0 += sy;
      }
    }
  }
}

void addVertex(int x, int y, GLFWwindow *window) {
  for (int i = 0; i < verticesCount; i++) {
    if (V[i].x == x && V[i].y == y) {
      return;
    }
  }
  verticesCount++;
  V.emplace_back(Vertex(x, y));

  if (verticesCount > 1) {
    if (!E.empty()) {
      E.pop_back();
    }
    if (!V[verticesCount - 2].incidentEdges.empty()) {
      V[verticesCount - 2].incidentEdges.pop_back();
    }
    if (!V[0].incidentEdges.empty()) {
      V[0].incidentEdges.pop_back();
    }

    int x0 = V[verticesCount - 2].x, y0 = V[verticesCount - 2].y;
    int x1 = V[verticesCount - 1].x, y1 = V[verticesCount - 1].y;
    Edge tmp = Edge(x0, y0, x1, y1);
    int dx = tmp.x1 - tmp.x0;
    int dy = (height - tmp.y1) - (height - tmp.y0);
    double k = double(dy) / dx;
    tmp.tg = k;
    tmp.x_h = y0 <= y1 ? x0 : x1;
    E.push_back(tmp);

    V[verticesCount - 2].incidentEdges.push_back(tmp);
    V[verticesCount - 1].incidentEdges.push_back(tmp);
    x0 = V[verticesCount - 1].x;
    y0 = V[verticesCount - 1].y;
    x1 = V[0].x;
    y1 = V[0].y;
    Edge e_cyclic(x0, y0, x1, y1);
    dx = e_cyclic.x1 - e_cyclic.x0;
    dy = (height - e_cyclic.y1) - (height - e_cyclic.y0);
    k = double(dy) / dx;
    e_cyclic.tg = k;
    e_cyclic.x_h = y0 <= y1 ? x0 : x1;
    E.push_back(e_cyclic);
    V[verticesCount - 1].incidentEdges.push_back(e_cyclic);
    V[0].incidentEdges.push_back(e_cyclic);
  }
}

void Filter() {
  const uint base[] = {0, 1, 0, 1, 2, 1, 0, 1, 0};
  const uint n = 6;

  for (int y = 1; y < height - 1; y++) {
    for (int x = 1; x < width - 1; x++) {
      uint c = 0;

      for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
          uint t = 1;
          for (uint k = 0; k < 3; ++k, t *= 256) {
            c += (uint) ((((Pixels[i + j * width]) >> (k * 8)) % 256) * base[(i - x + 1) - y + j + 1] / n) << (k * 8);
          }
          c += (uint) (((Pixels[i + j * width]) >> (3 * 8)) * base[(i - x + 1) - y + j + 1] / n) << (3 * 8);
        }
      }
      Pixels[x + y * width] = c;
    }
  }
}

void buffer_callback(GLFWwindow *window, int w, int h) {
  int oldW = width, oldH = height;
  glfwGetFramebufferSize(window, &width, &height);
  float kW = (float) width / oldW,
      kH = (float) height / oldH;
  for (int i = 0; i < V.size(); i++) {
    V[i].resized(kW, kH);
  }
  for (int i = 0; i < E.size(); i++) {
    E[i].resized(kW, kH);
  }
  //V.clear();
  //E.clear();
  Pixels.resize(width * height);
  oldPixels.resize(width * height);
  //fl = false;
  fill(Pixels.begin(), Pixels.end(), bgcolor);
  fill(oldPixels.begin(), oldPixels.end(), bgcolor);
  if (fl)
    drawFilled(window);
  else
    drawUnfilled(window);
  //verticesCount = 0;
  glViewport(0, 0, width, height);
}

/*
 * ENTER -> fill
 * SPACE -> filter
 * left button -> add vertex
 */


void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    addVertex(static_cast<int>(x), static_cast<int>(y), window);
    if (fl)
      drawFilled(window);
    else
      drawUnfilled(window);
  }
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    if (key == GLFW_KEY_ESCAPE)
      glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_BACKSPACE) {
      V.clear();
      E.clear();
      fl = false;
      fill(Pixels.begin(), Pixels.end(), bgcolor);
      fill(oldPixels.begin(), oldPixels.end(), bgcolor);
      verticesCount = 0;
    }
    if (key == GLFW_KEY_ENTER) {
      fl = !fl;
      if (fl) {
        drawFilled(window);
      } else {
        drawUnfilled(window);
      }
    }
    if (key == GLFW_KEY_SPACE) {
      filter = !filter;
      if (filter) {
        oldPixels = Pixels;
        Filter();
      } else {
        Pixels = oldPixels;
      }
    }
  }
}

int main() {
  color = maincolor;
  
  GLFWwindow *window;

  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  window = glfwCreateWindow(width, height, "Lab4", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, buffer_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, Pixels.data());
    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
