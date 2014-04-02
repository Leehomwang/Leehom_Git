#ifndef _UTIL_H_
#define _UTIL_H_

#include "vec.h"

_GIS_BEGIN

#define PI 3.14159265359

float3 cross(const float3& a, const float3& b);
float dot(const float3& a, const float3& b);
float3 triangle_normal(const float3& a, const float3&b, const float3& c);
float angle2radian(float angle);

_GIS_END

#endif