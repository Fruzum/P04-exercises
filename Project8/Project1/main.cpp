#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include "Dependencies\soil\soil.h" 

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "Dependencies\FMOD\fmod.hpp"

#include "TextLabel.h"

#include "images.h"
#include <iostream>

#include "ShaderLoader.h"

GLuint program;

GLuint vbo; //global variable 
GLuint vao;
GLuint ebo;
GLuint tex;
GLuint texture2;
GLfloat currentTime;

int g_iScreenWidth = 800;
int g_iScreenHeight = 600;

enum InputState
{
	INPUT_FIRST_RELEASE,
	INPUT_RELEASED,
	INPUT_FIRST_PRESS,
	INPUT_HOLD,
};
unsigned char KeyState[255];
void Keyboard_Down(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_HOLD;
}
void Keyboard_Up(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_RELEASED;
}

enum InputMouse
{
	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT,
};
unsigned char MouseState[3];
void Mouse(int button, int glutState, int x, int y)
{
	if (button < 3)
	{
		MouseState[button] = (glutState == GLUT_DOWN) ? INPUT_HOLD : INPUT_RELEASED;
	}
}
GLfloat MouseSensitivity = 0.30f;
GLfloat Yaw = 0.0f;
GLfloat Pitch = 0.0f;
GLfloat LastX = (float)g_iScreenWidth * 0.5f;
GLfloat LastY = (float)g_iScreenHeight * 0.5f;
bool FirstMouse = true;

void MousePassiveMovement(int x, int y);

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

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float cameraSpeed = 0.25f;

FMOD::System* audioMgr;
FMOD::Sound* fxThump;
FMOD::Sound* bgmTheme;
bool InitFmod();
const bool LoadAudio();

TextLabel* label;

int main(int argc, char **argv) {

	ShaderLoader shader;
	CIMAGELOADER ImageLoader;


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(g_iScreenWidth, g_iScreenHeight);
	glutCreateWindow("OpenGl First Window");
	glewInit();

	glutKeyboardFunc(Keyboard_Down); 
	glutKeyboardUpFunc(Keyboard_Up);
	glutMouseFunc(Mouse); 
	glutPassiveMotionFunc(MousePassiveMovement);

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


	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	int width, height;
	unsigned char* image = ImageLoader.GetImage("Images/Rayman.jpg", width, height);
	ImageLoader.CreateMipMap(width, height, image);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	int width2, height2;
	unsigned char* image2 = ImageLoader.GetImage("Images/AwesomeFace.png", width2, height2);
	ImageLoader.CreateMipMap(width2, height2, image2);

	glCullFace(GL_BACK); // Cull the Back faces 
	glFrontFace(GL_CW); // Front face is Clockwise order 
	//glEnable(GL_CULL_FACE); // Turn on the back face culling

	InitFmod();
	LoadAudio();

	FMOD::Channel* channel;
	audioMgr->playSound(bgmTheme, 0, false, &channel);

	label = new TextLabel("Sample Text", "fonts/arial.ttf", glm::vec2(100.0f, 100.0f));
	label->SetScale(1.0f);
	label->SetColor(glm::vec3(1.0f, 1.0f, 0.2f));

	//register callbacks
	glutDisplayFunc(render);
	glutIdleFunc(Update);
	glutMainLoop();
	return 0;
}

void render(void)
{


	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;


	currentTime = glutGet(GLUT_ELAPSED_TIME);// Get current time. 
	currentTime = currentTime / 1000;  // Convert millisecond to seconds
	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);// set value

	glClear(GL_COLOR_BUFFER_BIT); //clear
	glClearColor(1.0, 0.0, 1.0, 1.0); //clear Magenta

	
	
	glUseProgram(program); 

	//Translation
	glm::vec3 objPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 world = glm::translate(glm::mat4(), objPosition);
	GLuint worldLoc = glGetUniformLocation(program, "world");
	glUniformMatrix4fv(
		worldLoc,					//transformation location
		1,							//How many Matrix
		GL_FALSE,					//Normalizes
		glm::value_ptr(world));		//Point to memory

	model = glm::rotate(glm::mat4(), 0.0f/* -45.0f * currentTime / 100*/, glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	projection = glm::perspective(45.0f, (GLfloat)g_iScreenWidth / (GLfloat)g_iScreenHeight, 0.1f, 100.0f);

	glm::mat4 MVP = projection * view * model;
	GLint MVPLoc = glGetUniformLocation(program, "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));


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
	glUseProgram(0);

	label->Render();

	glutSwapBuffers();
}

void Update() 
{	// Update game information.
	glutPostRedisplay(); //render function is called

	glClearColor(abs(cos(currentTime)), abs(sin(currentTime)), 1.0, 1.0); //clear Magenta

	if (KeyState[(unsigned char) 'w'] == INPUT_HOLD)
	{
		cameraPos += cameraFront * cameraSpeed;
	}
	if (KeyState[(unsigned char) 's'] == INPUT_HOLD)
	{
		cameraPos -= cameraFront * cameraSpeed;
	}
	if (KeyState[(unsigned char) 'a'] == INPUT_HOLD)
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (KeyState[(unsigned char) 'd'] == INPUT_HOLD)
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
}

void MousePassiveMovement(int x, int y)
{
	//if (FirstMouse == true)
	//{
	//	LastX = x;
	//	LastY = y;
	//	FirstMouse = false;
	//}
	//GLfloat xOffset = x - LastX;
	//GLfloat yOffset = y - LastY;
	//LastX = x;
	//LastY = y;

	//xOffset *= MouseSensitivity;
	//yOffset *= MouseSensitivity;
	//Yaw -= xOffset;
	//Pitch -= yOffset;

	////Clamp 'Pitch' so screen doesn't flip
	//if (Pitch > 89.0f)
	//{
	//	Pitch = 89.0f;
	//}
	//if (Pitch < -89.0f)
	//{
	//	Pitch = -89.0f;
	//}

	//glm::vec3 frontVector(-cos(glm::radians(Pitch))*sin(glm::radians(Yaw)), sin(glm::radians(Pitch)), -cos(glm::radians(Pitch)) * cos(glm::radians(Yaw))); 
	//cameraFront = glm::normalize(frontVector);

}


bool InitFmod()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&audioMgr);
	if (result != FMOD_OK)
	{
		return (false);
	}

	result = audioMgr->init(50, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		return (false);
	}
	return (true);
}


const bool LoadAudio()
{
	FMOD_RESULT result;
	result = audioMgr->createSound("Audio/Thump.wav", FMOD_DEFAULT, 0, &fxThump);
	result = audioMgr->createSound("Audio/Background.mp3", FMOD_DEFAULT, 0, &bgmTheme);
	bgmTheme->setMode(FMOD_LOOP_NORMAL);

	return (true);
}