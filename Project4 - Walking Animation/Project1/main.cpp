#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include "Dependencies\soil\soil.h" 
#include "images.h"
#include <iostream>

#include "ShaderLoader.h"

GLuint program;

GLuint vbo; //global variable 
GLuint vao;
GLuint ebo;
GLuint tex;
GLuint texture2;
GLuint texture3;
GLuint texture4;
GLuint texture5;
GLuint texture6;
GLuint texture7;
GLuint texture8;
GLfloat g_iImage = -1.0f;
GLfloat g_iImageSpeed = 0.04f;

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
	unsigned char* image = ImageLoader.GetImage("Images/Capguy_Walk1.png", width, height);
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
	unsigned char* image2 = ImageLoader.GetImage("Images/Capguy_Walk2.png", width2, height2);
	ImageLoader.CreateMipMap(width2, height2, image2);

	glGenTextures(2, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	int width3, height3;
	unsigned char* image3 = ImageLoader.GetImage("Images/Capguy_Walk3.png", width3, height3);
	ImageLoader.CreateMipMap(width3, height3, image3);

	glGenTextures(3, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	int width4, height4;
	unsigned char* image4 = ImageLoader.GetImage("Images/Capguy_Walk4.png", width4, height4);
	ImageLoader.CreateMipMap(width4, height4, image4);

	glGenTextures(4, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5);
	int width5, height5;
	unsigned char* image5 = ImageLoader.GetImage("Images/Capguy_Walk5.png", width5, height5);
	ImageLoader.CreateMipMap(width5, height5, image5);

	glGenTextures(5, &texture6);
	glBindTexture(GL_TEXTURE_2D, texture6);
	int width6, height6;
	unsigned char* image6 = ImageLoader.GetImage("Images/Capguy_Walk6.png", width6, height6);
	ImageLoader.CreateMipMap(width2, height2, image6);

	glGenTextures(6, &texture7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	int width7, height7;
	unsigned char* image7 = ImageLoader.GetImage("Images/Capguy_Walk7.png", width7, height7);
	ImageLoader.CreateMipMap(width7, height7, image7);

	glGenTextures(7, &texture8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	int width8, height8;
	unsigned char* image8 = ImageLoader.GetImage("Images/Capguy_Walk8.png", width8, height8);
	ImageLoader.CreateMipMap(width8, height8, image8);

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

	if (-0.75f > g_iImage)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
		glUniform1i(glGetUniformLocation(program, "tex"), 0);
		g_iImage += g_iImageSpeed;
	}
	else if (-0.5f > g_iImage)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glUniform1i(glGetUniformLocation(program, "tex"), 1);
		g_iImage += g_iImageSpeed;
	}
	else if (-0.25f > g_iImage)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texture3);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glUniform1i(glGetUniformLocation(program, "tex"), 2);
		g_iImage += g_iImageSpeed;
	}
	else if (0.0f > g_iImage)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, texture4);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glUniform1i(glGetUniformLocation(program, "tex"), 3);
		g_iImage += g_iImageSpeed;
	}
	else if (0.25f > g_iImage)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, texture5);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glUniform1i(glGetUniformLocation(program, "tex"), 4);
		g_iImage += g_iImageSpeed;
	}
	else if (0.5f > g_iImage)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, texture6);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glUniform1i(glGetUniformLocation(program, "tex"), 5);
		g_iImage += g_iImageSpeed;
	}
	else if (0.75f > g_iImage)
	{
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, texture7);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glUniform1i(glGetUniformLocation(program, "tex"), 6);
		g_iImage += g_iImageSpeed;
	}
	else
	{
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, texture8);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glUniform1i(glGetUniformLocation(program, "tex"), 7);
		g_iImage = -1.0f;
	}

	glClear(GL_COLOR_BUFFER_BIT); //clear
	glClearColor(1.0, 0.0, 1.0, 1.0); //clear Magenta

	glUseProgram(program);

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