#include <iostream>
#include <fstream>
#include <string>

#include "shploader.h"

_GIS_BEGIN

ShpLoader::ShpLoader()
{
  hSHP = NULL;
}

ShpLoader::~ShpLoader()
{
  if(hSHP != NULL)
  {
    SHPClose(hSHP);
  }
}

bool ShpLoader::load( const char* filename )
{
  hSHP = SHPOpen(filename, "rb");

	if (hSHP == NULL)
	{
		return false;
	}

  float d6[] = 
  {
    hSHP->adBoundsMin[0], hSHP->adBoundsMax[0],
    hSHP->adBoundsMin[1], hSHP->adBoundsMax[1], 
    hSHP->adBoundsMin[2], hSHP->adBoundsMax[2], 
  };

  _bbox = BBox(d6);

  return true;
}

const SHPHandle& ShpLoader::getHandle() const
{
  return hSHP;
}

_GIS_END


