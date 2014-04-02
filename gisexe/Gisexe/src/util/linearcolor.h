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

	void setBound(float min, float max); // ��������ӳ�䷶Χ�������ֵ��Сֵ
	void setColors(const std::vector<float3>& colors); // ������ɫ����

	float3 operator()(float value = 0) const;

protected:
	void setSegment(); 

	float _segment;
	float _min, _max; 
	std::vector<float3> _colors; 
};

_GIS_END

#endif