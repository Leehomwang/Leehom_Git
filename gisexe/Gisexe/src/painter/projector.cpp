#include "../util/util.h"
#include "projector.h"

_GIS_BEGIN
///////////////////////////////////////////////////////////////////////////////
LinearScaler::LinearScaler(float bottom /*= 0.0f*/, float top /*= 1.0f*/ )
{
	setBound(0, 0);
	setVertical(bottom, top);
	_scale = 1.0f;
}

void LinearScaler::setBound( float min, float max )
{
	_min = min;
	_max = max;
	_scale = (_top - _bottom) / (_max - _min);
}

void LinearScaler::setVertical( float bottom, float top )
{
	_bottom = bottom;
	_top = top;
	_scale = (_max == _min) ? _scale : (_top - _bottom) / (_max - _min);
}

float LinearScaler::operator()( float value /*= 0*/ ) const
{
	return _bottom + (value - _min) * _scale; // 线性映射
}

float LinearScaler::getBottom() const
{
	return _bottom;
}

float LinearScaler::getTop() const
{
	return _top;
}

///////////////////////////////////////////////////////////////////////////////
float3 Projector::operator()( const float3& v ) const
{
	return (*this)(v[0], v[1], v[2]);
}

std::vector<float3> Projector::operator()( const std::vector<float3>& vs ) const
{
	std::vector<float3> result(vs.size());
	for (int i = 0; i < vs.size(); i++)
	{
		result[i] = (*this)(vs[i]);
	}
	return result;
}

///////////////////////////////////////////////////////////////////////////////
PlaneProjector::PlaneProjector()
{

}

PlaneProjector::PlaneProjector( const BBox& bbox, float square /*= 2.0*/)
{
	_square = square;

	float xmin = bbox[0], xmax = bbox[1];
	float ymin = bbox[2], ymax = bbox[3];

	float xlen = xmax - xmin;
	float ylen = ymax - ymin;

	// calculate center of the model 
	_center[0] = (xmin + xmax) / 2.0;
	_center[1] = (ymin + ymax) / 2.0;

	// calculate unitizing scale factor 
	float max = xlen > ylen ? xlen : ylen;

	_scale[0] = square / max; // xy的scale是一样的，按最长轴缩放到[-1, 1]来
	_scale[1] = square / max;
}

float3 PlaneProjector::operator()( float x, float y, float z ) const
{
	float v2[] = { x, y };
	float2 tmp(v2);
	tmp -= _center;
	tmp *= _scale;
	float v3[] = { tmp[0], tmp[1], z };
	return v3;
}

///////////////////////////////////////////////////////////////////////////////
SphereProjector::SphereProjector()
{

}

SphereProjector::SphereProjector( const BBox& bbox, float radius /*= 1.0*/ )
{
	_radius = radius;
}

float3 SphereProjector::operator()( float lon, float lat, float r ) const
{
	float theta = lon * PI / 180;
	float phi = lat * PI / 180;

	float radius = _radius + r;

	float v[] = 
	{
		-radius * cos(phi) * sin(theta),
		-radius * cos(phi) * cos(theta),
		-radius * sin(phi)
	};
	return v;
}

_GIS_END
