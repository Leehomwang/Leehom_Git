#ifndef _LADDER_H_
#define _LADDER_H_

#include "model.h"

_GIS_BEGIN

class Ladder : public Model
{
public:
	virtual void init(); 

	void setContour(const std::vector<double2>& contour);
	void setColor(const float3& color);
protected:
	float3 _color;
	std::vector<double2> _contour; 
};

_GIS_END

#endif