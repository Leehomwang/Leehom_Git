#ifndef _STACKEDBAR_H_
#define _STACKEDBAR_H_

#include "model.h"

_GIS_BEGIN

class StackedBar : public Model
{
public:
	void set(const std::vector<float>& values, const std::vector<float3>& colors,
		const float3& center, float radius = 1.0f);

	virtual void init();
protected:
	std::vector<float> _values;
	std::vector<float3> _colors;
	float _radius;
	float3 _center;
};

_GIS_END

#endif