#ifndef MYTRI_H
#define MYTRI_H

#include <vector>
#include "../../util/vec.h"

_GIS_BEGIN

class MyTri
{
public:
	static void triangulate(
		const std::vector<double2>& polygon, // 2d����ζ�������
		std::vector<double2>& triangles); // �����ζ������飬ÿ������һ�������ζ�������

	static void subdivide(
		std::vector<double2>& triangles, float maxLen = 15.f); // ������ϸ�֣�ʹ���߳�С��maxLen
};

_GIS_END

#endif