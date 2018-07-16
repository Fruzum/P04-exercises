#include "entity.h"

CEntity::CEntity()
{
	m_fTranslateX = 0.0f;
	m_fTranslateY = 0.0f;
	m_fTranslateZ = 0.0f;

	fGradualchange = 0.0f;

	m_fScaleX = 1.0f;
	m_fScaleY = 1.0f;
	m_fScaleZ = 1.0f;

	srand((unsigned)time(NULL));

	m_iDirectionCooldown = 0;
	m_bRender = false;

	m_iActiveTexture = 0;
}

void CEntity::BindImage(Shape _ThisShape, GLuint& _program, GLuint& _textureName, const char* _fileName, int _iTranslationMove, int _iRotationMove, int _iScaleMove)
{
	CIMAGELOADER Images;

	/* Initializes the movement */
	m_pMovementType = CMoveTypes::GetInstance();
	m_iTranslationOption = _iTranslationMove;
	m_iRotationOption = _iRotationMove;
	m_iScaleOption = _iScaleMove;

	program = _program;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	switch (_ThisShape)
	{
		//Temp
	case Background:
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(Shapes::verticesCube), Shapes::verticesCube, GL_STATIC_DRAW);
		break;
	}
	case Square:
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(Shapes::verticesCube), Shapes::verticesCube, GL_STATIC_DRAW);
		break;
	}
	}

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

	switch (_ThisShape)
	{
	case Background:
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Shapes::indicesSquare), Shapes::indicesSquare, GL_STATIC_DRAW);
		break;
	}
	case Square:
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Shapes::indicesSquare), Shapes::indicesSquare, GL_STATIC_DRAW);
		break;
	}
	}

	glGenTextures(1, &_textureName);
	glBindTexture(GL_TEXTURE_2D, _textureName);
	Images.CreateMipMap(_fileName); 
}


void CEntity::render(GLuint _textureName, const char* _comment)
{
	glUseProgram(program);

	m_pMovementType->Update(Translate, m_iTranslationOption, m_fTranslateX, m_fTranslateY, m_fTranslateZ);
	m_pMovementType->Update(Scale, m_iScaleOption, m_fTranslateX, m_fTranslateY, m_fTranslateZ);
	m_pMovementType->Update(Rotate, m_iRotationOption, m_fTranslateX, m_fTranslateY, m_fTranslateZ);

	glm::vec3 objPosition = glm::vec3(m_fTranslateX, m_fTranslateY, m_fTranslateZ);
	glm::mat4 translate = glm::translate(glm::mat4(), objPosition);

	/* Scale is not working */
	glm::vec3 objScale = glm::vec3(m_fScaleX, m_fScaleY, m_fScaleZ);
	glm::mat4 scale = glm::scale(glm::mat4(), objScale);

	// RotateX
	glm::vec3 rotationAxisX = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::mat4 rotateX = glm::rotate(glm::mat4(), glm::radians(m_fRotateX), rotationAxisX);
	// RotateY
	glm::vec3 rotationAxisY = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 rotateY = glm::rotate(glm::mat4(), glm::radians(m_fRotateY), rotationAxisY);
	// RotateZ
	glm::vec3 rotationAxisZ = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::mat4 rotateZ = glm::rotate(glm::mat4(), glm::radians(m_fRotateZ), rotationAxisZ);

	glm::mat4 rotate = rotateZ * rotateY * rotateX;

	glm::mat4 model = translate * rotate * scale;
	GLuint modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(
		modelLoc,				//transformation location
		1,							//How many Matrix
		GL_FALSE,					//Normalizes
		glm::value_ptr(model));	//Point to memory
	

	glCullFace(GL_BACK); // Cull the Back faces 
	glFrontFace(GL_CW); // Front face is Clockwise order 
	glEnable(GL_CULL_FACE); // Turn on the back face culling

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureName);
	glUniform1i(glGetUniformLocation(program, _comment), 0);

	glBindVertexArray(vao); // Bind VAO
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); // Unbind VAO

	glUseProgram(0);
	glDisable(GL_CULL_FACE);
}

void CEntity::ResetTranslation()
{
	m_fTranslateX = 0.0f;
	m_fTranslateY = 0.0f;
}

void CEntity::SetRender(bool _bRender)
{
	m_bRender = _bRender;
}
bool CEntity::GetRender() const
{
	return(m_bRender);
}