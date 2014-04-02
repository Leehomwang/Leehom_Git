/*
#include <gl/glew.h>
#include "painter.h"

_GIS_BEGIN

int IDSpace::_id = 1; // ��1��ʼ

IDSpace::~IDSpace() // ͳһ�ͷ���ʾ�б�
{
	for (int id = _id; id > 0; id--)
	{
		if (glIsList(id))
		{
			glDeleteLists(id, 1);
		}
	}
}

//Projector* Painter::_projector = NULL;
//
//Painter::Painter()
//{
//	_paintID = IDSpace::next();
//	_hintID = IDSpace::next(); 
//}
//
//Painter::~Painter()
//{
//	//if (_projector) // ����Ļ��̳�Painter�������ʱ���������ͻ��_projector�ͷ���
//	//{
//	//	delete _projector;
//	//	_projector = NULL;
//	//}
//	destory();
//}
//
//void Painter::destory()
//{
//	if (glIsList(_paintID))
//	{
//		glDeleteLists(_paintID, 1);
//	}
//	if (glIsList(_hintID))
//	{
//		glDeleteLists(_hintID, 1);
//	}
//}
//
//
//void Painter::callPaint()
//{
//	if (glIsList(_paintID))
//	{
//		beginPaint();
//		glCallList(_paintID);
//		endPaint();
//	}
//	else
//	{
//		glNewList(_paintID, GL_COMPILE);
//		initPaint();
//		glEndList();
//	}
//}
//
//void Painter::callHint()
//{
//	if (glIsList(_hintID))
//	{
//		beginHint();
//		glCallList(_hintID);
//		endHint();
//	}
//	else
//	{
//		glNewList(_hintID, GL_COMPILE);
//		initHint();
//		glEndList();
//	}
//}

///////////////////////////////////////////////////////////////////////////////
Projector* Painter::_projector = NULL;

Painter::Painter()
{
	_paintID = _hintID = 0;
}
///////////////////////////////////////////////////////////////////////////////
void JustPainter::init()
{
	initPaint(); // ��д�ĸ�������
	initHint();
}

void JustPainter::paint()
{
	if (ready())
	{
		begin();
		render();
		end();
	}
	else
	{
		init();
	}
}

///////////////////////////////////////////////////////////////////////////////
ListPainter::ListPainter()
{
	_paintID = IDSpace::next();
	_hintID = IDSpace::next(); 
}

ListPainter::~ListPainter()
{
	destory();
}

void ListPainter::destory() // ����������ʾ�б�
{
	if (glIsList(_paintID))
	{
		glDeleteLists(_paintID, 1);
	}
	if (glIsList(_hintID))
	{
		glDeleteLists(_hintID, 1);
	}
}

void ListPainter::reset()
{
	destory();
	// ��д�����������
}

void ListPainter::init()
{
	glNewList(_paintID, GL_COMPILE);
	initPaint();
	glEndList();

	glNewList(_hintID, GL_COMPILE);
	initHint();
	glEndList();
}

void ListPainter::paint()
{
	if (ready())
	{
		begin();
		render();
		glCallList(_paintID);
		end();
	}
	else
	{
		init();
	}
}

void ListPainter::hint()
{
	if (ready())
	{
		glCallList(_hintID);
	}
	else
	{
		init();
	}
}

bool ListPainter::ready()
{
	return (glIsList(_paintID) && glIsList(_hintID)); // ����������ʾ�б��Ƿ��ʼ�����
}


_GIS_END
*/