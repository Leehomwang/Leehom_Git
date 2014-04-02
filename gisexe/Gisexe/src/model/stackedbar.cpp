#include "stackedbar.h"
#include "fan.h"

_GIS_BEGIN

void StackedBar::set( const std::vector<float>& values, const std::vector<float3>& colors,
										 const float3& center, float radius /*= 1.0f*/ )
{
	_values = values;
	_colors = colors;
	_center = center;
	_radius = radius;
}

void gis::StackedBar::init()
{
	float sum = 0; // valuesµÄºÍ
	for (int i = 0; i < _values.size(); i++)
	{
		sum += _values[i];
	}

	float top =  _valueScaler.getTop(); 
	float bottom = _valueScaler.getBottom();

	float hight = top - bottom; 
	float current = bottom;

	for (int i = 0; i < _values.size(); i++)
	{
		Fan* fan = new Fan;
		fan->set(0, 360, _colors[i], _center, _radius);
		fan->setLinearScaler(LinearScaler(current, current + _values[i] / sum * hight));
		fan->init();
		_container.add(fan);

		current += _values[i] / sum * hight;
	}
}

_GIS_END