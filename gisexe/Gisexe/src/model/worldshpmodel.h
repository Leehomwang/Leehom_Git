#ifndef _WORLDSHPMODEL_H_
#define _WORLDSHPMODEL_H_

#include "model.h"
#include "ladder.h"
#include "../io/shploader.h"

_GIS_BEGIN

class WorldShpModel : public Model
{
public:
	WorldShpModel();
	virtual ~WorldShpModel();

	virtual void init(); // ��ʼ��
	virtual void begin();
	virtual void end();
	virtual void pick(int x, int y); // ѡ��

	void setShpLoader(ShpLoader* shpLoader);
	void setColor(const float3& color);
protected:
	ShpLoader* _shpLoader;
	float3 _color; // ��ɫ
};

_GIS_END

#endif

//#ifndef _WORLDSHPMODEL_H_
//#define _WORLDSHPMODEL_H_
//
//#include "model.h"
//#include "ladder.h"
//#include "../io/shploader.h"
//
//_GIS_BEGIN
//
//class WorldShpModel : public Model
//{
//public:
//  WorldShpModel();
//  virtual ~WorldShpModel();
//
//	virtual void init(); // ��ʼ��
//	virtual void begin();
//	virtual void paint(); // ����
//	virtual void end();
//	virtual void pick(int x, int y); // ѡ��
//
//	void setShpLoader(ShpLoader* shpLoader);
//	void setColor(const float3& color);
//protected:
//	void clear();
//
//	ShpLoader* _shpLoader;
//
//	float3 _color; // ��ɫ
//	std::vector<Ladder*> _ladders; // ��������
//};
//
//_GIS_END
//
//#endif