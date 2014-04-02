#include <iostream>
#include <fstream>
#include <string>

#include "loader.h"

_GIS_BEGIN

BBox GeometryLoader::getBBox() const
{
  return _bbox;
}

_GIS_END


