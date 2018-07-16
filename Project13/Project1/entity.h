#pragma once

#include <ctime>
#include <random>

#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include "Dependencies\soil\soil.h" 

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "ShaderLoader.h"

#include "Constants.h"
#include "ConstantsShapes.h"
#include "images.h"
#include "moveTypes.h"

enum Direction
{
	UP = 0,
	Down,
	Left,
	Right,
};

enum Shape
{
	Background,
	Square,
};

class CEntity
{
public:
	CEntity();
	~CEntity() {};

	void BindImage(Shape _ThisShape, GLuint& _program, GLuint& _textureName, const char* _fileName, int _iTranslationMove, int _iRotationMove, int _iScaleMove);
	void render(GLuint _textureName, const char* _fileName);

	void TranslateObject(int iDirection);
	void ScaleAnimation();
	void ResetTranslation();

	void enemyStart();
	void enemyStart4();

	void enemyMoveTypeOne();
	void enemyMoveTypeTwo();
	void enemyMoveTypeThree(float _fPlayerX, float _fPlayerY);
	void enemyDontMove();

	float GetXTranslatePosition() const;
	float GetYTranslatePosition() const;

	void SetRender(bool _bRender);
	bool GetRender() const;

	void InitializeTexture2(GLuint& _textureName, const char* _fileName);
	void InitializeTexture3(GLuint& _textureName, const char* _fileName);
	void ActivateTexture(GLuint _textureName, const char* _comment);

	void ImageNumber(int _iNumber);

private:
	GLuint program;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	CMoveTypes* m_pMovementType;

	GLuint texture1;
	GLuint texture2;
	GLuint texture3;

	int m_iActiveTexture;

	float m_fTranslateX;
	float m_fTranslateY;
	float m_fTranslateZ;
	float fGradualchange;
	float m_fScaleX;
	float m_fScaleY;
	float m_fScaleZ;
	float m_fRotateX;
	float m_fRotateY;
	float m_fRotateZ;

	int m_iTranslationOption;
	int m_iScaleOption;
	int m_iRotationOption;

	int m_iMovementDirection;

	int m_iDirectionCooldown;

	bool m_bRender;
};