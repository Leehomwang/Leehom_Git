#include <gl/glew.h>
#include "scene.h"
#include <stdio.h>

Scene::Scene()
{
	isClicked  = false; // 是否点击鼠标
	isRClicked = false; // 是否右击鼠标
	isDragging = false; // 是否拖动

	Matrix3fSetIdentity(&LastRot); // 置为单位阵
	Matrix3fSetIdentity(&ThisRot); // 置为单位阵

	float f16[] = // 4x4单位阵
	{
		1.0f, 0.0f, 0.0f, 0.0f, //计算变换
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	for (int i = 0; i < 16; i++) // 置为单位阵
	{
		modelView.M[i] = f16[i];
	}

	translate.s.X = translate.s.Y = 0; // xoy平面平移
	scaler = 1.0f; // 缩放系数

	_width = 1024; _height = 768;
	zeroPos.s.X = _width/2;  zeroPos.s.Y = _height/2;
}

void Scene::resize(int width, int height)
{
	height = height ? height : 1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = float(width) / height;
	glFrustum(-aspect , aspect	, -1, 1, 4, 1000);

	arcball.setBounds(width, height); // 更新ArcBall边界范围
}

bool Scene::update(MouseEventType type, int x , int y)
{
	bool repaint = false; // 返回是否重绘
	switch (type) // 注意case的顺序，越常出现的放前面
	{
	case MOUSEMOVE: // 鼠标移动
		position.s.X = float(x); // 鼠标坐标
		position.s.Y = float(y);

		if (!isDragging) { // 如果没有拖动
			if (isClicked) { // 此时按下鼠标左键
				isDragging = true; // 设置拖动变量为true
				LastRot = ThisRot; // 轨迹球变量更新
				arcball.click(&position);	// 记录当前对应的轨迹球的位置
			}
			if (isRClicked) // 此时按下鼠标右键
			{
				lastPos.s.X = x; // 更新鼠标上一位置
				lastPos.s.Y = y;
				isDragging = true;
			}
			if (isMClicked)//此时按下鼠标中键
			{
				lastPos.s.X = x;
				lastPos.s.Y = y;
				isDragging = true;
			}
		} else {
			if (isClicked) { // 如果按住左键并拖动
				Quat4fT ThisQuat;
				arcball.drag(&position, &ThisQuat); // 更新轨迹球的变量
				Matrix3fSetRotationFromQuat4f(&ThisRot, &ThisQuat); // 计算旋转量
				Matrix3fMulMatrix3f(&ThisRot, &LastRot);
				Matrix4fSetRotationFromMatrix3f(&modelView, &ThisRot); // 计算模型视图矩阵

				repaint = true; // 需要重绘
			}
			if (isRClicked) // 如果按下右键并拖动
			{
				translate.s.X += x - lastPos.s.X; // 更新xoy平面平移向量为，鼠标当前坐标 - 鼠标上一坐标
				translate.s.Y += y - lastPos.s.Y;
				//zoom.s.X += x - zeroPos.s.X;
				//zoom.s.Y += y - zeroPos.s.Y;
				//scaler += ( zoom.s.Y)/20000;
				//if (scaler + float(x) / 2000 > 0) // 避免zoom值小于0而发生反射
				//{
				//	scaler += float(x) / 2000;
				//}
				lastPos.s.X = x; // 更新鼠标上一坐标
				lastPos.s.Y = y;
				repaint = true; // 需要重绘
			}
			else//如果按下中键并拖动
			{
				zoom.s.Y = lastPos.s.Y - y;
				if (scaler + zoom.s.Y / 2000 > 0) // 避免zoom值小于0而发生反射
				{
					scaler += zoom.s.Y / 2000;
				}
				lastPos.s.X = x;
				lastPos.s.Y = y;
				repaint = true;
			}
		}
		break;
	case LBUTTONDOWN: // 左键按下
		isClicked   = true;
		break;
	case RBUTTONDOWN: // 右键按下
		isRClicked = true;
		break;
	case MBUTTONDOWN: //中键按下
		isMClicked = true;
		break;
	case LBUTTONUP: // 左键抬起
		isClicked = false;
		isDragging = false; // 拖动设否
		break;
	case RBUTTONUP: // 右键抬起
		isRClicked  = false;
		isDragging = false;
		break;
	case MBUTTONUP: //中键抬起
		isMClicked = false;
		isDragging = false;
		break;
	case MOUSEWHEEL: // 滚轮
		if (scaler + float(x) / 2000 > 0) // 避免zoom值小于0而发生反射
		{
			scaler += float(x) / 2000;
		}
		repaint = true;
		break;
	case RBUTTONDOUBLECLICK: // 右键双击，重置矩阵
		scaler = 1;
		translate.s.X = translate.s.Y = 0;
		Matrix3fSetIdentity(&LastRot);
		Matrix3fSetIdentity(&ThisRot);
		Matrix4fSetRotationFromMatrix3f(&modelView, &ThisRot);
		repaint = true;
		break;
	default:;
	}

	return repaint; // 返回是否需要重绘
}

void Scene::init()
{
	glClearColor(.0f, .0f, .0f, 1.f); // 清除缓冲区颜色
	glClearDepth(1);									// 设置深度缓存

	float lightAmbient[] = {.1, .1, .1, 1.0};
	float lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float lightPosition[] = {0.0f, 0.0f, 11.0f, 1.0f};

	glShadeModel(GL_SMOOTH);							// 启用阴影平滑，用于控制opengl中绘制指定两点间其他点颜色的过渡模式
	glEnable(GL_DEPTH_TEST);							// 启用深度测试
	glEnable(GL_CULL_FACE);								// 启用剔除功能，可以禁用多边形正面或背面上的光照、阴影和颜色计算及操作，消除不必要的渲染计算是因为无论对象如何进行旋转或变换，都不会看到多边形的背面
	glDepthFunc(GL_LEQUAL);								// 所作深度测试的类型，如果深度值小于或等于当前存储的深度值，则通过测试，绘制
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // 透视修正，真正精细的透视修正。这一行告诉OpenGL我们希望进行最好的透视修正。这会十分轻微的影响性能。但使得透视图看起来好一点。

	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);		// 设置环境光，经过多次反射而来的光称为环境光，无法确定其最初的方向，但当特定的光源关闭后，它们将消失。每个光源都能对场景提供环境光。此外，还有一个环境光，它不来自任何特定的光源，称之为全局环境光。这也就是为什么我们不加任何自定义光源，也能看见绘制的物体的原因。
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);		// 设置漫射光，来自同一方向，照射到物体表面后，将沿各个方向均匀反射，因此，无论从哪个方向观察，表面的亮度都相同
	glLightfv(GL_LIGHT1, GL_POSITION,lightPosition);	// 设置光源位置
	glEnable(GL_LIGHT1);								// 启用1号光源

	glEnable(GL_COLOR_MATERIAL); // 开启减少修改材料属性带来的开销, 使表面的材料属性总是使用当前颜色
	glColorMaterial(GL_FRONT, GL_DIFFUSE); // 使物体正面的材料属性(散射颜色)总是使用当前颜色

	glEnable(GL_NORMALIZE);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // 使内表面也能被正确地光照，OpenGL为面朝后的多边形求表面法线的逆。这就意味着多边形的两个面的表面法线均朝向观察者。作为结果，多边形的两个面均被正确地照亮。
}

void Scene::modelMatrix()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除屏幕

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, zDeep); // 把模型向内推，为了看见
	glTranslatef(translate.s.X / 100, -translate.s.Y / 100, 0); // 因为模型在[-1, 1]区间内，所以需要xoy平移的距离很小，需要除以一个比例

	glScalef(scaler, scaler, scaler); // 缩放
	glMultMatrixf(modelView.M); // 乘以变换矩阵
}
