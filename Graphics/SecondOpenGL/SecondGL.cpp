#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>

void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow* initWindow(const int resX, const int resY)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(resX, resY, "TEST", NULL, NULL);

	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, controls);

	// Get info of GPU and supported OpenGL version
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST); // Depth Testing
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	return window;
}

void drawCube()
{
	GLfloat vertices[] =
	{
		-1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
		1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
		-1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
		-1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
	};

	GLfloat colors[] =
	{
		0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
		1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
		0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
		0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
	};

	static float alpha = 0;
	//attempt to rotate cube
	glRotatef(alpha, 1, 1, 0);

	GLfloat r = 1.f;
	GLfloat g = 0.f;
	GLfloat b = 0.f;



	const int type = GL_POLYGON;

	GLfloat size = 0.5f;
	GLfloat offset = 0.5f;

	glLineWidth(2.0);
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(size + offset, -size + offset, size + offset);
	glVertex3f(-size + offset, -size + offset, size + offset);
	glVertex3f(-size + offset, size + offset, size + offset);
	glVertex3f(size + offset, size + offset, size + offset);
	glEnd();




	r = 0.f;
	g = 1.f;
	b = 0.f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(size + offset, -size + offset, -size + offset);
	glVertex3f(-size + offset, -size + offset, -size + offset);
	glVertex3f(-size + offset, size + offset, -size + offset);
	glVertex3f(size + offset, size + offset, -size + offset);
	glEnd();



	r = 0.f;
	g = 0.f;
	b = 1.f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(size + offset, -size + offset, -size + offset);
	glVertex3f(size + offset, -size + offset, size + offset);
	glVertex3f(size + offset, size + offset, size + offset);
	glVertex3f(size + offset, size + offset, -size + offset);
	glEnd();

	r = 0.99f;
	g = 0.89f;
	b = 0.01f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(-size + offset, -size + offset, -size + offset);
	glVertex3f(-size + offset, -size + offset, size + offset);
	glVertex3f(-size + offset, size + offset, size + offset);
	glVertex3f(-size + offset, size + offset, -size + offset);
	glEnd();

	r = 0.5f;
	g = 0.f;
	b = 0.5f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(-size + offset, size + offset, -size + offset);
	glVertex3f(-size + offset, size + offset, size + offset);
	glVertex3f(size + offset, size + offset, size + offset);
	glVertex3f(size + offset, size + offset, -size + offset);
	glEnd();

	r = 1.f;
	g = 0.4f;
	b = 0.8f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(-size + offset, -size + offset, -size + offset);
	glVertex3f(-size + offset, -size + offset, size + offset);
	glVertex3f(size + offset, -size + offset, size + offset);
	glVertex3f(size + offset, -size + offset, -size + offset);
	glEnd();

	alpha += 0.2;
}

void drawStaticCube() {
	const int type = GL_POLYGON;

	GLfloat r = 1.f;
	GLfloat g = 0.f;
	GLfloat b = 0.f;

	GLfloat size = 0.1f;
	GLfloat offset = -0.5f;

	glLineWidth(2.0);
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(size, -size, size);
	glVertex3f(-size, -size, size);
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);
	glEnd();




	r = 0.f;
	g = 1.f;
	b = 0.f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(size, -size, -size);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, size, -size);
	glVertex3f(size, size, -size);
	glEnd();



	r = 0.f;
	g = 0.f;
	b = 1.f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(size, -size, -size);
	glVertex3f(size, -size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, -size);
	glEnd();

	r = 0.99f;
	g = 0.89f;
	b = 0.01f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, -size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size, size, -size);
	glEnd();

	r = 0.5f;
	g = 0.f;
	b = 0.5f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(-size, size, -size);
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, -size);
	glEnd();

	r = 1.f;
	g = 0.4f;
	b = 0.8f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, size);
	glVertex3f(size, -size, -size);
	glEnd();
}

void display(GLFWwindow* window)
{
	while (!glfwWindowShouldClose(window))
	{
		// Scale to window size
		GLint windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);

		// Draw stuff
		glClearColor(0.7, 1, 1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION_MATRIX);
		glLoadIdentity();
		gluPerspective(50, (double)windowWidth / (double)windowHeight, 0.1, 100);

		glMatrixMode(GL_MODELVIEW_MATRIX);
		glTranslatef(0, 0, -5);

		drawCube();

		// Update Screen
		glfwSwapBuffers(window);

		// Check for any input, or window movement
		glfwPollEvents();
	}
}

int main(int argc, char** argv)
{
	GLFWwindow* window = initWindow(1024, 620);
	if (NULL != window)
	{
		display(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
