#ifndef _SCENE_H_
#define _SCENE_H_

#include "arcball.h"

class Scene
{
public:
	enum MouseEventType // 鼠标事件类型
	{
		MOUSEMOVE, // 移动
		LBUTTONDOWN, // 左键按下
		RBUTTONDOWN, // 右键按下
		MBUTTONDOWN,//中键按下
		MBUTTONUP,//中键抬起
		LBUTTONUP, // 左键抬起
		RBUTTONUP, // 右键抬起
		MOUSEWHEEL, // 滚轮
		RBUTTONDOUBLECLICK // 右键双击
	};

	Scene();
	void init();
	void modelMatrix();
	void resize(int width, int height);
	bool update(MouseEventType type, int x = 0, int y = 0); // 接受鼠标事件消息，返回是否需要重绘，xy为鼠标当前位置
protected:
	ArcBall arcball; // 创建轨迹球类
	Point2fT position; // 当前的鼠标位置

	bool isClicked; // 是否点击鼠标
	bool isMClicked;//是否点击鼠标中键
	bool isRClicked; // 是否右击鼠标
	bool isDragging; // 是否拖动

	Matrix4fT modelView; // 模型视图矩阵
	Matrix3fT LastRot;
	Matrix3fT ThisRot;

	float scaler; // 缩放

	Point2fT lastPos, translate;
	int _width, _height;
	Point2fT zeroPos;
	Point2fT zoom;//鼠标右键拖动
	const static int zDeep = -8; 
};
#endif