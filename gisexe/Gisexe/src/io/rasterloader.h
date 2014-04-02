#ifndef _RASTERLOADER_H_
#define _RASTERLOADER_H_

#include "loader.h"

_GIS_BEGIN

struct RasterInfo
{
  int ncols, nrows; 
  double xllcorner, yllcorner, cellsize; 
  int NODATA_value, REPLACE_value; 

  int** dem;
};

typedef RasterInfo* RasterHandle;

class RasterLoader : public GeometryLoader
{
public:
  RasterLoader();
  virtual ~RasterLoader();

  virtual bool load(const char* filename);
  const RasterHandle& getHandle() const;
protected:
  RasterHandle hRaster;
};

_GIS_END

#endif




/*
class RasterLoader : public GeometryLoader
{
public:
  RasterLoader();
  virtual ~RasterLoader();

  virtual bool load(const char* filename);

  int getNCols() const;
  int getNRows() const;
  double getXLLCorner() const;
  double getYLLCorner() const;
  double getCellsize() const;
  double getNoDataValue() const;

  int getLow() const;
  int getHigh() const;
  int getReplaceValue() const;
  int** getDem() const;
protected:
  int _ncols, _nrows; // 数据行列
  double _xllcorner, _yllcorner, _cellsize; // 左上角x,y坐标和每个点之间的差
  int NODATA_value, REPLACE_value; // 无意义的顶点值

  int** _dem; // 二维指针，数据存储
};*/

//class Loader
//{
//public:
//  static bool loadShpFile(const char* filename, ShpRaw* raw);
//  static bool loadDbfFile(const char* filename, DbfRaw* raw);
//  static bool loadRasterFile(const char* filename, RasterRaw* raw);
//};



//class ShpLoader : public GeometryLoader
//{
//public:
//  enum ShpType
//  {
//    POINT = 1, ARC = 3, POLYGON = 5
//  };
//
//  ShpLoader();
//  virtual ~ShpLoader();
//
//  virtual bool load(const char* filename);
//  ShpType getType() const;
//  std::vector<Point3dv> getPoints() const;
//
//protected:
//  ShpType _type;
//  std::vector<Point3dv> _points;
//  SHPHandle hSHP;
//};



/*
  template <class T>
  std::vector<T> getValues(const char* fieldname) const
  {
    std::vector<T> tmp;

    int count = DBFGetRecordCount(hDBF); // 得到行数
    int index = DBFGetFieldIndex(hDBF, fieldname); // 得到列下标

    if (index == -1) // 如果没有这列
    {
      Console::log("dbf field name not exists");
    }

    T (*fun) (DBFHandle, int, int); // 函数指针

    if (!strcmp(typeid(T).name(), typeid(double).name())) // 判断类型
    {
      fun = DBFReadDoubleAttribute;
    } else if (!strcmp(typeid(T).name(), typeid(int).name())) 
    {
      fun = DBFReadIntegerAttribute;
    } else if (!strcmp(typeid(T).name(), typeid(const char*).name())) 
    {
      fun = DBFReadStringAttribute;
    } else
    {
      Console::log("type not yet supported");
    }

    for (int i = 0; i < count; i++)
    {
      tmp.push_back(fun(hDBF, i, index));
    }

    return tmp;
  }*/


/*

class Loader
{
public:
virtual bool load(const char* filename) = 0;
virtual void create() = 0;
};

class GeometryLoader : public Loader
{
public:
BoundingBox getBBox() const;
GeometryDataSet getGeometryDataSet() const;
protected:
BoundingBox _bbox;
GeometryDataSet _dataset;
};

class StatisticLoader : public Loader
{
public:
void setFieldNames(const std::vector<std::string>& names);
StatisticDataSet getStatisticDataSet() const;
protected:
StatisticDataSet _dataset;
};

class ShpLoader : public GeometryLoader
{
public:
ShpLoader();
virtual ~ShpLoader();

virtual bool load(const char* filename);
virtual void create();
protected:
SHPHandle hSHP;
};

class DbfLoader : public StatisticLoader
{
public:
DbfLoader();
virtual ~DbfLoader();

virtual bool load(const char* filename);
virtual void create();
protected:
std::vector<double> getValues(const char* fieldname) const;

DBFHandle hDBF;
};

class RasterLoader : public GeometryLoader
{
public:
RasterLoader();
virtual ~RasterLoader();

virtual bool load(const char* filename);
virtual void create();
protected:
Vertex3dv getVertex(int row, int col) const;

int _nCols, _nRows; // 数据行列
double _xllcorner, _yllcorner, _cellsize; // 左上角x,y坐标和每个点之间的差
int NODATA_value, REPLACE_value; // 无意义的顶点值

int** _dem; // 二维指针，数据存储
};
*/