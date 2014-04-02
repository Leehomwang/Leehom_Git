

#include "../util/texture.h"
#include "earthball.h"
#include <gl/glut.h>

void gis::EarthBall::initList()
{
	// 中心球
	int EarthTexture = loadTexture("E:\\GIS\\data\\img\\earth1.bmp");

	glEnable(GL_TEXTURE_2D); // 启用纹理映射
	
	GLUquadricObj *quadratic = gluNewQuadric(); // 创建二次几何体
	gluQuadricNormals(quadratic, GL_SMOOTH);					  // Generate Smooth Normals For The Quad
	gluQuadricTexture(quadratic, GL_TRUE);						  // Enable Texture Coords For The Quad

	glColor3f(0.6, 0.6, 1);

	float mat_emission[] = { 0.1, 0.1, 0.9, 0.0f };
	float no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission); 
	glBindTexture(GL_TEXTURE_2D, EarthTexture);	
	//glRotatef(-90,1,0,0);
	//glRotatef(180,0,0,1);
	gluSphere(quadratic, 0.97, 64, 64);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	gluDeleteQuadric(quadratic); // 删除二次几何体

	glDisable(GL_TEXTURE_2D);
}

void gis::EarthBall::begin()
{
	glEnable(GL_LIGHTING);
}

void gis::EarthBall::end()
{
	glDisable(GL_LIGHTING);
}
