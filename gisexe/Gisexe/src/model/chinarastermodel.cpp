#include <gl/glew.h>
#include "../util/util.h"
#include "chinarastermodel.h"

_GIS_BEGIN

ChinaRasterModel::ChinaRasterModel()
{
	_rasterLoader = NULL;
	_triangleNormals = NULL;
}

ChinaRasterModel::~ChinaRasterModel()
{
	if (_rasterLoader)
	{ 
		delete _rasterLoader;
		_rasterLoader = NULL;
	}
	if (_triangleNormals)
	{
		delete _triangleNormals;
		_triangleNormals = NULL;
	}
}

void ChinaRasterModel::setColorMap(const std::vector<float3>& colors)
{
	_linearColor.setColors(colors);

	if (_vertices.size() && _normals.size() && _colors.size() && _indices.size())
	{
		computeColors();
		((Mesh*)_container.get(0))->set(_vertices, _normals, _colors, _indices);
	}
}

void ChinaRasterModel::setDemHScaler( float hScaler )
{
	_valueScaler.setVertical(_valueScaler.getBottom(), 
		_valueScaler.getTop() * hScaler); 
	if (_vertices.size() && _normals.size() && _colors.size() && _indices.size())
	{
		computeVertices();
		computeTriangleNormals();
		computeNormals();
		((Mesh*)_container.get(0))->set(_vertices, _normals, _colors, _indices);
	}
}

void ChinaRasterModel::setRasterLoader( RasterLoader* rasterLoader )
{
	_rasterLoader = rasterLoader;
}

void ChinaRasterModel::init()
{
	const RasterHandle& hRaster = _rasterLoader->getHandle();
	_nRows = hRaster->nrows;
	_nCols = hRaster->ncols;

	computeIndices();//计算所以需要构造三角网的顶点的索引
	computeColors();//计算每个点的颜色

	computeVertices();//计算每个顶点的xy坐标和z高度
	computeTriangleNormals();//得到_triangleNormals
	computeNormals();//得到_normals，_normals是共用该点的所以三角形法向量_triangleNormals的相加平均

	Mesh* mesh = new Mesh;
	mesh->set(_vertices, _normals, _colors, _indices);
	_container.add(mesh);
}

void ChinaRasterModel::computeIndices()
{
	_indices.clear();

	const RasterHandle& hRaster = _rasterLoader->getHandle();

	int** dem = hRaster->dem;
	int REPLACE_value = hRaster->REPLACE_value;

	for (int i = 0; i < _nRows; i++)
	{
		for (int j = 0; j < _nCols; j++)
		{
			if (i == (_nRows - 1) || j == (_nCols - 1) || 
				(dem[i][j] == REPLACE_value &&
				dem[i + 1][j] == REPLACE_value &&
				dem[i][j + 1] == REPLACE_value &&
				dem[i + 1][j + 1] == REPLACE_value)) 
			{
				continue;
			}

			if (dem[i][j] != REPLACE_value ||
				dem[i + 1][j] != REPLACE_value ||
				dem[i + 1][j + 1] != REPLACE_value) 
			{
				_indices.push_back(getTriangleVertexIndices(i, j, i + 1, j, i + 1, j + 1));
			}

			if (dem[i][j] != REPLACE_value ||
				dem[i + 1][j + 1] != REPLACE_value ||
				dem[i][j + 1] != REPLACE_value) 
			{
				_indices.push_back(getTriangleVertexIndices(i, j, i + 1, j + 1, i, j + 1));
			}
		}
	}

}

float3 ChinaRasterModel::getVertex( int i, int j ) const
{
	return _vertices[i * _nCols + j];
}

float3 ChinaRasterModel::computeVertexNormal( int i, int j ) const
{
	float3 tmp;
	int n = 0; 

	if (i - 1 >= 0 && j - 1 >= 0) 
	{
		tmp += getTriangleNormal(i - 1, j - 1, i, j, i - 1, j) + 
			     getTriangleNormal(i - 1, j - 1, i, j - 1, i, j);
		n += 2;
	}

	if (i + 1 < _nRows && j + 1 < _nCols)
	{
		tmp += getTriangleNormal(i, j, i + 1, j, i + 1, j + 1) +
			     getTriangleNormal(i, j, i + 1, j + 1, i, j + 1);
		n += 2;
	}

	if (i - 1 >= 0 && j + 1 < _nCols) 
	{
		tmp += getTriangleNormal(i - 1, j, i, j, i, j + 1);
		n += 1;
	}

	if (i + 1 < _nRows && j - 1 >= 0)
	{
		tmp += getTriangleNormal(i, j - 1, i + 1, j, i, j);
		n += 1;
	}

	return (tmp / n).normalize();
}

float3 ChinaRasterModel::computeTriangleNormal( int i0, int j0, int i1, int j1, int i2, int j2 ) const
{
	return triangle_normal(getVertex(i0, j0), getVertex(i1, j1), getVertex(i2, j2));
}

float3 ChinaRasterModel::getTriangleNormal( int i0, int j0, int i1, int j1, int i2, int j2 ) const
{
	int idx = i0 * (_nCols - 1) * 2 + j0 * 2; 
	if (j0 != j1) 
	{
		idx++;
	}
	return _triangleNormals[idx];
}

int3 ChinaRasterModel::getTriangleVertexIndices( int i0, int j0, int i1, int j1, int i2, int j2 ) const
{
	int3 tmp;
	tmp[0] = getVertexIndex(i0, j0);
	tmp[1] = getVertexIndex(i1, j1);
	tmp[2] = getVertexIndex(i2, j2);
	return tmp;
}

int ChinaRasterModel::getVertexIndex(int i, int j) const
{
	return i * _nCols + j;
}

void ChinaRasterModel::computeColors()
{
	_colors.clear();

	const RasterHandle& hRaster = _rasterLoader->getHandle();

	BBox bbox = _rasterLoader->getBBox(); 
	_linearColor.setBound(bbox[4], bbox[5]);

	for (int i = 0; i < _nRows; i++)
	{
		for (int j = 0; j < _nCols; j++)
		{
			_colors.push_back(_linearColor(hRaster->dem[i][j]));
		}
	}
}

void ChinaRasterModel::computeVertices()
{
	_vertices.clear();

	const RasterHandle& hRaster = _rasterLoader->getHandle();

	BBox bbox = _rasterLoader->getBBox();
	_valueScaler.setBound(bbox[4], bbox[5]); 

	_nRows = hRaster->nrows;
	_nCols = hRaster->ncols;

	float xllcorner = hRaster->xllcorner;
	float yllcorner = hRaster->yllcorner;
	float cellsize = hRaster->cellsize;

	float3 v;

	for (int i = 0; i < _nRows; i++) 
	{
		for (int j = 0; j < _nCols; j++)
		{
			v[0] = xllcorner + j * cellsize;
			v[1] = yllcorner + cellsize * (_nRows - 1) - i * cellsize; 

			v[2] = _valueScaler(hRaster->dem[i][j]);

			_vertices.push_back(v);
		}
	}

	_vertices = (*_projector)(_vertices); 
}

void ChinaRasterModel::computeNormals()
{
	_normals.clear();

	for (int i = 0; i < _nRows; i++) 
	{
		for (int j = 0; j < _nCols; j++)
		{
			_normals.push_back(computeVertexNormal(i, j));
		}
	}
}

void ChinaRasterModel::computeTriangleNormals()
{
	if (_triangleNormals)
	{
		delete _triangleNormals;
	}

	_triangleNormals = new float3[(_nRows - 1) * (_nCols - 1) * 2];
	
	for (int i = 0; i < _nRows - 1; i++) 
	{
		for (int j = 0; j < _nCols - 1; j++)
		{
			int idx = i * (_nCols - 1) * 2 + j * 2; 

			_triangleNormals[idx] = computeTriangleNormal(i, j, i + 1, j, i + 1, j + 1);
			_triangleNormals[idx + 1] = computeTriangleNormal(i, j, i + 1, j + 1, i, j + 1);
		}
	}
}

void ChinaRasterModel::begin()
{
	glEnable(GL_LIGHTING);
}

void ChinaRasterModel::end()
{
	glDisable(GL_LIGHTING);
}

_GIS_END
