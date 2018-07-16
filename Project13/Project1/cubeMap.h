#pragma once

#ifndef __CUBEMAP_H__
#define __CUBEMAP_H__

#include <vector>

#include "camera.h"
#include "ConstantsShapes.h"
#include "images.h"

class CCubeMap
{
public:
	CCubeMap() {};
	CCubeMap(GLuint& _program, std::vector<std::string> _vecImagePath);
	//glm::mat4 _CameraProjection, glm::mat4 _CameraView

	void Render();

	GLuint GetTextureID();

private:
	GLuint program;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint Images;

	std::vector<GLuint> TextureID;
};

#endif // _CUBEMAP_H__