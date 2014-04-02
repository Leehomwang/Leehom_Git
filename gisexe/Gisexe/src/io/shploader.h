#ifndef _SHPLOADER_H_
#define _SHPLOADER_H_

#include "shp/shapefil.h"
#include "loader.h"

_GIS_BEGIN

class ShpLoader : public GeometryLoader
{
public:
  ShpLoader();
  virtual ~ShpLoader();

  virtual bool load(const char* filename);
  const SHPHandle& getHandle() const;
protected:
  SHPHandle hSHP;
};

_GIS_END

#endif