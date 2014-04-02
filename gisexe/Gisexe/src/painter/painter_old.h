/*
#ifndef _PAINTER_H_
#define _PAINTER_H_

#include "projector.h"

_GIS_BEGIN

class IDSpace // 显示列表id生成器，生成唯一显示列表id
{
public:
	virtual ~IDSpace(); // 释放生成的显示列表
	static int next() { return _id++; } // 简单实现，只加不减
protected:
	IDSpace() { } // 禁止生成对象
	static int _id; // 静态
};

class Painter
{
public:
	virtual void init() = 0; // 初始化
	virtual void initPaint() = 0; // 初始化绘制列表 
	virtual void initHint() = 0; // 初始化拾取列表

	virtual void begin() = 0; // 绘制之前
	virtual void paint() = 0; // 绘制
	virtual void render() = 0; // 绘制中
	virtual void end() = 0; // 绘制之后
	virtual void hint() = 0; // 拾取

	virtual void destory() = 0; // 销毁
	virtual void reset() = 0; // 重置
	virtual bool ready() = 0; // 是否需要初始化

	int getHintID() const { return _hintID; }
	static void setProjector(Projector* projector) { _projector = projector; }
protected:
	int _paintID; // 用于显示的id
	int _hintID; // 用于拾取的id
	static Projector* _projector; // 投影xy
};

class JustPainter : public Painter // 不使用显示列表绘制
{
public:
	virtual void init(); // 初始化
	virtual void initPaint() {} // 初始化绘制列表，默认不用实现
	virtual void initHint() {} // 初始化拾取列表，默认不用实现
	virtual void begin() {} // 绘制之前
	virtual void paint(); // 绘制
	virtual void render() {} // 绘制中
	virtual void end() {} // 绘制之后
	virtual void hint() {} // 拾取
	virtual void destory() {} // 销毁
	virtual void reset() {} // 重置
	virtual bool ready() { return true; }
};

class ListPainter : public Painter // 使用显示列表绘制
{
public:
	ListPainter();
	virtual ~ListPainter();

	virtual void init(); // 初始化
	virtual void initPaint() {} // 初始化绘制列表 
	virtual void initHint() {} // 初始化拾取列表
	virtual void begin() {} // 绘制之前
	virtual void paint(); // 绘制
	virtual void render() {}
	virtual void end() {} // 绘制之后
	virtual void hint(); // 拾取
	virtual void destory(); // 销毁
	virtual void reset(); // 重置
	virtual bool ready();
};

_GIS_END

#endif 



//// painter绘制基础图元，每个painter有两个显示列表，一个用来显示，一个用来拾取
//class Painter
//{
//public:
//	Painter();
//	virtual ~Painter();
//
//	int getPaintID() const { return _paintID; }
//	int getHintID() const { return _hintID; }
//
//	// 不使用显示列表的绘制
//	virtual void init() { }
//	virtual void begin() { }
//	virtual void paint() { } // 绘制
//	virtual void end() { }
//	virtual void hint() { } // 拾取
//
//	// 使用显示列表的绘制
//	virtual void initPaint() { } // 初始化显示列表
//	virtual void initHint() { } // 初始化拾取列表
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
//	int _paintID; // 用于显示的id
//	int _hintID; // 用于选择的id
//
//	static Projector* _projector; // 投影xy
//};
*/