#ifndef _SCENE_H_
#define _SCENE_H_

#include "arcball.h"

class Scene
{
public:
	enum MouseEventType // ����¼�����
	{
		MOUSEMOVE, // �ƶ�
		LBUTTONDOWN, // �������
		RBUTTONDOWN, // �Ҽ�����
		MBUTTONDOWN,//�м�����
		MBUTTONUP,//�м�̧��
		LBUTTONUP, // ���̧��
		RBUTTONUP, // �Ҽ�̧��
		MOUSEWHEEL, // ����
		RBUTTONDOUBLECLICK // �Ҽ�˫��
	};

	Scene();
	void init();
	void modelMatrix();
	void resize(int width, int height);
	bool update(MouseEventType type, int x = 0, int y = 0); // ��������¼���Ϣ�������Ƿ���Ҫ�ػ棬xyΪ��굱ǰλ��
protected:
	ArcBall arcball; // �����켣����
	Point2fT position; // ��ǰ�����λ��

	bool isClicked; // �Ƿ������
	bool isMClicked;//�Ƿ�������м�
	bool isRClicked; // �Ƿ��һ����
	bool isDragging; // �Ƿ��϶�

	Matrix4fT modelView; // ģ����ͼ����
	Matrix3fT LastRot;
	Matrix3fT ThisRot;

	float scaler; // ����

	Point2fT lastPos, translate;
	int _width, _height;
	Point2fT zeroPos;
	Point2fT zoom;//����Ҽ��϶�
	const static int zDeep = -8; 
};
#endif