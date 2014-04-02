#ifndef _LINEARCOLOR_H_
#define _LINEARCOLOR_H_

#include <vector>
#include "vec.h"
#include "..\parameter\parameter.h"

_GIS_BEGIN

class LinearColor
{
public:
	LinearColor();

	void setBound(float min, float max); // 设置线性映射范围，即最大值最小值
	void setColors(const std::vector<float3>& colors); // 设置颜色数组

	float3 operator()(float value = 0) const;

protected:
	void setSegment(); 

	float _segment;
	float _min, _max; 
	std::vector<float3> _colors; 
};

_GIS_END

#endif