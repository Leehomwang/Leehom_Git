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

	void setColor(const float3& color); // ��һ��ɫ�ı�ʱ��mesh����Ҫ���¼���

	virtual void initList();
	virtual void initHint();
	virtual void reset();
protected:
	void compute(); // ���㷨����±�

	std::vector<float3> _colors;
	std::vector<float3> _vertices;
	std::vector<float3> _normals;
	std::vector<int3> _indices;
};

_GIS_END

#endif