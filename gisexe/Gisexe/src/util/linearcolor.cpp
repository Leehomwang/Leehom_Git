#include "linearcolor.h"

_GIS_BEGIN

LinearColor::LinearColor()
{
	setBound(0, 0);

	//float w[] = {1, 1, 1}; // ��
	//float r[] = {1, 0, 0}; // ��
	//float y[] = {1, 1, 0}; // ��
	//float g[] = {0, 1, 0}; // ��
	//float b[] = {0, 0, 1}; // ��

	std::vector<float3> c;

	c.push_back(C5); // ��
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

	setSegment(); // _colors�����仯������
}

float3 LinearColor::operator()( float value /* = 0 */ ) const
{
	float3 tmp = _colors.front(); // Ĭ����ɫ

	if (_colors.size() != 1 && _min != _max) // �������һ����ɫ�������½�ֵ��ͬ
	{
		int i = (value - _min) / _segment; // ���ȡ��
		float ratio = (value - _min - _segment * i) / _segment; // ȡ�������

		if (0 <= i && i < _colors.size() - 1) // i������ȷ��Χ�ڣ�ע��i == _colors.size() - 1ʱ��ӳ�䵽���ֵ
		{
			tmp = _colors[i] + (_colors[i + 1] - _colors[i]) * ratio;
		}
	} 

	return tmp;
}

_GIS_END
