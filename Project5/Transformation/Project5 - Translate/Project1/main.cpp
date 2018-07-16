#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include "Dependencies\soil\soil.h" 

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "images.h"
#include <iostream>

#include "ShaderLoader.h"

GLuint program;

GLuint vbo; //global variable 
GLuint vao;
GLuint ebo;
GLuint tex;
GLuint texture2;

GLfloat vertices[] = 
{	// Positions			// Colors				//Texture Coords
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,  // Top Left
	0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 0.0f,  // Top Right
	0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 0.0f,		1.0f, 1.0f, // Bottom Right
	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, // Bottom Left 
};

GLuint indices[] =
{	//position          
	0, 1, 2,	//First Triangle
	0, 2, 3		// Second Triangle
};

void render(void);
void Update();

int main(int argc, char **argv) {

	ShaderLoader shader;
	CIMAGELOADER ImageLoader;

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

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	int width, height;
	unsigned char* image = ImageLoader.GetImage("Images/Rayman.jpg", width, height);
	ImageLoader.CreateMipMap(width, height, image);

	glVertexAttribPointer(
		0, // Layout location on vertex shader 
		3, // 3 float components (eg position) 
		GL_FLOAT, // Type of data 
		GL_FALSE, // Data normalized? 
		8 * sizeof(GLfloat), // Stride of the entire single vertex 
		(GLvoid*)0); // Offset 
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1, // Layout location on vertex shader 
		3, // 3 float components (eg position) 
		GL_FLOAT, // Type of data 
		GL_FALSE, // Data normalized? 
		8 * sizeof(GLfloat), // Stride of the entire single vertex 
		(GLvoid*)(3 * sizeof(GLfloat))); // Offset 
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2, // Layout location on vertex shader 
		2, // 3 float components (eg position) 
		GL_FLOAT, // Type of data 
		GL_FALSE, // Data normalized? 
		8 * sizeof(GLfloat), // Stride of the entire single vertex 
		(GLvoid*)(6 * sizeof(GLfloat))); // Offset 
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	int width2, height2;
	unsigned char* image2 = ImageLoader.GetImage("Images/AwesomeFace.png", width2, height2);
	ImageLoader.CreateMipMap(width2, height2, image2);

	glCullFace(GL_BACK); // Cull the Back faces 
	glFrontFace(GL_CW); // Front face is Clockwise order 
	glEnable(GL_CULL_FACE); // Turn on the back face culling

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

	glm::vec3 objPosition = glm::vec3(0.5f, -0.5f, 0.0f);
	glm::mat4 translate = glm::translate(glm::mat4(), objPosition);

	GLuint transformLoc = glGetUniformLocation(program, "translate");
	glUniformMatrix4fv(
		transformLoc,				//transformation location
		1,							//How many Matrix
		GL_FALSE,					//Normalizes
		glm::value_ptr(translate));	//Point to memory

	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glUniform1i(glGetUniformLocation(program, "tex"), 0); 
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glUniform1i(glGetUniformLocation(program, "texture2"), 1);

	glBindVertexArray(vao); // Bind VAO

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0); // Unbind VAO

	glutSwapBuffers();
}

void Update() 
{	// Update game information. 
	glutPostRedisplay(); //render function is called 
}