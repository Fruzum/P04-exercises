#pragma once

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include "Dependencies\soil\soil.h"  

namespace Utility
{
	const unsigned int SCR_WIDTH = 1080;
	const unsigned int SCR_HEIGHT = 800;

	const GLfloat vertices[] =
	{	// Positions			// Normals				//Texture Coords
		-1.0f,  1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,  // Top Left
		1.0f,  1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f,  // Top Right
		1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Bottom Right
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, // Bottom Left 
	};

	const GLuint indices[] =
	{	//position          
		0, 1, 2,	//First Triangle
		0, 2, 3		// Second Triangle
	};

	const GLfloat verticesPyramid[] =
	{	// Positions			// Colors				//Texture Coords
		-1.0f, 0.0f, -1.0f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		//0		// Base
		1.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,		//1
		1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		//2
		-1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,		//3
		-1.0f, 0.0f, -1.0f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		//4		// Side 1
		-1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		//5
		-1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f,		//6		// Side 2
		1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,		1.0f, 1.0f,		//7
		1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,		//8		// Side 3
		1.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,		//9
		1.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 1.0f,		//10	// Side 4
		-1.0f, 0.0f, -1.0f,		1.0f, 1.0f, 0.0f,		1.0f, 1.0f,		//11

		0.0f, 1.0f, 0.0f,		0.0f, 1.0f, 1.0f,		0.5, 0.0f,		//12	//Top point
	};
	const GLuint indicesPyramid[] =
	{	//position          
		4,  12, 5,	//Side 1
		6,  12, 7,	//Side 2
		8,  12, 9,	//Side 3
		10, 12, 11,	//Side 4

		3, 2, 1,	//Bottom triangle 1
		3, 1, 0,	//Bottom triangle 2
	};


	const GLfloat verticesCube[] =
	{	// Positions			// Colors				//Texture Coords
		-1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,			//Front Face
		1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		0.0f, 1.0f,

		1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 0.0f,		0.0f, 0.0f,			//Right Face
		1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f,

		1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f,			//Back Face
		-1.0f, 1.0f, -1.0f,		1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,		1.0f, 1.0f, 
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,			//Left Face
		-1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,		0.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,			//Top Face
		1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,

		-1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,			//Bottom Face
		1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 1.0f,		1.0f, 0.0f, 
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f, 
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
	};

	const GLuint indicesCube[] =
	{	//position          
		0, 1, 2,		//Front Face
		0, 2, 3,
		12, 13, 14,		//Left Face
		12, 14, 15,
		4, 5, 6,		//Right Face
		4, 6, 7,
		16, 17, 18,		//Top Face
		16, 18, 19,
		8, 9, 10,		//Back face
		8, 10, 11, 
		20, 21, 22,		//Bottom Face
		20, 22, 23,
	};

}
#endif // __CONSTANTS_H__


