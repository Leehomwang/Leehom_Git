#ifndef _PROJECTOR_H_
#define _PROJECTOR_H_

#include <vector>
#include "../util/vec.h"

_GIS_BEGIN

// 把xy归一到[-1, 1]内，h(即z)归一到[0, 1]内
class LinearScaler
{
public:
	LinearScaler(float bottom = 0.0f, float top = 1.0f);

	void setBound(float min, float max);
	void setVertical(float bottom, float top);

	float getBottom() const; // 返回可以映射到的最高最低值，防止阶梯那样只有最高和最低的值
	float getTop() const;

	float operator()(float value = 0) const; // 根据值映射
protected:
	float _bottom, _top; // 高度，将高度归一到_base到_base + _height之间
	float _min, _max; // 值上下限
	float _scale; // 值映射时候的缩放
};

class Projector
{
public:
	float3 operator()(const float3& v) const;
	std::vector<float3> operator()(const std::vector<float3>& vs) const;

	virtual float3 operator()(float x, float y, float z) const = 0; // 只归一化xy，z由LinearScaler负责，已经归一了
};

// 构造投影，用边长为square的正方体包围包围盒xy轴，z轴高度总共为height，中心(0, 0, 0)
// 即把xy轴中最长的归一到square，z轴归一到height
class PlaneProjector : public Projector
{
public:
	PlaneProjector();
	PlaneProjector(const BBox& bbox, float square = 2.0);
	virtual float3 operator()(float x, float y, float z) const;
protected:
	float _square; // 长宽
	float2 _center, _scale; // 归一化变量：xy中心，xy轴缩放系数
};

class SphereProjector : public Projector
{
public:
	SphereProjector();
	SphereProjector(const BBox& bbox, float radius = 1.0);

	virtual float3 operator()(float x, float y, float z) const;
protected:
	float _radius; // 投影球半径
};

_GIS_END

#endif