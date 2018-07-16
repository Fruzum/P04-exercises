#pragma once

#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include "Dependencies\soil\soil.h" 

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "Constants.h"

class CCamera
{
public:
	static CCamera* GetCamera();
	void Initialize(glm::vec3 _cameraFront, glm::vec3 _cameraUp);
	void render(GLuint _program, GLfloat _CurrentTime, glm::mat4& model);

	glm::mat4 GetModel() const;
	glm::mat4 GetView() const;
	glm::mat4 GetProjection() const;

	GLfloat GetCamX() const;
	GLfloat GetCamY() const;
	GLfloat GetCamZ() const;

	void DeleteCamera();

protected:
	CCamera() {};
	~CCamera() {};

private:
	CCamera(CCamera const&);
	CCamera& operator=(CCamera const&);

	static CCamera* m_pCamera;
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	GLfloat m_fCamX;
	GLfloat m_fCamY;
	GLfloat m_fCamZ;
};