#ifndef _FAN_H_
#define _FAN_H_

#include "model.h"

_GIS_BEGIN

class Fan : public Model
{
public:
	void set(float start, float end, const float3& color, 
		const float3& center, float radius = 1.0f, float slice = 1);
	void setCircle(float start, float end);
	void setColor(const float3& color);
	void setSlice(float slice);
	void setRadius(float radius);

	virtual void init(); 
protected:
	float3 _color;
	float _start, _end; 
	float _slice; 
	float _radius;
	float3 _center; 
};

_GIS_END

#endif