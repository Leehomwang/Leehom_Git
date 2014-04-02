#include <gl/glew.h>
#include "sphere.h"

_GIS_BEGIN

Sphere::Sphere( const float3& center, const float3& color, int level /*= 2*/ )
{
	set(center, color, level);
}

void Sphere::set( const float3& center, const float3& color, int level /*= 2*/ )
{
	_center = center; 
	_color = color;
	_level = level;

	_vertices.clear();
	_normals.clear();
	destory();
}

void Sphere::initList()
{
	if (_vertices.empty())
	{
		compute();
	}

	glColor3fv(_color.c_ptr());

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < _vertices.size(); i++) // 遍历三角形下标
	{
		glNormal3fv(_normals[i].c_ptr());
		glVertex3fv(_vertices[i].c_ptr());
	}
	glEnd();
}

void Sphere::initHint()
{
	if (_vertices.empty())
	{
		compute();
	}

	glColor3ub((_hintID) % 256, (_hintID >> 8) % 256, (_hintID >> 16) % 256); 

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < _vertices.size(); i++) // 遍历三角形下标
	{
		glVertex3fv(_vertices[i].c_ptr());
	}
	glEnd();
}

void Sphere::compute()
{
	float top =  _valueScaler.getTop(); 
	float bottom = _valueScaler.getBottom();
	_radius = (top - bottom) / 2; 
	_center[2] = bottom + (top - bottom) / 2;

	_center =  (*_projector)(_center); 

	const float X = .525731112;
	const float Z = .850650808;

	const float vs[12][3] = 
	{
		{-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
		{0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
		{Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
	};

	int ts[20][3] = 
	{
		{1,4,0}, {4,9,0}, {4,5,9}, {8,5,4}, {1,8,4},
		{1,10,8}, {10,3,8}, {8,3,5}, {3,2,5}, {3,7,2},
		{3,10,7}, {10,6,7}, {6,11,7}, {6,0,11}, {6,1,0},
		{10,1,6}, {11,0,9}, {2,11,9}, {5,2,9}, {11,2,7}
	};

	for (int i = 0; i < 20; i++) 
	{
		subdivide(vs[ts[i][0]], vs[ts[i][1]], vs[ts[i][2]], _level);
	}
}

void Sphere::subdivide( const float* v1, const float* v2, const float* v3, int level )
{
	if (level--) 
	{
		float v12[3], v23[3], v31[3];

		for (int i = 0; i < 3; i++)
		{
			v12[i] = (v1[i] + v2[i]) / 2.0;
			v23[i] = (v2[i] + v3[i]) / 2.0;
			v31[i] = (v3[i] + v1[i]) / 2.0;
		}
		normalize(v12);
		normalize(v23);
		normalize(v31);

		subdivide(v1, v12, v31, level);
		subdivide(v2, v23, v12, level);
		subdivide(v3, v31, v23, level);
		subdivide(v12, v23, v31, level);
	}
	else 
	{
		_normals.push_back(v1);
		_normals.push_back(v2);
		_normals.push_back(v3);

		float3 v;
		v = v1;
		_vertices.push_back(_center + v * _radius);
		v = v2;
		_vertices.push_back(_center + v * _radius);
		v = v3;
		_vertices.push_back(_center + v * _radius);
	}
}

void Sphere::normalize( float* v )
{
	float d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] /= d;
	v[1] /= d;
	v[2] /= d;
}

void Sphere::setLinearScaler( const LinearScaler& scaler )
{
	_valueScaler = scaler;
}

_GIS_END