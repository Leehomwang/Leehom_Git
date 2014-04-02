

#include "../util/texture.h"
#include "earthball.h"
#include <gl/glut.h>

void gis::EarthBall::initList()
{
	// ������
	int EarthTexture = loadTexture("E:\\GIS\\data\\img\\earth1.bmp");

	glEnable(GL_TEXTURE_2D); // ��������ӳ��
	
	GLUquadricObj *quadratic = gluNewQuadric(); // �������μ�����
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

	gluDeleteQuadric(quadratic); // ɾ�����μ�����

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
