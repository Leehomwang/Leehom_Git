#ifndef _CHINARASTERMODEL_H_
#define _CHINARASTERMODEL_H_

#include "model.h"
#include "../io/rasterloader.h"
#include "../util/linearcolor.h"

_GIS_BEGIN

class ChinaRasterModel : public Model
{
public:
	ChinaRasterModel();
	virtual ~ChinaRasterModel();

	virtual void init(); 
	virtual void begin();
	virtual void end();

	void setRasterLoader(RasterLoader* rasterLoader); 
	void setColorMap(const std::vector<float3>& colors); 
	void setDemHScaler(float hScaler); 
protected:
	void computeVertices(); 
	void computeColors(); 
	void computeTriangleNormals(); 
	void computeNormals(); 
	void computeIndices(); 
	float3 getVertex(int i, int j) const;

	float3 computeTriangleNormal(int i0, int j0, int i1, int j1, int i2, int j2) const; 
	float3 getTriangleNormal(int i0, int j0, int i1, int j1, int i2, int j2) const;

	float3 computeVertexNormal(int i, int j) const;
	int getVertexIndex(int i, int j) const;
	int3 getTriangleVertexIndices(int i0, int j0, int i1, int j1, int i2, int j2) const;
	
	RasterLoader* _rasterLoader;
	LinearColor _linearColor;

	std::vector<float3> _vertices; 
	std::vector<float3> _colors;
	std::vector<float3> _normals;
	std::vector<int3> _indices; 
	float3* _triangleNormals; 

	int _nRows;
	int _nCols;
};


_GIS_END

#endif