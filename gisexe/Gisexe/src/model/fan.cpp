#include "../util/util.h"
#include "fan.h"

_GIS_BEGIN

void Fan::set( float start, float end, const float3& color, const float3& center, float radius /*= 1.0f*/, float slice /*= 1*/ )
{
	_start = start;
	_end = end;
	_color = color;
	_radius = radius;
	_slice = slice;
	_center = center; 
}

void Fan::init()
{
	std::vector<float3> vertices;

	float top =  _valueScaler.getTop(); 
	float bottom = _valueScaler.getBottom();

	_center[2] = top;
	//_center = (*_projector)(_center);

	int time = (_end - _start) / _slice; 

	float ct[] = { 0, 0, top}; 
	float cb[] = { 0, 0, bottom}; 

	vertices.push_back(ct); 
	vertices.push_back(cb);

	float v0[] =
	{
		cos(angle2radian(_start)),
		sin(angle2radian(_start)),
		bottom
	};
	vertices.push_back(v0);

	vertices.push_back(ct); 
	vertices.push_back(v0);
	v0[2] = top;
	vertices.push_back(v0);

	for (int i = 0; i < (int)time; i++) 
	{
	  vertices.push_back(ct); 
		
		float v1[] =
		{
			cos(angle2radian(_start + i * _slice)),
			sin(angle2radian(_start + i * _slice)),
			top
		};
		vertices.push_back(v1);

		float v2[] = 
		{
			cos(angle2radian(_start + (i + 1) * _slice)),
			sin(angle2radian(_start + (i + 1) * _slice)),
			top
		};
		vertices.push_back(v2);
		
		vertices.push_back(v1); 
		v1[2] = bottom;
		vertices.push_back(v1);
		vertices.push_back(v2);

		vertices.push_back(v1);
		v2[2] = bottom;
		vertices.push_back(v2);
		v2[2] = top;
		vertices.push_back(v2);
	}

	float v3[] = 
	{
		cos(angle2radian(_end)),
		sin(angle2radian(_end)),
		top
	};
	vertices.push_back(v3);
	v3[2] = bottom;
	vertices.push_back(v3);
	vertices.push_back(cb);
	
	v3[2] = top; 
	vertices.push_back(v3);
	vertices.push_back(cb);
	vertices.push_back(ct);

	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i][0] *= _radius; 
		vertices[i][1] *= _radius;

		vertices[i][0] += _center[0];
		vertices[i][1] += _center[1];
	}

	std::vector<float3> colors(vertices.size(), _color); 
	Mesh* mesh = new Mesh;
	mesh->set(vertices, colors);
	_container.add(mesh);
}

_GIS_END