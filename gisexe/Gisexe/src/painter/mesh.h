#ifndef _MESH_H_
#define _MESH_H_

#include "painter.h"

_GIS_BEGIN

class Mesh : public Painter
{
public:
	void set(const std::vector<float3>& vertices, 
		const std::vector<float3>& colors);

	void set(const std::vector<float3>& vertices, 
		const std::vector<float3>& normals,
		const std::vector<float3>& colors,
		const std::vector<int3>& indices);

	void setColor(const float3& color); // 单一颜色改变时，mesh不需要重新计算

	virtual void initList();
	virtual void initHint();
	virtual void reset();
protected:
	void compute(); // 计算法向和下标

	std::vector<float3> _colors;
	std::vector<float3> _vertices;
	std::vector<float3> _normals;
	std::vector<int3> _indices;
};

_GIS_END

#endif