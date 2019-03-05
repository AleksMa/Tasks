#define GLEW_STATIC 
#include <GL/glew.h> 
#include <GLFW/glfw3.h> 
#include <iostream> 
using namespace std;

GLfloat a = 1.0f, b = 0.2f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		GLfloat c = a;
		a = b;
		b = c;
	}
}

int main() {

	glfwInit();
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "FirstLab", NULL, NULL);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glfwSetKeyCallback(window, key_callback);
	glViewport(0, 0, width, height);

	while (!glfwWindowShouldClose(window)) {
		int width, height;

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		float ratio;
		glfwGetFramebufferSize(window, &width, &height);
		
		ratio = width / (float)height;
		glViewport(0, 0, width, height);


		

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);

		
		glLoadIdentity();
		glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
		

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
