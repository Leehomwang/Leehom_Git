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

	virtual void init(); // 初始化
	virtual void begin();
	virtual void end();
	virtual void pick(int x, int y); // 选择

	void setShpLoader(ShpLoader* shpLoader);
	void setColor(const float3& color);
protected:
	ShpLoader* _shpLoader;
	float3 _color; // 颜色
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
//	virtual void init(); // 初始化
//	virtual void begin();
//	virtual void paint(); // 绘制
//	virtual void end();
//	virtual void pick(int x, int y); // 选择
//
//	void setShpLoader(ShpLoader* shpLoader);
//	void setColor(const float3& color);
//protected:
//	void clear();
//
//	ShpLoader* _shpLoader;
//
//	float3 _color; // 颜色
//	std::vector<Ladder*> _ladders; // 各个阶梯
//};
//
//_GIS_END
//
//#endif