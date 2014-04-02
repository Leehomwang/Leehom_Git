#include <gl/glew.h>
#include "painter.h"

_GIS_BEGIN

int IDSpace::_id = 1; // 从1开始

IDSpace::~IDSpace() 
{
	for (int id = _id; id > 0; id--)
	{
		if (glIsList(id))
		{
			glDeleteLists(id, 1);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

Projector* Painter::_projector = NULL;

Painter::Painter()
{
	_isUseList = true;
	_listID = IDSpace::next();
	_hintID = IDSpace::next();
}

Painter::~Painter()
{
	destory();
}

void Painter::destory() // 销毁两个显示列表
{
	if (glIsList(_listID))
	{
		glDeleteLists(_listID, 1);
	}
	if (glIsList(_hintID))
	{
		glDeleteLists(_hintID, 1);
	}
}

void Painter::reset()
{
	destory();
}

void Painter::init()
{
	glNewList(_listID, GL_COMPILE);
	initList();
	glEndList();

	glNewList(_hintID, GL_COMPILE);
	initHint();
	glEndList();
}

void Painter::paint()
{
	if (glIsList(_listID) && glIsList(_hintID) || ready())
	{
		begin();
		render();
		if (_isUseList)
		{
			glCallList(_listID);
		}
		end();
	}
	else
	{
		init();
	}
}

void Painter::hint()
{
	if (glIsList(_listID) && glIsList(_hintID))
	{
		glCallList(_hintID);
	}
	else
	{
		init();
	}
}

///////////////////////////////////////////////////////////////////////////////

PainterContainer::PainterContainer()
{
	
}

PainterContainer::~PainterContainer()
{
	for (int i = 0; i < _painters.size(); i++)
	{
		delete _painters[i];
	}
}

void PainterContainer::add( Painter* painter )
{
	_painters.push_back(painter);
}

Painter* PainterContainer::find( int hintID )
{
	for (int i = 0; i < _painters.size(); i++)
	{
		if (_painters[i]->getHintID() == hintID)
		{
			return _painters[i];
		}
	}
	return NULL;
}

void PainterContainer::paint()
{
	for (int i = 0; i < _painters.size(); i++)
	{
		_painters[i]->paint();
	}
}

void PainterContainer::hint()
{
	for (int i = 0; i < _painters.size(); i++)
	{
		_painters[i]->hint();
	}
}

int PainterContainer::getHintID( int i /*= 0*/ )
{
	if (0 <= i && i < _painters.size())
	{
		return _painters[i]->getHintID();
	}
	else
	{
		return -1;
	}
}

Painter* PainterContainer::get( int i )
{
	if (0 <= i && i < _painters.size())
	{
		return _painters[i];
	}
	else
	{
		return NULL;
	}
}

_GIS_END