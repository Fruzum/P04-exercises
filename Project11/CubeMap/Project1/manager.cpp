#include "manager.h"

CManager* CManager::m_pInstance = nullptr;

CManager::~CManager()
{
	delete m_pSphere;
	m_pSphere = 0;
};

CManager* CManager::GetInstance()
{
	if (nullptr == m_pInstance)
	{
		m_pInstance = new CManager();
	}
	return(m_pInstance);
}

void CManager::Initialise()
{
	ShaderLoader shader;
	CIMAGELOADER ImageLoader;

	/* Create the program */
	m_Program = shader.CreateProgram("Vertex.txt", "Fragment.txt");
	m_Program2 = shader.CreateProgram("cubeMapVertex.txt", "cubeMapFragment.txt");

	/* Initializes the movement */
	//m_pMovementTypeInitiliser = CMoveTypes::GetInstance();

	/* Initialise the camera */
	m_pCamera = CCamera::GetCamera();
	m_pCamera->Initialize(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	/* Create and load audio */
	InitFmod();
	LoadAudio();
	FMOD::Channel* channel;
	m_paudioMgr->playSound(m_pbgmTheme, 0, false, &channel);

	m_pSphere = new Sphere();

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	ImageLoader.CreateMipMap("Images/Rayman.png");

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	ImageLoader.CreateMipMap("Images/AwesomeFace.png");

	std::vector<std::string> FileNames;
	FileNames.push_back("right.jpg");
	FileNames.push_back("left.jpg");
	FileNames.push_back("top.jpg");
	FileNames.push_back("bottom.jpg");
	FileNames.push_back("back.jpg");
	FileNames.push_back("front.jpg");
	m_pCubeMap = new CCubeMap(m_Program2, FileNames);
}

void CManager::Render()
{
	glUseProgram(m_Program);
	m_fCurrentTime = (GLfloat)glutGet(GLUT_ELAPSED_TIME);// Get current time. 
	m_fCurrentTime = m_fCurrentTime / 1000;  // Convert millisecond to seconds
	GLint m_iCurrentTimeLoc = glGetUniformLocation(m_Program, "currentTime");
	glUniform1f(m_iCurrentTimeLoc, m_fCurrentTime);// set value

	GLfloat ambientStrength = 0.05f;
	GLint ambientStrengthLoc = glGetUniformLocation(m_Program, "ambientStrength");
	glUniform1f(ambientStrengthLoc, ambientStrength);

	glm::vec3 ambientColor = glm::vec3(1.0f, 1.0f, 1.0f);
	GLint ambientColorLoc = glGetUniformLocation(m_Program, "ambientColor");
	glUniform3fv(ambientColorLoc, 1, glm::value_ptr(ambientColor));

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	GLint lightColorLoc = glGetUniformLocation(m_Program, "lightColor");
	glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

	glm::vec3 lightPos = glm::vec3(-5.0f, 5.0f, 0.5f);
	GLint lightPosLoc = glGetUniformLocation(m_Program, "lightPos");
	glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));

	GLfloat lightSpecStrength = 1.0f;
	GLint lightSpecStrengthLoc = glGetUniformLocation(m_Program, "lightSpecStrength");
	glUniform1f(lightSpecStrengthLoc, lightSpecStrength);

	GLfloat shininess = 256.0f;
	GLint shininessLoc = glGetUniformLocation(m_Program, "shininess");
	glUniform1f(shininessLoc, shininess);

	glm::vec3 rimColor = glm::vec3(0.5f, 0.0f, 1.0f);
	GLint rimColorLoc = glGetUniformLocation(m_Program, "rimColor");
	glUniform3fv(rimColorLoc, 1, glm::value_ptr(rimColor));
	glUseProgram(0);


	/* Camera */
	glUseProgram(m_Program);

	glm::mat4 CameraModel = glm::mat4();
	//m_pCamera->render(m_Program, m_fCurrentTime, CameraModel);
	////For the class
	//GLint modelLoc = glGetUniformLocation(m_Program, "model");
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CameraModel));

	//glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(CameraModel)));
	//GLint normalMatrixLoc = glGetUniformLocation(m_Program, "normalMatrix");
	//glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	//glm::vec3 camPos = glm::vec3(m_fCamX, m_fCamY, m_fCamZ);// glm::vec3(m_pCamera->GetCamX(), m_pCamera->GetCamY(), m_pCamera->GetCamZ());
	//GLint camPosLoc = glGetUniformLocation(m_Program, "camPos");
	//glUniform3fv(camPosLoc, 1, glm::value_ptr(camPos));
	//glUseProgram(0);

	//For the local camera
	GLfloat radius = 4.0f;
	GLfloat m_fCamX = sin(m_fCurrentTime) * radius; //Rotating the camera around
	GLfloat m_fCamY = 3.0f;
	GLfloat m_fCamZ = cos(m_fCurrentTime) * radius; //The 3D object

	glm::mat4 CameraView = glm::lookAt(glm::vec3(m_fCamX, m_fCamY, m_fCamZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 CameraProjection = glm::perspective(45.0f, (GLfloat)Utility::SCR_WIDTH / (GLfloat)Utility::SCR_HEIGHT, 0.1f, 10000.0f);

	glm::mat4 MVP = CameraProjection * CameraView * CameraModel;
	GLint MVPLoc = glGetUniformLocation(m_Program, "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	//For the local
	GLint modelLoc = glGetUniformLocation(m_Program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(CameraModel));

	glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(CameraModel)));
	GLint normalMatrixLoc = glGetUniformLocation(m_Program, "normalMatrix");
	glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	glm::vec3 camPos = glm::vec3(m_fCamX, m_fCamY, m_fCamZ);
	GLint camPosLoc = glGetUniformLocation(m_Program, "camPos");
	glUniform3fv(camPosLoc, 1, glm::value_ptr(camPos));

	/* Change later */
	glUseProgram(m_Program);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(glGetUniformLocation(m_Program, "tex"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(m_Program, "texture2"), 1);

	m_pSphere->Render();
	glUseProgram(0);

	m_pCubeMap->Render(CameraProjection, CameraView);
}

void CManager::Update()
{
	
}

bool CManager::InitFmod()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&m_paudioMgr);
	if (result != FMOD_OK)
	{
		return (false);
	}

	result = m_paudioMgr->init(50, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		return (false);
	}
	return (true);
}

const bool CManager::LoadAudio()
{
	FMOD_RESULT result;
	result = m_paudioMgr->createSound("Audio/Explosion3.wav", FMOD_DEFAULT, 0, &m_pfxExplosion3);
	result = m_paudioMgr->createSound("Audio/Background.wav", FMOD_DEFAULT, 0, &m_pbgmTheme);
	m_pbgmTheme->setMode(FMOD_LOOP_NORMAL);

	return (true);
}