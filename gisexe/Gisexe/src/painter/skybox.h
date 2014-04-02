#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "painter.h"
#include "../parameter/parameter.h"

_GIS_BEGIN

class SkyBox : public Painter
{
public:
	virtual void initList();
	virtual void begin();
	virtual void end();
protected:
};

_GIS_END

#endif