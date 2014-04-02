#include <gl/glew.h>
#include "scene.h"
#include <stdio.h>

Scene::Scene()
{
	isClicked  = false; // �Ƿ������
	isRClicked = false; // �Ƿ��һ����
	isDragging = false; // �Ƿ��϶�

	Matrix3fSetIdentity(&LastRot); // ��Ϊ��λ��
	Matrix3fSetIdentity(&ThisRot); // ��Ϊ��λ��

	float f16[] = // 4x4��λ��
	{
		1.0f, 0.0f, 0.0f, 0.0f, //����任
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	for (int i = 0; i < 16; i++) // ��Ϊ��λ��
	{
		modelView.M[i] = f16[i];
	}

	translate.s.X = translate.s.Y = 0; // xoyƽ��ƽ��
	scaler = 1.0f; // ����ϵ��

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

	arcball.setBounds(width, height); // ����ArcBall�߽緶Χ
}

bool Scene::update(MouseEventType type, int x , int y)
{
	bool repaint = false; // �����Ƿ��ػ�
	switch (type) // ע��case��˳��Խ�����ֵķ�ǰ��
	{
	case MOUSEMOVE: // ����ƶ�
		position.s.X = float(x); // �������
		position.s.Y = float(y);

		if (!isDragging) { // ���û���϶�
			if (isClicked) { // ��ʱ����������
				isDragging = true; // �����϶�����Ϊtrue
				LastRot = ThisRot; // �켣���������
				arcball.click(&position);	// ��¼��ǰ��Ӧ�Ĺ켣���λ��
			}
			if (isRClicked) // ��ʱ��������Ҽ�
			{
				lastPos.s.X = x; // ���������һλ��
				lastPos.s.Y = y;
				isDragging = true;
			}
			if (isMClicked)//��ʱ��������м�
			{
				lastPos.s.X = x;
				lastPos.s.Y = y;
				isDragging = true;
			}
		} else {
			if (isClicked) { // �����ס������϶�
				Quat4fT ThisQuat;
				arcball.drag(&position, &ThisQuat); // ���¹켣��ı���
				Matrix3fSetRotationFromQuat4f(&ThisRot, &ThisQuat); // ������ת��
				Matrix3fMulMatrix3f(&ThisRot, &LastRot);
				Matrix4fSetRotationFromMatrix3f(&modelView, &ThisRot); // ����ģ����ͼ����

				repaint = true; // ��Ҫ�ػ�
			}
			if (isRClicked) // ��������Ҽ����϶�
			{
				translate.s.X += x - lastPos.s.X; // ����xoyƽ��ƽ������Ϊ����굱ǰ���� - �����һ����
				translate.s.Y += y - lastPos.s.Y;
				//zoom.s.X += x - zeroPos.s.X;
				//zoom.s.Y += y - zeroPos.s.Y;
				//scaler += ( zoom.s.Y)/20000;
				//if (scaler + float(x) / 2000 > 0) // ����zoomֵС��0����������
				//{
				//	scaler += float(x) / 2000;
				//}
				lastPos.s.X = x; // ���������һ����
				lastPos.s.Y = y;
				repaint = true; // ��Ҫ�ػ�
			}
			else//��������м����϶�
			{
				zoom.s.Y = lastPos.s.Y - y;
				if (scaler + zoom.s.Y / 2000 > 0) // ����zoomֵС��0����������
				{
					scaler += zoom.s.Y / 2000;
				}
				lastPos.s.X = x;
				lastPos.s.Y = y;
				repaint = true;
			}
		}
		break;
	case LBUTTONDOWN: // �������
		isClicked   = true;
		break;
	case RBUTTONDOWN: // �Ҽ�����
		isRClicked = true;
		break;
	case MBUTTONDOWN: //�м�����
		isMClicked = true;
		break;
	case LBUTTONUP: // ���̧��
		isClicked = false;
		isDragging = false; // �϶����
		break;
	case RBUTTONUP: // �Ҽ�̧��
		isRClicked  = false;
		isDragging = false;
		break;
	case MBUTTONUP: //�м�̧��
		isMClicked = false;
		isDragging = false;
		break;
	case MOUSEWHEEL: // ����
		if (scaler + float(x) / 2000 > 0) // ����zoomֵС��0����������
		{
			scaler += float(x) / 2000;
		}
		repaint = true;
		break;
	case RBUTTONDOUBLECLICK: // �Ҽ�˫�������þ���
		scaler = 1;
		translate.s.X = translate.s.Y = 0;
		Matrix3fSetIdentity(&LastRot);
		Matrix3fSetIdentity(&ThisRot);
		Matrix4fSetRotationFromMatrix3f(&modelView, &ThisRot);
		repaint = true;
		break;
	default:;
	}

	return repaint; // �����Ƿ���Ҫ�ػ�
}

void Scene::init()
{
	glClearColor(.0f, .0f, .0f, 1.f); // �����������ɫ
	glClearDepth(1);									// ������Ȼ���

	float lightAmbient[] = {.1, .1, .1, 1.0};
	float lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float lightPosition[] = {0.0f, 0.0f, 11.0f, 1.0f};

	glShadeModel(GL_SMOOTH);							// ������Ӱƽ�������ڿ���opengl�л���ָ���������������ɫ�Ĺ���ģʽ
	glEnable(GL_DEPTH_TEST);							// ������Ȳ���
	glEnable(GL_CULL_FACE);								// �����޳����ܣ����Խ��ö������������ϵĹ��ա���Ӱ����ɫ���㼰��������������Ҫ����Ⱦ��������Ϊ���۶�����ν�����ת��任�������ῴ������εı���
	glDepthFunc(GL_LEQUAL);								// ������Ȳ��Ե����ͣ�������ֵС�ڻ���ڵ�ǰ�洢�����ֵ����ͨ�����ԣ�����
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // ͸��������������ϸ��͸����������һ�и���OpenGL����ϣ��������õ�͸�����������ʮ����΢��Ӱ�����ܡ���ʹ��͸��ͼ��������һ�㡣

	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);		// ���û����⣬������η�������Ĺ��Ϊ�����⣬�޷�ȷ��������ķ��򣬵����ض��Ĺ�Դ�رպ����ǽ���ʧ��ÿ����Դ���ܶԳ����ṩ�����⡣���⣬����һ�������⣬���������κ��ض��Ĺ�Դ����֮Ϊȫ�ֻ����⡣��Ҳ����Ϊʲô���ǲ����κ��Զ����Դ��Ҳ�ܿ������Ƶ������ԭ��
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);		// ��������⣬����ͬһ�������䵽�������󣬽��ظ���������ȷ��䣬��ˣ����۴��ĸ�����۲죬��������ȶ���ͬ
	glLightfv(GL_LIGHT1, GL_POSITION,lightPosition);	// ���ù�Դλ��
	glEnable(GL_LIGHT1);								// ����1�Ź�Դ

	glEnable(GL_COLOR_MATERIAL); // ���������޸Ĳ������Դ����Ŀ���, ʹ����Ĳ�����������ʹ�õ�ǰ��ɫ
	glColorMaterial(GL_FRONT, GL_DIFFUSE); // ʹ��������Ĳ�������(ɢ����ɫ)����ʹ�õ�ǰ��ɫ

	glEnable(GL_NORMALIZE);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // ʹ�ڱ���Ҳ�ܱ���ȷ�ع��գ�OpenGLΪ�泯��Ķ��������淨�ߵ��档�����ζ�Ŷ���ε�������ı��淨�߾�����۲��ߡ���Ϊ���������ε������������ȷ��������
}

void Scene::modelMatrix()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �����Ļ

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, zDeep); // ��ģ�������ƣ�Ϊ�˿���
	glTranslatef(translate.s.X / 100, -translate.s.Y / 100, 0); // ��Ϊģ����[-1, 1]�����ڣ�������Ҫxoyƽ�Ƶľ����С����Ҫ����һ������

	glScalef(scaler, scaler, scaler); // ����
	glMultMatrixf(modelView.M); // ���Ա任����
}
