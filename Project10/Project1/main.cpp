#include <iostream>

#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include "Dependencies\soil\soil.h" 

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "Dependencies\FMOD\fmod.hpp"

#include "TextLabel.h"
#include "images.h"
#include "ShaderLoader.h"
#include "Constants.h"
#include "Sphere.h"

GLuint program;

GLuint vbo; //global variable 
GLuint vao;
GLuint ebo;
GLuint tex;
GLuint texture2;
GLfloat currentTime;

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
GLfloat LastX = (float)Utility::SCR_WIDTH * 0.5f;
GLfloat LastY = (float)Utility::SCR_HEIGHT * 0.5f;
bool FirstMouse = true;

void MousePassiveMovement(int x, int y);

void Initialize();
void render(void);
void Update();
void CleanUp();

FMOD::System* audioMgr;
FMOD::Sound* fxThump;
FMOD::Sound* bgmTheme;
bool InitFmod();
const bool LoadAudio();

TextLabel* label;
Sphere* pSphere;


int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(Utility::SCR_WIDTH, Utility::SCR_HEIGHT);
	glutCreateWindow("OpenGl First Window");
	glewInit();

	Initialize();

	//register callbacks
	glutDisplayFunc(render);
	glutIdleFunc(Update);
	glutCloseFunc(CleanUp);
	glutMainLoop();
	return 0;
}

void Initialize()
{

	ShaderLoader shader;
	CIMAGELOADER ImageLoader;

	
	glutKeyboardFunc(Keyboard_Down);
	glutKeyboardUpFunc(Keyboard_Up);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(MousePassiveMovement);

	glClearColor(1.0, 0.0, 1.0, 1.0); //clear Magenta

	program = shader.CreateProgram("Vertex.txt", "Fragment.txt");

	pSphere = new Sphere();
	
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	ImageLoader.CreateMipMap("Images/Rayman.png");

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	ImageLoader.CreateMipMap("Images/AwesomeFace.png");


	glEnable(GL_DEPTH_TEST);	// Turns on depth
	glEnable(GL_CULL_FACE);		// Turn on the back face culling
	glCullFace(GL_BACK);		// Cull the Back faces 
	glFrontFace(GL_CW);			// Front face is Clockwise order 

	InitFmod();
	LoadAudio();

	FMOD::Channel* channel;
	audioMgr->playSound(bgmTheme, 0, false, &channel);

	label = new TextLabel("Sample Text", "fonts/arial.ttf", glm::vec2(100.0f, 100.0f));
	label->SetScale(1.0f);
	label->SetColor(glm::vec3(1.0f, 1.0f, 0.2f));

}

void render(void)
{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	glUseProgram(program);
	GLfloat ambientStrength = 0.05f;
	GLint ambientStrengthLoc = glGetUniformLocation(program, "ambientStrength");
	glUniform1f(ambientStrengthLoc, ambientStrength);

	glm::vec3 ambientColor = glm::vec3(1.0f, 1.0f, 1.0f);
	GLint ambientColorLoc = glGetUniformLocation(program, "ambientColor");
	glUniform3fv(ambientColorLoc, 1, glm::value_ptr(ambientColor));

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	GLint lightColorLoc = glGetUniformLocation(program, "lightColor");
	glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

	glm::vec3 lightPos = glm::vec3(-5.0f, 5.0f, 0.5f);
	GLint lightPosLoc = glGetUniformLocation(program, "lightPos");
	glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));

	GLfloat lightSpecStrength = 1.0f;
	GLint lightSpecStrengthLoc = glGetUniformLocation(program, "lightSpecStrength");
	glUniform1f(lightSpecStrengthLoc, lightSpecStrength);

	GLfloat shininess = 32.0f;
	GLint shininessLoc = glGetUniformLocation(program, "shininess");
	glUniform1f(shininessLoc, shininess);

	currentTime = (GLfloat)glutGet(GLUT_ELAPSED_TIME);// Get current time. 
	currentTime = currentTime / 1000;  // Convert millisecond to seconds
	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);// set value
	glUseProgram(0);



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear
	glClearColor(1.0, 0.0, 1.0, 1.0);					//clear Magenta

	

	GLfloat camY = 3.0f;
	GLfloat radius = 4.0f;
	GLfloat camX = sin(currentTime) * radius; //Rotating the camera around
	GLfloat camZ = cos(currentTime) * radius; //The 3D object

	projection = glm::perspective(45.0f, (GLfloat)Utility::SCR_WIDTH / (GLfloat)Utility::SCR_HEIGHT, 0.1f, 100.0f);
	model = glm::mat4();
	view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 MVP = projection * view * model;

	glUseProgram(program);
	GLint MVPLoc = glGetUniformLocation(program, "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	GLint modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));
	GLint normalMatrixLoc = glGetUniformLocation(program, "normalMatrix");
	glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	glm::vec3 camPos = glm::vec3(camX, camY, camZ);
	GLint camPosLoc = glGetUniformLocation(program, "camPos");
	glUniform3fv(camPosLoc, 1, glm::value_ptr(camPos));
	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(glGetUniformLocation(program, "tex"), 0); 
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(program, "texture2"), 1);

	pSphere->Render();
	glUseProgram(0);

	label->Render();

	glutSwapBuffers();
}

void Update() 
{	// Update game information.
	glutPostRedisplay(); //render function is called

	glClearColor(abs(cos(currentTime)), abs(sin(currentTime)), 1.0, 1.0); //clear Magenta
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

void CleanUp()
{
	//All delete for pointers
	delete pSphere;
	pSphere = 0;
}