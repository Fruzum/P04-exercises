#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include <iostream>

#include "ShaderLoader.h"

GLuint program;
GLuint program2;
GLuint program3;

void render(void);

int main(int argc, char **argv) {

	ShaderLoader shader;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGl First Window");
	glewInit();

	glClearColor(1.0, 0.0, 1.0, 1.0); //clear Magenta

	program = shader.CreateProgram("Vertex.txt", "Fragment.txt");
	program2 = shader.CreateProgram("Vertex.txt", "Fragment.txt");
	program3 = shader.CreateProgram("Vertex.txt", "Fragment.txt");

	//register callbacks
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //clear
	glClearColor(1.0, 0.0, 1.0, 1.0); //clear Magenta

	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
}