#ifndef _MODEL_H_
#define _MODEL_H_

#include "../painter/mesh.h"

_GIS_BEGIN

class Model : public Painter
{
public:
	Model();

	virtual void paint(); 
	virtual void hint();

	int getHintID();

	virtual void pick(int x, int y); 

	void setLinearScaler(const LinearScaler& scaler);
protected:
	int _lastID; 
	PainterContainer _container;
	LinearScaler _valueScaler;
};

_GIS_END
#endif

