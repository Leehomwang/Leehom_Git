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
	Painter();
	virtual ~Painter();

	virtual void init(); // 初始化
		virtual void initList() { } 
		virtual void initHint() { } 

	virtual void paint(); // 绘制
		virtual void begin() { }
		virtual void render() { }
		virtual void end() { }

	virtual void hint(); // 拾取

	virtual void destory(); // 销毁
	virtual void reset(); // 重置
	virtual bool ready() { return false; }

	int getHintID() const { return _hintID; }
	static void setProjector(Projector* projector) { _projector = projector; }
protected:
	bool _isUseList;
	int _listID; // 用于显示的id
	int _hintID; // 用于拾取的id

	static Projector* _projector; // 投影xy
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
