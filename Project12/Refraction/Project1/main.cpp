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
#include "manager.h"

GLuint program;

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
bool FirstMouse = true;

void Initialize();
void render(void);
void Update();
void CleanUp();

TextLabel* label;
Sphere* pSphere;

CManager* m_pManager;

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
	m_pManager = CManager::GetInstance();
	m_pManager->Initialise();
	
	glutKeyboardFunc(Keyboard_Down);
	glutKeyboardUpFunc(Keyboard_Up);
	glutMouseFunc(Mouse);

	glClearColor(1.0, 0.0, 1.0, 1.0); //clear Magenta

	//program = shader.CreateProgram("Vertex.txt", "Fragment.txt");
	
	glEnable(GL_DEPTH_TEST);	// Turns on depth
	glEnable(GL_CULL_FACE);		// Turn on the back face culling
	glCullFace(GL_BACK);		// Cull the Back faces 
	glFrontFace(GL_CW);			// Front face is Clockwise order 

}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear
	glClearColor(1.0, 0.0, 1.0, 1.0);					//clear Magenta

	m_pManager->Render();
	
	glutSwapBuffers();
}

void Update() 
{	// Update game information.
	glutPostRedisplay(); //render function is called

	glClearColor(abs(cos(currentTime)), abs(sin(currentTime)), 1.0, 1.0); //clear Magenta
}

void CleanUp()
{
	//All delete for pointers
	
}