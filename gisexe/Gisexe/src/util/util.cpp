
#include "util.h"

_GIS_BEGIN

//当大型对象被传递给函数时，使用引用参数可使参数传递效率得到提高，因为引用并不产生对象的
//副本，也就是参数传递时，对象无须复制。
float3 triangle_normal(const float3& a, const float3&b, const float3& c) // a,b,c逆时针
{
	return cross(b - a, c - b).normalize();
}

float3 cross(const float3& a, const float3& b)
{
	float3 tmp;
	tmp[0] = a[1] * b[2] - a[2] * b[1];
	tmp[1] = a[2] * b[0] - a[0] * b[2];
	tmp[2] = a[0] * b[1] - a[1] * b[0];
	return tmp; 
}

float dot(const float3& a, const float3& b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float angle2radian( float angle )
{
	return angle * PI / 180;
}

_GIS_END