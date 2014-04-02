#include "seidel/mytri.h"
#include "ladder.h"

_GIS_BEGIN

void Ladder::setContour( const std::vector<double2>& contour )
{
	_contour = contour;
}

void Ladder::setColor( const float3& color )
{
	_color = color;
}

void Ladder::init()
{
	std::vector<double2> triangles2d;

	MyTri::triangulate(_contour, triangles2d); 
	MyTri::subdivide(triangles2d); //µÃµ½triangles

	std::vector<float3> vertices;
	
	float top =  _valueScaler.getTop(); 
	float bottom = _valueScaler.getBottom();

	float v[] = { 0, 0, top }; 
	
	for (int i = 0; i < triangles2d.size(); i++) 
	{
		v[0] = triangles2d[i][0];
		v[1] = triangles2d[i][1];

		vertices.push_back(v);
	}

	for (int i = 0; i < _contour.size() - 1; i++) 
	{
		v[0] = _contour[i][0];
		v[1] = _contour[i][1];
		v[2] = top;
		vertices.push_back(v);

		v[0] = _contour[i][0];
		v[1] = _contour[i][1];
		v[2] = bottom;
		vertices.push_back(v);

		v[0] = _contour[i + 1][0];
		v[1] = _contour[i + 1][1];
		v[2] = top;
		vertices.push_back(v);

		v[0] = _contour[i + 1][0];
		v[1] = _contour[i + 1][1];
		v[2] = top;
		vertices.push_back(v);

		v[0] = _contour[i][0];
		v[1] = _contour[i][1];
		v[2] = bottom;
		vertices.push_back(v);

		v[0] = _contour[i + 1][0];
		v[1] = _contour[i + 1][1];
		v[2] = bottom;
		vertices.push_back(v);
	}

	std::vector<float3> colors(vertices.size(), _color);
	
	Mesh* mesh = new Mesh;
	mesh->set(vertices, colors);
	_container.add(mesh);
}

_GIS_END