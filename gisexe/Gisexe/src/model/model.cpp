#include "model.h"

_GIS_BEGIN

Model::Model()
{
	_lastID = 0;
	_isUseList = false;
}

void Model::paint()
{
	begin();
	_container.paint();
	end();
}

void Model::hint() 
{
	_container.hint();
}

void Model::pick( int x, int y )
{

}

int Model::getHintID()
{
	return _container.getHintID(0);
}

void Model::setLinearScaler( const LinearScaler& scaler )
{
	_valueScaler = scaler;
}

_GIS_END

