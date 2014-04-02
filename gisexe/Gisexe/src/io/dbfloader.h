#ifndef _DBFLOADER_H_
#define _DBFLOADER_H_

#include <vector>

#include "shp/shapefil.h"
#include "loader.h"

_GIS_BEGIN

class DbfLoader : public StatisticLoader
{
public:
  DbfLoader();
  virtual ~DbfLoader();

  virtual bool load(const char* filename);
  const DBFHandle& getHandle() const;
protected:
  DBFHandle hDBF;
};

_GIS_END

#endif


