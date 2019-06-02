#include <GLFW/glfw3.h>
#include "SOIL.h"
#include "bits/stdc++.h"

#include "Sphere.h"
#include "Cube.h"
#include "Config.h"

#define INIT_WINDOW_WIDTH 1000
#define INIT_WINDOW_HEIGHT 800

#define sphere_Points 20
#define sphere_Layers 10


#define sphere_A 1.f
#define sphere_B 1.f
#define sphere_C 1.f
#define sphere_R 70.f
#define cube_A   350.f

Config config("/home/alexey/CLionProjects/Lab6/config.json");

GLboolean polygon_mode = true;
GLboolean textures_mode = true;
GLboolean pause_mode = false;

GLint w, h;

Sphere sphere(sphere_R,
              sphere_A,
              sphere_B,
              sphere_C,
              sphere_Points,
              sphere_Layers,
              config.sphere_pos);

Cube cube(cube_A, cube_A, cube_A);

GLfloat d_time = 0.f;
GLfloat last_time = 0.f;

std::unordered_map<std::string, GLuint> textures;

void LoadTexture(std::string name, std::string path) {
  int width, height;
  unsigned char *image = SOIL_load_image(path.c_str(), &width, &height, nullptr, SOIL_LOAD_RGB);

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glBindTexture(GL_TEXTURE_2D, 0);

  SOIL_free_image_data(image);
  textures[name] = texture;
}

void resize_callback(GLFWwindow *window, int new_w, int new_h) {
  w = new_w, h = new_h;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  } else if (key == GLFW_KEY_R && mods == GLFW_MOD_SHIFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    sphere.set_r(sphere.get_r() + 0.1);
    sphere.rebuild();
  } else if (key == GLFW_KEY_R && mods == GLFW_MOD_CONTROL && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    if (sphere.get_r() > 1) {
      sphere.set_r(sphere.get_r() - 0.1);
      sphere.rebuild();
    }
  } else if (key == GLFW_KEY_EQUAL && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    sphere.set_layers_count(sphere.get_layers_count() + 1);
    sphere.rebuild();
  } else if (key == GLFW_KEY_MINUS && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    if (sphere.get_layers_count() > 1) {
      sphere.set_layers_count(sphere.get_layers_count() - 1);
      sphere.rebuild();
    }
  } else if (key == GLFW_KEY_COMMA && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    if (sphere.get_points_count() > 3) {
      sphere.set_points_count(sphere.get_points_count() - 1);
      sphere.rebuild();
    }
  } else if (key == GLFW_KEY_PERIOD && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    sphere.set_points_count(sphere.get_points_count() + 1);
    sphere.rebuild();
  } else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
    pause_mode = !pause_mode;
  } else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
    if (polygon_mode) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    polygon_mode = !polygon_mode;
  } else if (key == GLFW_KEY_T && action == GLFW_PRESS) {
    if (!textures_mode) {
      sphere.set_texture_mode(true);
    } else {
      sphere.set_texture_mode(false);
    }
    textures_mode = !textures_mode;
  }
}

void projection(GLint width, GLint height) {

  GLfloat project[] = {
      1.f, 0.f, 0.f, 0.5f,
      0.f, 1.f, 0.f, 0.f,
      0.f, 0.f, 1.f, 0.5f,
      0.f, 0.f, 0.f, 1.f};

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMultMatrixf(project);

  glOrtho(-w / 2, w / 2, -h / 2,
          h / 2, -(w + h) / 4, (w + h) / 4);

}

void draw() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  cube.draw();
  sphere.draw();
}

void rebound() {
  auto sphere_x_interval = sphere.get_x_interval();
  auto sphere_y_interval = sphere.get_y_interval();
  auto sphere_z_interval = sphere.get_z_interval();

  auto cube_x_interval = cube.get_x_interval();
  auto cube_y_interval = cube.get_y_interval();
  auto cube_z_interval = cube.get_z_interval();

  Vector pos = sphere.get_position();
  if ((sphere_x_interval.first + pos.x < cube_x_interval.first && config.sphere_velocity.x < 0)
      || (sphere_x_interval.second + pos.x > cube_x_interval.second && config.sphere_velocity.x > 0)) {
    config.sphere_velocity.x *= -1.f;
  }

  if ((sphere_y_interval.first + pos.y < cube_y_interval.first && config.sphere_velocity.y < 0)
      || (sphere_y_interval.second + pos.y > cube_y_interval.second && config.sphere_velocity.y > 0)) {
    config.sphere_velocity.y *= -1.f;
  }

  if ((sphere_z_interval.first + pos.z < cube_z_interval.first && config.sphere_velocity.z < 0)
      || (sphere_z_interval.second + pos.z > cube_z_interval.second && config.sphere_velocity.z > 0)) {
    config.sphere_velocity.z *= -1.f;
  }
}

void animation() {
  if(pause_mode)
    return;
  GLfloat dx = config.sphere_velocity.x * d_time;
  GLfloat dy = config.sphere_velocity.y * d_time;
  GLfloat dz = config.sphere_velocity.z * d_time;

  Vector pos = sphere.get_position();
  pos.x += dx;
  pos.y += dy;
  pos.z += dz;

  sphere.set_position(pos);
  rebound();

  config.sphere_pos.x = pos.x;
  config.sphere_pos.y = pos.y;
  config.sphere_pos.z = pos.z;

}

int main() {
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    exit(EXIT_FAILURE);
  }

  GLFWwindow
      *window = glfwCreateWindow(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT, "Lab6", nullptr, nullptr);
  if (!window) {
    fprintf(stderr, "Failed to open GLFW window.\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetWindowSizeCallback(window, resize_callback);

  glfwGetFramebufferSize(window, &w, &h);

  cube.rebuild();
  sphere.rebuild();

  //glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);
  //glDepthFunc(GL_LEQUAL);

  //glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_SMOOTH);



#ifdef LIGHT


  GLfloat amb[] = {.8f, .8f, .8f, 1.f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

  GLfloat lightPos[] = {250.f, 250.f, -700.f, 100.f};
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  GLfloat light_amb[] = {.75f, .75f, .75f, 1.f};
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);

  GLfloat light_diff[] = {.75f, .75f, .75f, 1.f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);

  GLfloat light_spec[] = {85, 85, 85, 1.f};
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_spec);

  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, .5f);
  glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, .01f);
  glEnable(GL_LIGHT0);

#endif

  LoadTexture("brick", "/home/alexey/CLionProjects/Lab6/brick.jpg");
  cube.set_texture(textures["brick"]);
  sphere.set_texture(textures["brick"]);

  while (!glfwWindowShouldClose(window)) {

    GLfloat current_frame_time = glfwGetTime();
    d_time = current_frame_time - last_time;
    last_time = current_frame_time;

    glClearColor(0.7, 1, 1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, w, h);
    projection(w, h);
    draw();

    glfwPollEvents();
    glfwSwapBuffers(window);
    animation();
  }
  glfwDestroyWindow(window);
  glfwTerminate();

  config.save_config("/home/alexey/CLionProjects/Lab6/config.json");
  exit(EXIT_SUCCESS);
}