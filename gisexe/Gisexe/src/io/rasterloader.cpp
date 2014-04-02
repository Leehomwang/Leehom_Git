#include <iostream>
#include <fstream>
#include <string>

#include "rasterloader.h"

_GIS_BEGIN

RasterLoader::RasterLoader()
{
  hRaster = new RasterInfo; 
  hRaster->dem = NULL;
}

RasterLoader::~RasterLoader()
{
  if (hRaster) 
  {
    if (hRaster->dem)
    {
      for (int i = 0; i < hRaster->nrows; i++)
      {
        delete [] hRaster->dem[i];
      }
      delete [] hRaster->dem;
    }

    delete hRaster;
  }
}

const RasterHandle& RasterLoader::getHandle() const
{
  return hRaster;
}

bool RasterLoader::load( const char* filename )
{
  std::ifstream in(filename); 

  if (!in)
  {
    Console::debug("Raster file open error !\n");
    return false;
  }

  int ncols, nrows;
  double xllcorner, yllcorner, cellsize; 
  int NODATA_value, REPLACE_value; 
  int** dem;

  std::string tmp;
  int low, high; 

  low = high = REPLACE_value = 0; // 初始化，bug...

  in >> tmp >> ncols >> tmp >> nrows >> 
    tmp >> xllcorner >> tmp >> yllcorner >>
    tmp >> cellsize >> tmp >> NODATA_value;

  // 申请二维数组
  dem = new int* [nrows];

  for (int i = 0; i < nrows; i++)
  {
    dem[i] = new int [ncols];
  }

  int z;
  // 读入
  for (int i = 0; i < nrows; i++)
  {
    for (int j = 0; j < ncols; j++)
    {
      in >> z;

      if (z != NODATA_value)
      {
        low = std::min<int>(z, low);
        high = std::max<int>(z, high);

        dem[i][j] = z;
      } else
      {
        dem[i][j] = REPLACE_value; 
      }
    }
  }

  in.close();

  float dv[] = 
  {
    xllcorner, xllcorner + (ncols - 1) * cellsize,
    yllcorner, yllcorner + (nrows - 1) * cellsize, 
    low, high 
  };

  _bbox = BBox(dv);

  hRaster->ncols = ncols;
  hRaster->nrows = nrows;
  hRaster->xllcorner = xllcorner;
  hRaster->yllcorner = yllcorner;
  hRaster->cellsize = cellsize;
  hRaster->NODATA_value = NODATA_value;
  hRaster->REPLACE_value = REPLACE_value;
  hRaster->dem = dem;

  return true;
}

_GIS_END

