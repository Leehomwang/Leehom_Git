/*
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
	virtual void init() = 0; // ��ʼ��
	virtual void initPaint() = 0; // ��ʼ�������б� 
	virtual void initHint() = 0; // ��ʼ��ʰȡ�б�

	virtual void begin() = 0; // ����֮ǰ
	virtual void paint() = 0; // ����
	virtual void render() = 0; // ������
	virtual void end() = 0; // ����֮��
	virtual void hint() = 0; // ʰȡ

	virtual void destory() = 0; // ����
	virtual void reset() = 0; // ����
	virtual bool ready() = 0; // �Ƿ���Ҫ��ʼ��

	int getHintID() const { return _hintID; }
	static void setProjector(Projector* projector) { _projector = projector; }
protected:
	int _paintID; // ������ʾ��id
	int _hintID; // ����ʰȡ��id
	static Projector* _projector; // ͶӰxy
};

class JustPainter : public Painter // ��ʹ����ʾ�б����
{
public:
	virtual void init(); // ��ʼ��
	virtual void initPaint() {} // ��ʼ�������б�Ĭ�ϲ���ʵ��
	virtual void initHint() {} // ��ʼ��ʰȡ�б�Ĭ�ϲ���ʵ��
	virtual void begin() {} // ����֮ǰ
	virtual void paint(); // ����
	virtual void render() {} // ������
	virtual void end() {} // ����֮��
	virtual void hint() {} // ʰȡ
	virtual void destory() {} // ����
	virtual void reset() {} // ����
	virtual bool ready() { return true; }
};

class ListPainter : public Painter // ʹ����ʾ�б����
{
public:
	ListPainter();
	virtual ~ListPainter();

	virtual void init(); // ��ʼ��
	virtual void initPaint() {} // ��ʼ�������б� 
	virtual void initHint() {} // ��ʼ��ʰȡ�б�
	virtual void begin() {} // ����֮ǰ
	virtual void paint(); // ����
	virtual void render() {}
	virtual void end() {} // ����֮��
	virtual void hint(); // ʰȡ
	virtual void destory(); // ����
	virtual void reset(); // ����
	virtual bool ready();
};

_GIS_END

#endif 



//// painter���ƻ���ͼԪ��ÿ��painter��������ʾ�б�һ��������ʾ��һ������ʰȡ
//class Painter
//{
//public:
//	Painter();
//	virtual ~Painter();
//
//	int getPaintID() const { return _paintID; }
//	int getHintID() const { return _hintID; }
//
//	// ��ʹ����ʾ�б�Ļ���
//	virtual void init() { }
//	virtual void begin() { }
//	virtual void paint() { } // ����
//	virtual void end() { }
//	virtual void hint() { } // ʰȡ
//
//	// ʹ����ʾ�б�Ļ���
//	virtual void initPaint() { } // ��ʼ����ʾ�б�
//	virtual void initHint() { } // ��ʼ��ʰȡ�б�
//
//	virtual void beginPaint() { }
//	virtual void beginHint() { }
//
//	virtual void callPaint();
//	virtual void callHint();
//
//	virtual void endPaint() { }
//	virtual void endHint() { }
//
//	static void setProjector(Projector* projector) { _projector = projector; }
//protected:
//	void destory();
//
//	int _paintID; // ������ʾ��id
//	int _hintID; // ����ѡ���id
//
//	static Projector* _projector; // ͶӰxy
//};
*/