#include <GLFW/glfw3.h>
#include "bits/stdc++.h"
using namespace std;

const int N = 3;

struct Point {
  GLint x;
  GLint y;
};

GLfloat *buff;
vector<Point> points;

bool filterFlag = false;

int height = 800;
int width = 800;

void fillBuf() {
  fill_n(buff, height * width * N, 1);
}

int sign(int x) {
  return (x == 0) ? 0 : x / abs(x);
}

void fillZero(int x, int y) {
  for (int c = 0; c < N; c++) {
    buff[(x + y * width) * N + c] = 0;
  }
}

void drawLine(const Point &pA, const Point &pB) {
  bool flag = false;

  int x = pA.x,
      y = pA.y;

  int dx = abs(pB.x - pA.x),
      dy = abs(pB.y - pA.y);

  int sX = sign(pB.x - pA.x),
      sY = sign(pB.y - pA.y);

  if (dy > dx) {
    flag = true;
    std::swap(dx, dy);
  }

  int k = 2 * dy - dx;

  for (int i = 0; i < dx; i++) {
    fillZero(x, y);

    if (k >= 0) {
      if (flag) {
        x += sX;
      } else {
        y += sY;
      }
      k -= 2 * dx;
      fillZero(x, y);
    }

    if (flag) {
      y += sY;
    } else {
      x += sX;
    }

    k += 2 * dy;
  }

}

void filterFrame() {
  const int kernel[] = {0, 1, 0, 1, 2, 1, 0, 1, 0};
  const double norm = 6;

  for (int y = 1; y < height - 1; y++) {
    for (int x = 1; x < width - 1; x++) {
      float c = 0;

      for (int i = x - 1; i <= x + 1; i++) {
        for (int k = y - 1; k <= y + 1; k++) {
          c += kernel[(i - x + 1) * N - y + 1 + k] * buff[(i + k * width) * N];
        }
      }

      for (int i = 0; i < N; i++) {
        buff[(x + y * width) * N + i] = c / norm;
      }
    }
  }
}

void draw(GLFWwindow *window) {
  glClear(GL_COLOR_BUFFER_BIT);

  fillBuf();

  if (!points.empty()) {
    for (int i = 0; i < points.size(); i++)
      drawLine(points[i], points[(i + 1) % points.size()]);
  }

  if (filterFlag) {
    filterFrame();
  }

  glDrawPixels(width, height, GL_RGB, GL_FLOAT, (void *) buff);
  glfwSwapBuffers(window);
}

void buffer_callback(GLFWwindow *window, int w, int h) {
  height = h;
  width = w;

  delete[] buff;
  points.clear();
  filterFlag = false;

  buff = new GLfloat[width * height * N];
  fillBuf();
  glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {

      case GLFW_KEY_ENTER:filterFlag = !filterFlag;
        break;

      case GLFW_KEY_DELETE:points.clear();
        filterFlag = false;
        fillBuf();
        break;

      case GLFW_KEY_ESCAPE:glfwSetWindowShouldClose(window, GL_TRUE);
        break;
    }
  }
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
  if (action == GLFW_PRESS) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      double x, y;
      glfwGetCursorPos(window, &x, &y);
      fillBuf();
      Point tmp{
          static_cast<int>(x),
          static_cast<int>(height - y)
      };
      points.push_back(tmp);
    }
  }
}

int main() {

  if (!glfwInit()) {
    return EXIT_FAILURE;
  }
  GLFWwindow *window = glfwCreateWindow(width, height, "Lab 4", NULL, NULL);

  if (!window) {
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetWindowSizeCallback(window, buffer_callback);

  buff = new GLfloat[width * height * N];
  fillBuf();
  glViewport(0, 0, width, height);

  while (!glfwWindowShouldClose(window)) {
    draw(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  delete[] buff;
  return EXIT_SUCCESS;
}
