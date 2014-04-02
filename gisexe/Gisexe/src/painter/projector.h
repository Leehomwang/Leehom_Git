#ifndef _PROJECTOR_H_
#define _PROJECTOR_H_

#include <vector>
#include "../util/vec.h"

_GIS_BEGIN

// ��xy��һ��[-1, 1]�ڣ�h(��z)��һ��[0, 1]��
class LinearScaler
{
public:
	LinearScaler(float bottom = 0.0f, float top = 1.0f);

	void setBound(float min, float max);
	void setVertical(float bottom, float top);

	float getBottom() const; // ���ؿ���ӳ�䵽��������ֵ����ֹ��������ֻ����ߺ���͵�ֵ
	float getTop() const;

	float operator()(float value = 0) const; // ����ֵӳ��
protected:
	float _bottom, _top; // �߶ȣ����߶ȹ�һ��_base��_base + _height֮��
	float _min, _max; // ֵ������
	float _scale; // ֵӳ��ʱ�������
};

class Projector
{
public:
	float3 operator()(const float3& v) const;
	std::vector<float3> operator()(const std::vector<float3>& vs) const;

	virtual float3 operator()(float x, float y, float z) const = 0; // ֻ��һ��xy��z��LinearScaler�����Ѿ���һ��
};

// ����ͶӰ���ñ߳�Ϊsquare���������Χ��Χ��xy�ᣬz��߶��ܹ�Ϊheight������(0, 0, 0)
// ����xy������Ĺ�һ��square��z���һ��height
class PlaneProjector : public Projector
{
public:
	PlaneProjector();
	PlaneProjector(const BBox& bbox, float square = 2.0);
	virtual float3 operator()(float x, float y, float z) const;
protected:
	float _square; // ����
	float2 _center, _scale; // ��һ��������xy���ģ�xy������ϵ��
};

class SphereProjector : public Projector
{
public:
	SphereProjector();
	SphereProjector(const BBox& bbox, float radius = 1.0);

	virtual float3 operator()(float x, float y, float z) const;
protected:
	float _radius; // ͶӰ��뾶
};

_GIS_END

#endif