

#include "../util/texture.h"
#include "seaplane.h"
#include <gl/glut.h>

void gis::SeaPlane::initList()
{
	// 中心球
	int SeaTexture = loadTexture("E:\\GIS\\data\\img\\ss.bmp");
	float width = 10.0f;
	float height = 10.0f;
	
	glEnable(GL_TEXTURE_2D); // 启用纹理映射
	glColor3f(0.6, 0.6, 1);
	float mat_emission[] = { 0.45, 0.87, 0.93, 0.0f };
	float no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission); 
	glBindTexture(GL_TEXTURE_2D, SeaTexture);	
	glBegin(GL_QUADS); 
	// 底面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, 0.03f, -height);	// 纹理和四边形的右上
	glTexCoord2f(1.0f, 0.0f); glVertex3f( width, 0.03f, -height);	// 纹理和四边形的左上
	glTexCoord2f(1.0f, 1.0f); glVertex3f( width, 0.03f,  height);	// 纹理和四边形的左下
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, 0.03f,  height);	// 纹理和四边形的右下
	glEnd();
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glDisable(GL_TEXTURE_2D);
}

void gis::SeaPlane::begin()
{
	glEnable(GL_LIGHTING);
}

void gis::SeaPlane::end()
{
	glDisable(GL_LIGHTING);
}
