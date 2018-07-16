#include "camera.h"

CCamera* CCamera::m_pCamera = nullptr;

CCamera* CCamera::GetCamera()
{
	if (nullptr == m_pCamera)
	{
		m_pCamera = new CCamera();
	}
	return(m_pCamera);
}

void CCamera::Initialize(glm::vec3 _cameraFront, glm::vec3 _cameraUp)
{
	m_fCamX = 0.0f;
	m_fCamY = 3.0f;
	m_fCamZ = 0.0f;
	m_cameraPos = glm::vec3(m_fCamX, m_fCamX, m_fCamX);
	m_cameraFront = _cameraFront;// -m_cameraPos;
	m_cameraUp = _cameraUp;
}

void CCamera::render(GLuint _program, GLfloat _CurrentTime, glm::mat4& _model)
{
	glUseProgram(_program);

	GLfloat radius = 4.0f;
	m_fCamX = sin(_CurrentTime) * radius; //Rotating the camera around
	m_fCamY = 3.0f;
	m_fCamZ = cos(_CurrentTime) * radius; //The 3D object

	view = glm::lookAt(glm::vec3(m_fCamX, m_fCamY, m_fCamZ), glm::vec3(0.0f, 0.0f, 0.0f), m_cameraUp);
	projection = glm::perspective(45.0f, (GLfloat)Utility::SCR_WIDTH / (GLfloat)Utility::SCR_HEIGHT, 0.1f, 10000.0f);

	glm::mat4 MVP = projection * view * _model;
	GLint MVPLoc = glGetUniformLocation(_program, "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	glUseProgram(0);
}

glm::mat4 CCamera::GetModel() const
{
	return(model);
}
glm::mat4 CCamera::GetView() const
{
	return(view);
}
glm::mat4 CCamera::GetProjection() const
{
	return(projection);
}

GLfloat CCamera::GetCamX() const
{
	return(m_fCamX);
}
GLfloat CCamera::GetCamY() const
{
	return(m_fCamY);
}
GLfloat CCamera::GetCamZ() const
{
	return(m_fCamZ);
}

void CCamera::DeleteCamera()
{
	delete m_pCamera;
	m_pCamera = 0;
}