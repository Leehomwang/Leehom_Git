#ifndef LOADER_H
#define LOADER_H

#include <vector>

#include "../util/vec.h"

_GIS_BEGIN

class Loader
{
public:
  virtual bool load(const char* filename) = 0;
};

class GeometryLoader : public Loader
{
public:
  BBox getBBox() const;
protected:
  BBox _bbox;
};

class StatisticLoader : public Loader
{

};


_GIS_END

#endif


