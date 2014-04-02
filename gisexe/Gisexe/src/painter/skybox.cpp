

#include "../util/texture.h"
#include "skybox.h"
#include <gl/glut.h>

void gis::SkyBox::initList()
{
	//// 中心球
	//GLUquadricObj *quadratic = gluNewQuadric(); // 创建二次几何体
	//gluQuadricNormals(quadratic, GL_SMOOTH);					  // Generate Smooth Normals For The Quad
	//gluQuadricTexture(quadratic, GL_TRUE);						  // Enable Texture Coords For The Quad

	//glColor3f(0.6, 0.6, 1);

	//float mat_emission[] = { 0.1, 0.1, 0.9, 0.0f };
	//float no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	//glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission); 
	//gluSphere(quadratic, 0.97, 64, 64);
	//glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	//gluDeleteQuadric(quadratic); // 删除二次几何体


	// 天空盒
	glColor3f(0.6, 0.6, 1);////保证天空盒的颜色
	int front, back, top, bottom, left, right;
	if (ChooseProjection)
	{
		front = loadTexture("E:\\GIS\\data\\img\\star2_up.bmp");
		back = loadTexture("E:\\GIS\\data\\img\\star2_botton.bmp");
		top = loadTexture("E:\\GIS\\data\\img\\star2_front.bmp");
		bottom = loadTexture("E:\\GIS\\data\\img\\star2_back.bmp");
		left = loadTexture("E:\\GIS\\data\\img\\star2_left.bmp");
		right = loadTexture("E:\\GIS\\data\\img\\star2_right.bmp");
	}
	else
	{
		front = loadTexture("E:\\GIS\\data\\img\\ypos1.bmp");
		back = loadTexture("E:\\GIS\\data\\img\\yneg1.bmp");
		top = loadTexture("E:\\GIS\\data\\img\\zpos1.bmp");
		bottom = loadTexture("E:\\GIS\\data\\img\\zneg1.bmp");
		left = loadTexture("E:\\GIS\\data\\img\\xpos1.bmp");
		right = loadTexture("E:\\GIS\\data\\img\\xneg1.bmp");
	}
	

	glEnable(GL_TEXTURE_2D); // 启用纹理映射

	float len = 10.f;

	glBindTexture(GL_TEXTURE_2D, back);	
	glBegin(GL_QUADS); // 后面zneg
		glTexCoord2f(0.0f, 0.0f); glNormal3f(len, len, len); glVertex3f(-len, -len, -len);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glNormal3f(-len, len, len); glVertex3f(len, -len, -len);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glNormal3f(-len, -len, len); glVertex3f(len, len, -len);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glNormal3f(len, -len, len); glVertex3f(-len, len, -len);	// 纹理和四边形的左上
	glEnd();

	glBindTexture(GL_TEXTURE_2D, left);	
	glBegin(GL_QUADS); // 左面xpos
		glTexCoord2f(0.0f, 0.0f); glNormal3f(len, len, -len); glVertex3f(-len, -len, len);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glNormal3f(len, len, len); glVertex3f(-len, -len, -len);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glNormal3f(len, -len, len); glVertex3f(-len, len, -len);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glNormal3f(len, -len, -len); glVertex3f(-len, len, len);	// 纹理和四边形的左上
	glEnd();

	glBindTexture(GL_TEXTURE_2D, right);	
	glBegin(GL_QUADS); // 右面xpos
		glTexCoord2f(0.0f, 0.0f); glNormal3f(-len, len, len); glVertex3f(len, -len, -len);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glNormal3f(-len, len, -len); glVertex3f(len, -len, len);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glNormal3f(-len, -len, -len); glVertex3f(len, len, len);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glNormal3f(-len, -len, len); glVertex3f(len, len, -len);	// 纹理和四边形的左上
	glEnd();

	glBindTexture(GL_TEXTURE_2D, top);	
	glBegin(GL_QUADS); // 上面
		glTexCoord2f(0.0f, 0.0f); glNormal3f(-len, -len, -len); glVertex3f(len, len, len);	// 纹理和四边形的右上
		glTexCoord2f(1.0f, 0.0f); glNormal3f(len, -len, -len); glVertex3f(-len, len, len);	// 纹理和四边形的左上
		glTexCoord2f(1.0f, 1.0f); glNormal3f(len, -len, len); glVertex3f(-len, len, -len);	// 纹理和四边形的左下
		glTexCoord2f(0.0f, 1.0f); glNormal3f(-len, -len, len); glVertex3f(len, len, -len);	// 纹理和四边形的右下
	glEnd();

	glBindTexture(GL_TEXTURE_2D, front);	
	glBegin(GL_QUADS); // 前面zpos
		glTexCoord2f(0.0f, 0.0f); glNormal3f(-len, len, -len); glVertex3f(len, -len, len);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glNormal3f(len, len, -len); glVertex3f(-len, -len, len);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glNormal3f(len, -len, -len); glVertex3f(-len, len, len);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glNormal3f(-len, -len, -len); glVertex3f(len, len, len);	// 纹理和四边形的左上
	glEnd();

	glBindTexture(GL_TEXTURE_2D, bottom);	
	glBegin(GL_QUADS); // 下面
		glTexCoord2f(0.0f, 0.0f); glNormal3f(len, len, -len); glVertex3f(-len, -len, len);	// 纹理和四边形的右上
		glTexCoord2f(1.0f, 0.0f); glNormal3f(-len, len, -len); glVertex3f(len, -len, len);	// 纹理和四边形的左上
		glTexCoord2f(1.0f, 1.0f); glNormal3f(-len, len, len); glVertex3f(len, -len, -len);	// 纹理和四边形的左下
		glTexCoord2f(0.0f, 1.0f); glNormal3f(len, len, len); glVertex3f(-len, -len, -len);	// 纹理和四边形的右下
	glEnd();
	
	glDisable(GL_TEXTURE_2D);

}

void gis::SkyBox::begin()
{
	glEnable(GL_LIGHTING);
}

void gis::SkyBox::end()
{
	glDisable(GL_LIGHTING);
}
