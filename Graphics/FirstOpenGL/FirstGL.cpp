#define GLEW_STATIC 
#include <GL/glew.h> 
#include <GLFW/glfw3.h> 
#include <iostream> 
using namespace std;

float a = 1, b = 0.2;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_RIGHT/* && action == GLFW_PRESS*/) {
		float c = a;
		a = b;
		b = c;
	}
}

int main() {

	if (!glfwInit()) {
		cout << "Failed to initialize GLFW" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Simple example", nullptr, nullptr);
	if (!window) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		cout << "Failed to initialize GLEW" << endl;
		glfwTerminate();
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glfwSetKeyCallback(window, key_callback);
	glViewport(0, 0, width, height);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glPointSize(1.0);
		glBegin(GL_POLYGON);
		glColor3f(0, 0, 1); glVertex2f(a, b);    
		glColor3f(0, 0, 1); glVertex2f(-a, b);
		glColor3f(0, 0, 1); glVertex2f(-a, -b);
		glColor3f(0, 0, 1); glVertex2f(a, -b);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
