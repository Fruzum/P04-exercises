#include "glew.h"
#include "freeglut.h"
#include "soil.h"

class CIMAGELOADER
{
public:
	unsigned char* GetImage(const char* _fileName, int &_iWidth, int &_iHeight)
	{
		unsigned char* image = SOIL_load_image(
			_fileName,				//File Path/Name
			&_iWidth,				//Output for the image width
			&_iHeight,				//Output for the image height
			0,						//Output for the number of channels
			SOIL_LOAD_RGB			//Load RGB values only
		);
		return(image);
	}
	void CreateMipMap(int &_iWidth, int &_iHeight, unsigned char* _ucpImage)
	{
		glTexImage2D(
			GL_TEXTURE_2D,		//Type of texture
			0,					//Mipmap level, 0 for base
			GL_RGB,				//Number of colour components in texture
			_iWidth,			//Width of the texture
			_iHeight,			//Height of the texture
			0,					//This value must be 0
			GL_RGB,				//Format for the pixel data
			GL_UNSIGNED_BYTE,	//Date type for the pixel data
			_ucpImage			//Pointer to the image data in memory	
		);

		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(_ucpImage);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};