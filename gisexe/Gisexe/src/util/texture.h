#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "common.h"
#include <gl/glaux.h>

_GIS_BEGIN

AUX_RGBImageRec* LoadBMP(const char *Filename); // ��Ҫlink���glaux.lib

GLuint loadTexture(const char* Filename);

_GIS_END

#endif