#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

GLfloat a = 0.f, b = 0.f, c = 0.f;
GLfloat x = 0.f, y = 0.f, z = 0.f;
GLboolean  fl = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action,
	int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GL_TRUE);

		if (key == GLFW_KEY_ENTER || key == GLFW_KEY_SPACE)
			fl = !fl;
	}

	if (action = GLFW_REPEAT) {
		if (key == GLFW_KEY_UP) {
			a -= 3.f;
		}
		if (key == GLFW_KEY_DOWN) {
			a += 3.f;
		}
		if (key == GLFW_KEY_RIGHT) {
			b -= 3.f;
		}

		if (key == GLFW_KEY_LEFT) {
			b += 3.f;
		}

		if (key == GLFW_KEY_KP_1) {
			c -= 3.f;
		}

		if (key == GLFW_KEY_RIGHT_SHIFT) {
			c += 3.f;
		}

		//////////////

		if (key == GLFW_KEY_A) {
			x -= 3.f;
		}
		if (key == GLFW_KEY_D) {
			x += 3.f;
		}
		if (key == GLFW_KEY_S) {
			y -= 3.f;
		}

		if (key == GLFW_KEY_W) {
			y += 3.f;
		}

		if (key == GLFW_KEY_Z) {
			z -= 3.f;
		}

		if (key == GLFW_KEY_Q) {
			z += 3.f;
		}

	}
}

GLfloat project[] = { 
	1.f, 0.f, 0.f, 0.5f, 
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.5f, 
	0.f, 0.f, 0.f, 1.f };

GLFWwindow* initWindow(const int resX, const int resY) {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);  

	GLFWwindow* window = glfwCreateWindow(resX, resY, "TEST", NULL, NULL);

	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glEnable(GL_DEPTH_TEST);  // Depth Testing
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	return window;
}

void drawCube(GLFWwindow* window) {
	static float alpha = 0;

	glTranslatef(x, y, z);

	glRotatef(a, 1, 0, 0);
	glRotatef(b, 0, 1, 0);
	glRotatef(c, 0, 0, 1);

	glTranslatef(-x, -y, -z);

	GLfloat r = 1.f;
	GLfloat g = 0.f;
	GLfloat b = 0.f;

	const int type = (fl ? GL_POLYGON : GL_LINE_LOOP);

	GLfloat size = 40.f;				// 1/2 length of one side
	GLfloat offset = 0.f;				// for debug

	glLineWidth(2.0);
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(x + size + offset,  y + -size + offset, z + size);
	glVertex3f(x + -size + offset, y + -size + offset, z + size);
	glVertex3f(x + -size + offset, y + size + offset,  z + size);
	glVertex3f(x + size + offset,  y + size + offset,  z + size);
	glEnd();

	r = 0.f;
	g = 1.f;
	b = 0.f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(x + size + offset,  y + -size + offset, z + -size);
	glVertex3f(x + -size + offset, y + -size + offset, z + -size);
	glVertex3f(x + -size + offset, y + size + offset,  z + -size);
	glVertex3f(x + size + offset,  y + size + offset,  z + -size);
	glEnd();

	r = 0.f;
	g = 0.f;
	b = 1.f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(x + size + offset, y + -size + offset, z + -size);
	glVertex3f(x + size + offset, y + -size + offset, z + size);
	glVertex3f(x + size + offset, y + size + offset,  z + size);
	glVertex3f(x + size + offset, y + size + offset,  z + -size);
	glEnd();

	r = 0.99f;
	g = 0.89f;
	b = 0.01f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(x + -size + offset, y + -size + offset, z + -size);
	glVertex3f(x + -size + offset, y + -size + offset, z + size);
	glVertex3f(x + -size + offset, y + size + offset,  z + size);
	glVertex3f(x + -size + offset, y + size + offset,  z + -size);
	glEnd();

	r = 0.5f;
	g = 0.f;
	b = 0.5f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(x + -size + offset, y + size + offset, z + -size);
	glVertex3f(x + -size + offset, y + size + offset, z + size);
	glVertex3f(x + size  + offset, y + size + offset, z + size);
	glVertex3f(x + size  + offset, y + size + offset, z + -size);
	glEnd();

	r = 1.f;
	g = 0.4f;
	b = 0.8f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(x + -size + offset, y + -size + offset, z + -size);
	glVertex3f(x + -size + offset, y + -size + offset, z + size);
	glVertex3f(x + size  + offset, y + -size + offset, z + size);
	glVertex3f(x + size  + offset, y + -size + offset, z + -size);
	glEnd();

}

// =======================

void drawStaticCube(GLFWwindow* window) {
	const int type = GL_POLYGON;

	GLint windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	GLfloat r = 1.f;
	GLfloat g = 0.f;
	GLfloat b = 0.f;

	GLfloat size = 10.f;
	GLfloat offsetX = - windowWidth / 3 + 3 * size;
	GLfloat offsetY = -windowHeight / 3 + 3 * size;


	glLineWidth(2.0);
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(size + offsetX, -size + offsetY, size);
	glVertex3f(-size + offsetX, -size + offsetY, size);
	glVertex3f(-size + offsetX, size + offsetY, size);
	glVertex3f(size + offsetX, size + offsetY, size);
	glEnd();

	r = 0.f;
	g = 1.f;
	b = 0.f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(size + offsetX, -size + offsetY, -size);
	glVertex3f(-size + offsetX, -size + offsetY, -size);
	glVertex3f(-size + offsetX, size + offsetY, -size);
	glVertex3f(size + offsetX, size + offsetY, -size);
	glEnd();

	r = 0.f;
	g = 0.f;
	b = 1.f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(size + offsetX, -size + offsetY, -size);
	glVertex3f(size + offsetX, -size + offsetY, size);
	glVertex3f(size + offsetX, size + offsetY, size);
	glVertex3f(size + offsetX, size + offsetY, -size);
	glEnd();

	r = 0.99f;
	g = 0.89f;
	b = 0.01f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(-size + offsetX, -size + offsetY, -size);
	glVertex3f(-size + offsetX, -size + offsetY, size);
	glVertex3f(-size + offsetX, size + offsetY, size);
	glVertex3f(-size + offsetX, size + offsetY, -size);
	glEnd();

	r = 0.5f;
	g = 0.f;
	b = 0.5f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(-size + offsetX, size + offsetY, -size);
	glVertex3f(-size + offsetX, size + offsetY, size);
	glVertex3f(size + offsetX, size + offsetY, size);
	glVertex3f(size + offsetX, size + offsetY, -size);
	glEnd();

	r = 1.f;
	g = 0.4f;
	b = 0.8f;
	glBegin(type);
	glColor3f(r, g, b);
	glVertex3f(-size + offsetX, -size + offsetY, -size);
	glVertex3f(-size + offsetX, -size + offsetY, size);
	glVertex3f(size + offsetX, -size + offsetY, size);
	glVertex3f(size + offsetX, -size + offsetY, -size);
	glEnd();
}

void display(GLFWwindow* window) {
	while (!glfwWindowShouldClose(window)) {
		GLint windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);

		glClearColor(0.7, 1, 1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		
		glLoadIdentity();

		glLoadMatrixf(project);

		glOrtho(-windowWidth / 2, windowWidth / 2, -windowHeight / 2,
			windowHeight / 2, -(windowWidth + windowHeight) / 4, (windowWidth + windowHeight) / 4);

		glMatrixMode(GL_MODELVIEW_MATRIX);

		drawStaticCube(window);
		drawCube(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main(int argc, char** argv) {
	GLFWwindow* window = initWindow(800, 600);
	if (NULL != window) {
		display(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
