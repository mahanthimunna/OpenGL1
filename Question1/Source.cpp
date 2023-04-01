#include<GL/glut.h>
#include<stdlib.h>
#include<time.h>

GLfloat vertices[] = {
	-1.0f,-0.5f,
	1.0f,-0.5f,
	0.0f,0.5f
};

GLfloat currentColor[] = { 1.0f,1.0f,1.0f,1.0f };

int iterations = 5;

void drawTriangle(GLfloat* vertices)
{
	glBegin(GL_TRIANGLES);
	glColor4fv(currentColor);
	glVertex2fv(&vertices[0]);
	glVertex2fv(&vertices[2]);
	glVertex2fv(&vertices[4]);
	glEnd();
}

void sierpinski(GLfloat* vertices, int iteration)
{
	if (iteration == 0)
	{
		drawTriangle(vertices);
		return;
	}
	GLfloat v1[6] = {
		(vertices[0] + vertices[2]) / 2.0f,
		(vertices[1] + vertices[3]) / 2.0f,
		vertices[0],vertices[1],
		vertices[2],vertices[3]
	};
	GLfloat v2[6] = {
		(vertices[2] + vertices[4]) / 2.0f,
		(vertices[3] + vertices[5]) / 2.0f,
		vertices[2],vertices[3],
		vertices[4],vertices[5]
	};
	GLfloat v3[6] = {
		(vertices[4] + vertices[0]) / 2.0f,
		(vertices[5] + vertices[1]) / 2.0f,
		vertices[4],vertices[5],
		vertices[0],vertices[1]
	};
	sierpinski(v1, iteration - 1);
	sierpinski(v2, iteration - 1);
	sierpinski(v3, iteration - 1);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	sierpinski(vertices, iterations);

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '+':
		iterations++;
		break;
	case '-':
		iterations--;
		if (iterations < 0)iterations = 0;
		break;
	case 'c':
		currentColor[0] = (GLfloat)rand() / RAND_MAX;
		currentColor[1] = (GLfloat)rand() / RAND_MAX;
		currentColor[2] = (GLfloat)rand() / RAND_MAX;
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Sierpinski Gasket");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}