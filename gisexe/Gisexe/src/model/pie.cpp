#include "pie.h"
#include "fan.h"

_GIS_BEGIN

void Pie::set( const std::vector<float>& values, const std::vector<float3>& colors, const float3& center, float radius /*= 1.0f*/ )
{
	_values = values;
	_colors = colors;
	_center = center;
	_radius = radius;
}

void gis::Pie::init()
{
	float sum = 0; // valuesµÄºÍ
	for (int i = 0; i < _values.size(); i++)
	{
		sum += _values[i];
	}

	float current = 0;

	for (int i = 0; i < _values.size(); i++)
	{
		Fan* fan = new Fan;
		fan->set(current, current + _values[i] / sum * 360, _colors[i], _center, _radius);
		fan->setLinearScaler(_valueScaler);
		fan->init();
		_container.add(fan);

		current += _values[i] / sum * 360;
	}
}

_GIS_END