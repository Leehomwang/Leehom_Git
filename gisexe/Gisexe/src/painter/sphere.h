#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "painter.h"

_GIS_BEGIN

class Sphere : public Painter
{
public:
	Sphere(const float3& center, const float3& color, int level = 2);
	void set(const float3& center, const float3& color, int level = 2);

	virtual void initList();
	virtual void initHint();

	void setLinearScaler(const LinearScaler& scaler);
protected:
	void compute();

	void subdivide(const float* v1, const float* v2, const float* v3, int level); // µÝ¹éÏ¸·Ö
	void normalize(float* v); 

	int _level;
	float _radius; // °ë¾¶
	float3 _center; 

	float3 _color;
	std::vector<float3> _vertices;
	std::vector<float3> _normals;

	LinearScaler _valueScaler; 
};

_GIS_END


#endif