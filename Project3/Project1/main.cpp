#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include <iostream>

#include "ShaderLoader.h"

GLuint program;

GLuint vbo; //global variable 
GLuint vao;

GLfloat vertices[] = 
{	//position			//color             
	-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	// Left 
	0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	// Right 
	0.0f,  0.5f, 0.0f,	0.0f, 0.0f, 1.0f	// Top  
};

void render(void);
void Update();

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

	glGenVertexArrays(1, &vao); // Add “GLuint vao;” to global variables 
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0, // Layout location on vertex shader 
		3, // 3 float components (eg position) 
		GL_FLOAT, // Type of data 
		GL_FALSE, // Data normalized? 
		6 * sizeof(GLfloat), // Stride of the entire single vertex 
		(GLvoid*)0); // Offset 
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1, // Layout location on vertex shader 
		3, // 3 float components (eg position) 
		GL_FLOAT, // Type of data 
		GL_FALSE, // Data normalized? 
		6 * sizeof(GLfloat), // Stride of the entire single vertex 
		(GLvoid*)(3 * sizeof(GLfloat))); // Offset 
	glEnableVertexAttribArray(1);


	//register callbacks
	glutDisplayFunc(render);
	glutIdleFunc(Update);
	glutMainLoop();
	return 0;
}

void render(void)
{
	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME);// Get current time. 
	currentTime = currentTime / 1000;  // Convert millisecond to seconds
	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);// set value

	glClear(GL_COLOR_BUFFER_BIT); //clear
	glClearColor(1.0, 0.0, 1.0, 1.0); //clear Magenta

	glUseProgram(program);
	glBindVertexArray(vao); // Bind VAO

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0); // Unbind VAO

	glutSwapBuffers();
}

void Update() 
{	// Update game information. 
	glutPostRedisplay(); //render function is called 
}