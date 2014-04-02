#ifndef MYTRI_H
#define MYTRI_H

#include <vector>
#include "../../util/vec.h"

_GIS_BEGIN

class MyTri
{
public:
	static void triangulate(
		const std::vector<double2>& polygon, // 2d多边形顶点序列
		std::vector<double2>& triangles); // 三角形顶点数组，每三个是一个三角形顶点坐标

	static void subdivide(
		std::vector<double2>& triangles, float maxLen = 15.f); // 三角形细分，使最大边长小于maxLen
};

_GIS_END

#endif