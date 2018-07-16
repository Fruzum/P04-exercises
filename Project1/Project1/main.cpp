#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include <iostream>


void render(void);

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGl First Window");

	glClearColor(1.0, 0.0, 1.0, 1.0); //clear Magenta

	//register callbacks
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 0.0, 1.0, 1.0); //clear Magenta

	glutSwapBuffers();
}