#include "linearcolor.h"

_GIS_BEGIN

LinearColor::LinearColor()
{
	setBound(0, 0);

	//float w[] = {1, 1, 1}; // 白
	//float r[] = {1, 0, 0}; // 红
	//float y[] = {1, 1, 0}; // 黄
	//float g[] = {0, 1, 0}; // 绿
	//float b[] = {0, 0, 1}; // 蓝

	std::vector<float3> c;

	c.push_back(C5); // 蓝
	c.push_back(C4);
	c.push_back(C3);
	c.push_back(C2);
	c.push_back(C1);

	setColors(c);
}

void LinearColor::setBound( float min, float max )
{
	_min = min;
	_max = max;

	setSegment();
}

void LinearColor::setSegment()
{
	if (_colors.size() > 1)
	{
		_segment = (_max - _min) / (_colors.size() - 1);
	}
}

void LinearColor::setColors( const std::vector<float3>& colors )
{
	_colors = colors;

	setSegment(); // _colors发生变化，重设
}

float3 LinearColor::operator()( float value /* = 0 */ ) const
{
	float3 tmp = _colors.front(); // 默认颜色

	if (_colors.size() != 1 && _min != _max) // 如果不是一个颜色，且上下界值不同
	{
		int i = (value - _min) / _segment; // 相除取整
		float ratio = (value - _min - _segment * i) / _segment; // 取余算比例

		if (0 <= i && i < _colors.size() - 1) // i落在正确范围内，注意i == _colors.size() - 1时即映射到最大值
		{
			tmp = _colors[i] + (_colors[i + 1] - _colors[i]) * ratio;
		}
	} 

	return tmp;
}

_GIS_END
