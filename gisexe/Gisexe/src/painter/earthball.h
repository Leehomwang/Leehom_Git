#ifndef _EARTHBALL_H_
#define _EARTHBALL_H_

#include "painter.h"

_GIS_BEGIN

class EarthBall : public Painter
{
public:
	virtual void initList();
	virtual void begin();
	virtual void end();
protected:
};

_GIS_END

#endif