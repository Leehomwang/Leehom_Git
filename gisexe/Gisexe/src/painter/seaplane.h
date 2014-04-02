#ifndef _SEAPLANE_H_
#define _SEAPLANE_H_

#include "painter.h"

_GIS_BEGIN

class SeaPlane : public Painter
{
public:
	virtual void initList();
	virtual void begin();
	virtual void end();
protected:
};

_GIS_END

#endif