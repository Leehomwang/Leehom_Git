#include "interface.h"
#include "triangulate.h"
#include "mytri.h"

_GIS_BEGIN

void MyTri::triangulate( const std::vector<double2>& polygon, 
												std::vector<double2>& triangles)
{
	int verts_size = polygon.size(); // 多边形顶点数，多边形首尾重合
	if (verts_size > SEGSIZE) // 多边形顶点数多于固定分配的数组大小
	{
		Console::log("polygon size too big");
		return;
	}

	int counter_number = 1; // 多边形数
	int verts_in_counter[] = { verts_size - 1 }; // 多边形顶点数，下标0处的点不用
	double verts[SEGSIZE][2]; // 固定长度数组

	for (int i = 0; i < verts_size; i++) // 从下标0的被忽略了，因为是首尾重叠的，所以无所谓
	{
		verts[i][0] = polygon[i][0]; // 复制2d顶点坐标
		verts[i][1] = polygon[i][1];
	}
	
	int tris_size = verts_size - 1 - 2; // 没有洞的话，是这个公式
	int tris[SEGSIZE][3];

	triangulate_polygon(counter_number, verts_in_counter, verts, tris); // 多边形化

	triangles.clear(); // 这里会清空
	for (int i = 0; i < tris_size; i++)
	{
		for (int j = 0; j < 3; j++) // 三个下标，每个三角形产生3个顶点
		{
			triangles.push_back(polygon[tris[i][j]]);
		}
	}
}

void MyTri::subdivide( std::vector<double2>& triangles, float maxLen )
{
	std::vector<double2> result;

	for (int i = 0; i < triangles.size(); i += 3)
	{
		double2 v[3];
		for (int j = 0; j < 3; j++) // 这个三角形三顶点
		{
			v[j] = triangles[i + j];
		}

		double longest = std::max<double> ((v[0] - v[1]).magnitude(), (v[1] - v[2]).magnitude());
		longest = std::max<double> (longest, (v[0] - v[2]).magnitude());

		if (longest > maxLen) // 最长边不满足要求
		{
			double2 m[3];
			m[0] = (v[0] + v[1]) / 2;
			m[1] = (v[1] + v[2]) / 2;
			m[2] = (v[0] + v[2]) / 2;
			
			triangles.push_back(v[0]);
			triangles.push_back(m[0]);
			triangles.push_back(m[2]);

			triangles.push_back(v[1]);
			triangles.push_back(m[1]);
			triangles.push_back(m[0]);

			triangles.push_back(v[2]);
			triangles.push_back(m[2]);
			triangles.push_back(m[1]);

			triangles.push_back(m[0]);
			triangles.push_back(m[1]);
			triangles.push_back(m[2]);
		}
		else // 满足要求
		{
			for (int j = 0; j < 3; j++)
			{
				result.push_back(v[j]);
			}
		}
	}

	triangles = result;
}

_GIS_END