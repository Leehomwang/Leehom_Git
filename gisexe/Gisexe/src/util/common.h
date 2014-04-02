#ifndef _COMMON_H_
#define _COMMON_H_

#if defined(__cplusplus)
#define _GIS_BEGIN	namespace gis {
#define _GIS_END		}
#define _GIS	::gis::
#else
#define _GIS_BEGIN
#define _GIS_END
#define _GIS
#endif

#include "console.h"

#endif