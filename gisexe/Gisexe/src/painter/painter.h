#ifndef _PAINTER_H_
#define _PAINTER_H_

#include "projector.h"

_GIS_BEGIN

class IDSpace // ��ʾ�б�id������������Ψһ��ʾ�б�id
{
public:
	virtual ~IDSpace(); // �ͷ����ɵ���ʾ�б�
	static int next() { return _id++; } // ��ʵ�֣�ֻ�Ӳ���
protected:
	IDSpace() { } // ��ֹ���ɶ���
	static int _id; // ��̬
};

class Painter
{
public:
	Painter();
	virtual ~Painter();

	virtual void init(); // ��ʼ��
		virtual void initList() { } 
		virtual void initHint() { } 

	virtual void paint(); // ����
		virtual void begin() { }
		virtual void render() { }
		virtual void end() { }

	virtual void hint(); // ʰȡ

	virtual void destory(); // ����
	virtual void reset(); // ����
	virtual bool ready() { return false; }

	int getHintID() const { return _hintID; }
	static void setProjector(Projector* projector) { _projector = projector; }
protected:
	bool _isUseList;
	int _listID; // ������ʾ��id
	int _hintID; // ����ʰȡ��id

	static Projector* _projector; // ͶӰxy
};

class PainterContainer
{
public:
	PainterContainer();
	virtual ~PainterContainer();
	
	void paint();
	void hint();
	
	void add(Painter* painter);
	Painter* find(int hintID);
	Painter* get(int i = 0);
	int getHintID(int i = 0);
protected:
	std::vector<Painter*> _painters;
};

_GIS_END

#endif 
