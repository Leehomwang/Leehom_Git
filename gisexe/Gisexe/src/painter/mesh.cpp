#include <gl/glew.h>
#include <map>
#include "../util/util.h"
#include "mesh.h"

_GIS_BEGIN

void Mesh::set( const std::vector<float3>& vertices, const std::vector<float3>& colors )
{
	reset();
	
	_vertices = (*_projector)(vertices); 
	_colors = colors;
}

void Mesh::set( const std::vector<float3>& vertices, const std::vector<float3>& normals, 
							 const std::vector<float3>& colors, const std::vector<int3>& indices )
{
	reset();

	_vertices = vertices;
	_normals = normals;
	_colors = colors;
	_indices = indices;
}

void Mesh::initList()
{
	if (_indices.empty())
	{
		compute();
	}

	glBegin(GL_TRIANGLES);
	//glBegin(GL_LINES);
	for (int i = 0; i < _indices.size(); i++) // 遍历三角形下标
	{
		for (int j = 0; j < 3; j++) // 三角形顶点下标
		{
			int idx = _indices[i][j]; // 下标
			glColor3fv(_colors[idx].c_ptr());
			glNormal3fv(_normals[idx].c_ptr());
			glVertex3fv(_vertices[idx].c_ptr());
		}
	}
	glEnd();
}

void Mesh::initHint()
{
	if (_indices.empty())
	{
		compute();
	}

	glColor3ub((_hintID) % 256, (_hintID >> 8) % 256, (_hintID >> 16) % 256); 
	Console::debug("%d %d %d\n", (_hintID) % 256, (_hintID >> 8) % 256, (_hintID >> 16) % 256);

	glBegin(GL_TRIANGLES);
	//glBegin(GL_LINES);
	for (int i = 0; i < _indices.size(); i++) // 遍历三角形下标
	{
		for (int j = 0; j < 3; j++) // 三角形顶点下标
		{
			int idx = _indices[i][j]; // 下标
			glVertex3fv(_vertices[idx].c_ptr());
		}
	}
	glEnd();
}

void Mesh::compute()
{
	std::vector<float3> vertices;
	std::vector<float3> colors; 
	std::vector<std::vector<float3> > normals; 
	std::map<float3, int> locator;

	for (int i = 0; i < _vertices.size(); i += 3) // 遍历点，每三个是一个三角形
	{
		float3 n = triangle_normal(_vertices[i], _vertices[i + 1], _vertices[i + 2]); // 计算这个三角形的法向
		int3 idx3; // 这个三角形的顶点在vertices中的下标

		for (int j = 0; j < 3; j++) 
		{
			float3 v = _vertices[i + j]; 
			float3 c = _colors[i + j];

			if (locator.find(v) == locator.end()) 
			{
				locator[v] = vertices.size();
				idx3[j] = vertices.size(); 

				vertices.push_back(v);
				colors.push_back(c);

				std::vector<float3> vec; 
				vec.push_back(n); 
				normals.push_back(vec); 
			}
			else
			{
				idx3[j] = locator[v];
				normals[idx3[j]].push_back(n);
			}
		}

		_indices.push_back(idx3); 
	}

	_normals.resize(normals.size());
	for (int i = 0; i < normals.size(); i++)
	{
		float3 n;
		int length = normals[i].size();
		for (int j = 0; j < length; j++)
		{
			n += normals[i][j];
		}
		n /= length;
		_normals[i] = n;
	}

	_vertices = vertices; // 替换
	_colors = colors;
}

void Mesh::reset()
{
	destory();
	_vertices.clear();
	_normals.clear();
	_colors.clear();
	_indices.clear();
}

_GIS_END