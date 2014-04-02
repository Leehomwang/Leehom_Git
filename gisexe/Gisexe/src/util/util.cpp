
#include "util.h"

_GIS_BEGIN

//�����Ͷ��󱻴��ݸ�����ʱ��ʹ�����ò�����ʹ��������Ч�ʵõ���ߣ���Ϊ���ò������������
//������Ҳ���ǲ�������ʱ���������븴�ơ�
float3 triangle_normal(const float3& a, const float3&b, const float3& c) // a,b,c��ʱ��
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