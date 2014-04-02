#include <stdio.h>
#include "texture.h"

_GIS_BEGIN

// 需要link里加glaux.lib
AUX_RGBImageRec *LoadBMP(const char *Filename)				// 载入位图图象
{
	FILE *File=NULL;									// 文件句柄
	if (!Filename)										// 确保文件名已提供
	{
		return NULL;									// 如果没提供，返回 NULL
	}
	File=fopen(Filename,"r");							// 尝试打开文件
	if (File)											// 文件存在么?
	{
		fclose(File);									// 关闭句柄
		return auxDIBImageLoadA(Filename);				// 载入位图并返回指针
	}
	return NULL;										// 如果载入失败，返回 NULL
}

GLuint loadTexture(const char *Filename)									// 载入位图(调用上面的代码)并转换成纹理
{
	static int textureID = 1;
	GLuint texture = textureID++;

	AUX_RGBImageRec* TextureImage[1];					// 创建纹理的存储空间
	memset(TextureImage,0,sizeof(void *)*1);			// 将指针设为 NULL
	if (TextureImage[0]=LoadBMP(Filename))
	{
		glGenTextures(1, &texture);					// 创建纹理

		// 使用来自位图数据生成 的典型纹理
		glBindTexture(GL_TEXTURE_2D, texture);
		// 生成纹理
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// 线形滤波
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// 线形滤波
	}

	if (TextureImage[0])								// 纹理是否存在
	{
		if (TextureImage[0]->data)						// 纹理图像是否存在
		{
			free(TextureImage[0]->data);				// 释放纹理图像占用的内存
		}
		free(TextureImage[0]);							// 释放图像结构
	}

	return texture;
}

_GIS_END