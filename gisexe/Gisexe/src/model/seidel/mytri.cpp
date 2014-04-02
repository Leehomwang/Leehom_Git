#include "interface.h"
#include "triangulate.h"
#include "mytri.h"

_GIS_BEGIN

void MyTri::triangulate( const std::vector<double2>& polygon, 
												std::vector<double2>& triangles)
{
	int verts_size = polygon.size(); // ����ζ��������������β�غ�
	if (verts_size > SEGSIZE) // ����ζ��������ڹ̶�����������С
	{
		Console::log("polygon size too big");
		return;
	}

	int counter_number = 1; // �������
	int verts_in_counter[] = { verts_size - 1 }; // ����ζ��������±�0���ĵ㲻��
	double verts[SEGSIZE][2]; // �̶���������

	for (int i = 0; i < verts_size; i++) // ���±�0�ı������ˣ���Ϊ����β�ص��ģ���������ν
	{
		verts[i][0] = polygon[i][0]; // ����2d��������
		verts[i][1] = polygon[i][1];
	}
	
	int tris_size = verts_size - 1 - 2; // û�ж��Ļ����������ʽ
	int tris[SEGSIZE][3];

	triangulate_polygon(counter_number, verts_in_counter, verts, tris); // ����λ�

	triangles.clear(); // ��������
	for (int i = 0; i < tris_size; i++)
	{
		for (int j = 0; j < 3; j++) // �����±꣬ÿ�������β���3������
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
		for (int j = 0; j < 3; j++) // ���������������
		{
			v[j] = triangles[i + j];
		}

		double longest = std::max<double> ((v[0] - v[1]).magnitude(), (v[1] - v[2]).magnitude());
		longest = std::max<double> (longest, (v[0] - v[2]).magnitude());

		if (longest > maxLen) // ��߲�����Ҫ��
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
		else // ����Ҫ��
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