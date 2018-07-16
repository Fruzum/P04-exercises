#pragma once

#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include "Dependencies\soil\soil.h" 

class CIMAGELOADER
{
public:
	CIMAGELOADER() {};
	~CIMAGELOADER() {};
	void CreateMipMap(const char* _fileName);
};