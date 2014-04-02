#include <gl/glew.h>
#include "seidel/mytri.h"
#include "worldshpmodel.h"
#include <fstream>

_GIS_BEGIN

WorldShpModel::WorldShpModel()
{
	_shpLoader = NULL;
}

WorldShpModel::~WorldShpModel()
{
	if (_shpLoader)
	{ 
		delete _shpLoader; 
		_shpLoader = NULL;
	}
}

void WorldShpModel::setShpLoader( ShpLoader* shpLoader )
{
	_shpLoader = shpLoader;
}

void WorldShpModel::setColor( const float3& color )
{
	_color = color;
}

void WorldShpModel::init()
{
	const SHPHandle& hSHP = _shpLoader->getHandle();
	float c[7][3] = {{0.5,1,1},{0.5,1,0.5},{0.5,1,0.8},{0.8,1,0.5},{0.5,0.8,1},{0.8,0.5,1},{1,0.5,0.8}};//���������̣��̣����̣�����������, ��ɫ
	for (int i = 0; i < hSHP->nRecords; i++) // ����ÿ����¼
	{
		//std::ofstream savefile("Indeices.txt");
		std::vector<double2> contour; 
		SHPObject *psShape = SHPReadObject(hSHP, i);
		for (int j = psShape->nVertices - 1; j >= 0; j--)
		{
			//savefile << psShape->padfX[j] << " ";
			//savefile << psShape->padfY[j] << std::endl;
			double v[] = { psShape->padfX[j], psShape->padfY[j] };
			contour.push_back(v);
		}
		SHPDestroyObject(psShape);
		//savefile.close();

		//float c[] = { rand() % 256 / 255.0, rand() % 256 / 255.0, rand() % 256 / 255.0 };
		int num = i%7;
		Ladder* ladder = new Ladder;
		//ladder->setColor(c);
		float cc[3] = {1,1,0.5};
		for (int k = 0; k < 3; k++)
		{
			cc[k]= c[num][k];
		}
		ladder->setColor(cc);
		ladder->setLinearScaler(_valueScaler);
		ladder->setContour(contour);
		ladder->init(); // ��ʼ��

		_container.add(ladder);
	}
}

void WorldShpModel::pick(int x, int y)
{
	_container.hint();

	// ʰȡ
	int nWidth = 1; 
	int nHeight = 1;
	unsigned char *pRGB = new unsigned char [3 * (nWidth + 1) * (nHeight + 1) + 3];
	glReadPixels(x, y, nWidth, nHeight, GL_RGB, GL_UNSIGNED_BYTE, pRGB);//��ȡ1X1�����ؿ���ɫֵ��pRGB�У�x��yΪ���ؿ����½�����
	//glReadPixels(x, y, nWidth, nHeight, GL_BGR, GL_UNSIGNED_BYTE, pRGB);
	int hintID = (pRGB[0]) + (pRGB[1] << 8) + (pRGB[2] << 16) -2;//˫��֮ǰ_hintIDĪ������ı仯��2����ԭ����14��Ϊ16֮���
	//int hintID1 = 203 + 203<<8 + 255<<16;
	//int hintID2 = 204 + 204<<8 + 255<<16;

	Console::debug("%d %d %d %d\n", pRGB[0], pRGB[1], pRGB[2], hintID);


	Ladder* ladder = NULL;

	ladder = (Ladder*)_container.find(_lastID);
	if (ladder)
	{
		ladder->setLinearScaler(_valueScaler);
		ladder->init();
		ladder->paint(); 
	}
	
	ladder = (Ladder*)_container.find(hintID);
	if (ladder)
	{
		ladder->setLinearScaler(
			LinearScaler(_valueScaler.getBottom(), 
			(_valueScaler.getTop() - _valueScaler.getBottom()) * 1.5)); // �߶�����1.5��
		ladder->init();
		ladder->paint(); 
	}
}

void WorldShpModel::begin()
{
	glEnable(GL_LIGHTING);
}

void WorldShpModel::end()
{
	glDisable(GL_LIGHTING);
}

_GIS_END
