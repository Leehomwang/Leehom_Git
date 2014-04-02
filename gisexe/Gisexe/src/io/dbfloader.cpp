#include <iostream>
#include <fstream>
#include <string>

#include "dbfloader.h"

_GIS_BEGIN

DbfLoader::DbfLoader()
{
  hDBF = NULL;
}

DbfLoader::~DbfLoader()
{
  if(hDBF != NULL)
  {
    DBFClose(hDBF);
  }
}

bool DbfLoader::load( const char* filename )
{
  hDBF = DBFOpen(filename, "rb");

  if (hDBF == NULL)
  {
    return false;
  }

  return true;
}

const DBFHandle& DbfLoader::getHandle() const
{
  return hDBF;
}

_GIS_END

