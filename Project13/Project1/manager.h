#pragma once

#include <vector>
#include <ctime>
#include <string>

#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include "Dependencies\soil\soil.h" 

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "Dependencies\FMOD\fmod.hpp"

#include "TextLabel.h"
#include "entity.h"
#include "camera.h"
#include "moveTypes.h"
#include "Sphere.h"
#include "ConstantsShapes.h"
#include "cubeMap.h"
#include "Model.h"
#include "ModelMesh.h"

#ifndef __MANAGER_H__
#define __MANAGER_H__

class CManager
{
public:
	static CManager* GetInstance();

	void Initialise();
	void Render();
	void Update();

	/*void NextLevel();

	void PlayerMovementUP();
	void PlayerMovementDown();
	void PlayerMovementLeft();
	void PlayerMovementRight();

	void Immune();

	void renderEnemy4(int _iTime);*/

protected:

private:
	CManager() {};
	~CManager();

	CManager(CManager const&);
	CManager& operator=(CManager const&);

	static CManager* m_pInstance;

	FMOD::System* m_paudioMgr;
	FMOD::Sound* m_pfxExplosion3;
	FMOD::Sound* m_pbgmTheme;
	bool InitFmod();
	const bool LoadAudio();

	CCamera* m_pCamera;

	GLuint m_Program;
	GLuint m_Program2;
	GLuint m_Program3;
	GLfloat m_fCurrentTime;

	Sphere* m_pSphere;

	GLuint tex;
	GLuint texture2;

	CCubeMap* m_pCubeMap;

	Model* my3DModel;

	//CMoveTypes* m_pMovementTypeInitiliser;




	//int m_iPlayerCollisionWithEnemy;
	//bool m_bLastLevel;
	//bool m_bTest;

	//int m_iLevel;
	//int m_iCollisionCoolDown;
	//
	//bool m_bDeactivateCollisions;
	//int m_iTime;
	//int m_iNumber;
	//std::string strTimer;
	//std::string strNumber;
	//TextLabel* m_pTimertext;
	//TextLabel* m_pTimertext2;
	//TextLabel* m_pLevel;
	//TextLabel* m_pLevelNumber;
	//TextLabel* m_pImmunetext;

	//bool m_bImmune;

	//GLuint m_Background;
	//CEntity* m_pPlayer;
	//GLuint m_Player;
	//std::vector<CEntity*> vecEnemies;


	///* Start Screen */
	//TextLabel* m_pTitle;
	//TextLabel* m_pSubtext;
	//GLuint m_enemyOpening;
	//GLuint m_enemyOpening2;
	//std::vector<CEntity*> vecEnemyOpening;

	///* Level 1 */
	//CEntity* m_pImage;
	//CEntity* m_pEnemy1;
	//GLuint m_enemy1;

	///* Level 2 */
	//CEntity* m_pEnemy2;
	//GLuint m_enemy2;

	///* Level 3 */
	//CEntity* m_pEnemy3;
	//GLuint m_enemy3;

	///* Level 4 */
	//CEntity* m_pEnemy41;
	//CEntity* m_pEnemy42;
	//GLuint m_enemy4Image1;
	//GLuint m_enemy4Image2;
	//GLuint m_enemy4Image3;

	///* Win Screen */
	//TextLabel* m_pEndTitleWin;

	///* Game Over */
	//TextLabel* m_pEndTitle;
	//TextLabel* m_pEndSubtext;


	//

	//TextLabel* label;


	//void TestForCollisions();
	//
	//int m_iAnimationCoolDown;
};

#endif // __MANAGER_H__