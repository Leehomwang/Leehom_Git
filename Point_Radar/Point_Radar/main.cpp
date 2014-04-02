#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osg/BlendFunc>
#include <osg/CullFace>
#include <osg/Depth>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/Material>
#include <osgDB/Registry>
#include <osgDB/WriteFile>
#include <osgGA/StateSetManipulator>
#include <osgUtil/Optimizer>
#include <osg/Geometry>

#include "createRadar.h"
#include "createCoordinate.h"
#include "map.h"
#include "createEarth.h"
#include "MyPoint.h"
#include "CoordinatesToXYZ.h"

#define PI 3.1415926535898

osg::ref_ptr<osg::Light> creatLocalLight(int lightNumb, osg::Vec4 lightPos, osg::Vec4 lightAmbi, osg::Vec4 lightDiff, osg::Vec4 lightSpec,float constantA, float linearA, float quadraticA)
{
	osg::ref_ptr<osg::Light> light = new osg::Light;
	light->setLightNum(lightNumb);
	light->setPosition(lightPos);
	light->setAmbient(lightAmbi);
	light->setDiffuse(lightDiff);
	light->setSpecular(lightSpec);
	light->setConstantAttenuation(constantA);
	light->setLinearAttenuation(linearA);
	light->setQuadraticAttenuation(quadraticA);
	return light;
}

osg::ref_ptr<osg::Light> createSpotLight(int lightNumb, osg::Vec4 lightPos, osg::Vec4 lightAmbi, osg::Vec4 lightDiff,osg::Vec4 lightSpec,float cutoff, float exponent, osg::Vec3 direction)
{
	osg::ref_ptr<osg::Light> light = new osg::Light;
	light->setLightNum(lightNumb);
	light->setPosition(lightPos);
	light->setAmbient(lightAmbi);
	light->setDiffuse(lightDiff);
	light->setSpecular(lightSpec);
	light->setSpotCutoff(cutoff);//ָ���۹�Ƶİ��
	light->setSpotExponent(exponent);//ָ���۹�Ƶ�ָ��������
	light->setDirection(direction);
	return light;
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	viewer->setUpViewInWindow(100, 100, 1024, 768);

	

	//��������
	osg::ref_ptr<osg::Group> earth = createEarth(500.0,  "Images/land_shallow_topo_2048.jpg");
	//�����״�
	osg::ref_ptr<osg::Group> Radar1 = CreateRadar("I:\\Leehomwang\\OSG\\data\\mydata\\mydata.txt", osg::Vec4(0.6, 0.8, 0.0, 0.4), 94);
	osg::ref_ptr<osg::Group> Radar2 = CreateRadar("I:\\Leehomwang\\OSG\\data\\mydata\\mydata.txt", osg::Vec4(0.2, 0.8, 0.6, 0.4), 94);
	//��������
	osg::ref_ptr<osg::Group> Wave = CreateRadar("I:\\Leehomwang\\OSG\\data\\mydata\\mydata_Wavebar.txt", osg::Vec4(0.2, 0.8, 0.6, 0.4), 45);
	//��������ϵ
	osg::ref_ptr<osg::Group> coordintaNode1 = createCoordinate();
	osg::ref_ptr<osg::Group> coordintaNode2 = createCoordinate();

	//�������ڵ�
	osg::ref_ptr<osg::Group> root = new osg::Group;


	//���û�Ϻ���
	osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc();
	blendFunc->setSource(osg::BlendFunc::SRC_ALPHA);
	blendFunc->setDestination(osg::BlendFunc::ONE_MINUS_SRC_ALPHA);

	//����������
	osg::ref_ptr<osg::CullFace> cullFace = new osg::CullFace(osg::CullFace::BACK);

	//������
	osg::ref_ptr<osg::Group> Radar_Coor1 = new osg::Group;
	osg::ref_ptr<osg::Group> Radar_Coor2 = new osg::Group;

	//������Ա
	Radar_Coor1->addChild(Radar1.get());
	Radar_Coor1->addChild(coordintaNode1.get());
	//Radar_Coor1->addChild(lightSource0.get());
	Radar_Coor2->addChild(Radar2.get());
	Radar_Coor2->addChild(coordintaNode2.get());
	//Radar_Coor2->addChild(lightSource1.get());
	//��γ��ת��ά����
	MyPoint point1 = CoordinatesToXYZ(120.2, 30.3, 500);//����
	MyPoint point2 = CoordinatesToXYZ(119.3, 26.08, 500);//����
	MyPoint point3 = CoordinatesToXYZ(124.27, 27.86, 500);//
	
	//ģ��λ�ÿ���
	osg::ref_ptr<osg::MatrixTransform> pos1 = new osg::MatrixTransform;
	pos1->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(40.0),0,1,0) *osg::Matrix::rotate(osg::DegreesToRadians(40.0),1,0,0) * osg::Matrix::translate(point1.x,point1.y,point1.z));
	pos1->addChild(Radar_Coor1.get());

	osg::ref_ptr<osg::MatrixTransform> pos2 = new osg::MatrixTransform;
	pos2->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(40.0),0,1,0) *osg::Matrix::rotate(osg::DegreesToRadians(45.0),1,0,0) *osg::Matrix::translate(point2.x,point2.y,point2.z));
	pos2->addChild(Radar_Coor2.get());

	osg::ref_ptr<osg::MatrixTransform> pos3 = new osg::MatrixTransform;
	pos3->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(40.0),0,1,0) *osg::Matrix::rotate(osg::DegreesToRadians(45.0),1,0,0) *osg::Matrix::translate(point3.x,point3.y,point3.z));
	pos3->addChild(Wave.get());

	osg::ref_ptr<osg::MatrixTransform> earthPos = new osg::MatrixTransform;
	earthPos->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(31.0), 0, 0, 1));
	earthPos->addChild(earth.get());


	//�����ƹ�
	osg::ref_ptr<osg::Light> localLight0 = creatLocalLight(1,osg::Vec4(point1.x,point1.y,point1.z,1.0f),osg::Vec4(1.0f,1.0f,1.0f,1.0f),osg::Vec4(1.0f,1.0f,1.0f,1.0f),osg::Vec4(0.2f,0.2f,0.2f,0.2f),0.01f,0.005f,0.001f);
	osg::ref_ptr<osg::Light> localLight1 = creatLocalLight(2,osg::Vec4(point2.x,point2.y,point2.z,1.0f),osg::Vec4(1.0f,1.0f,1.0f,1.0f),osg::Vec4(1.0f,1.0f,1.0f,1.0f),osg::Vec4(0.2f,0.2f,0.2f,0.2f),0.01f,0.005f,0.001f);
	osg::ref_ptr<osg::Light> localLight2 = creatLocalLight(3,osg::Vec4(point3.x,point3.y,point3.z,1.0f),osg::Vec4(1.0f,1.0f,1.0f,1.0f),osg::Vec4(1.0f,1.0f,1.0f,1.0f),osg::Vec4(0.2f,0.2f,0.2f,0.2f),0.01f,0.001f,0.001f);//
	//osg::ref_ptr<osg::Light> spotLight = createSpotLight(1,osg::Vec4(0.0f,0.0f,30.0f,1.0f),osg::Vec4(1.0f,0.0f,0.0f,1.0f),osg::Vec4(1.0f,0.0f,0.0f,1.0f),osg::Vec4(1.0f,0.0f,0.0f,1.0f),20.0f,50.0f,osg::Vec3(0.0f,0.0f,-1.0f));
	osg::ref_ptr<osg::LightSource> lightSource0 = new osg::LightSource;
	osg::ref_ptr<osg::LightSource> lightSource1 = new osg::LightSource;
	osg::ref_ptr<osg::LightSource> lightSource2 = new osg::LightSource;
	lightSource0->setLight(localLight0);
	lightSource1->setLight(localLight1);
	lightSource2->setLight(localLight2);
	//lightSource->setLight(spotLight);
	lightSource0->setLocalStateSetModes(osg::StateAttribute::ON);
	lightSource1->setLocalStateSetModes(osg::StateAttribute::ON);
	lightSource2->setLocalStateSetModes(osg::StateAttribute::ON);

	//���Ҷ�ڵ�
	osg::ref_ptr<osg::Group> node = new osg::Group;
	node->addChild(pos1.get());
	node->addChild(pos2.get());

	

	osg::ref_ptr<osg::Group> map = createMap();

	//osg::ref_ptr<osg::Group> earth = createEarth(10.0,  "Images/land_shallow_topo_2048.jpg");

	//���ø��ڵ�״̬
	osg::ref_ptr<osg::StateSet> rootState = root->getOrCreateStateSet();
	rootState->setMode(GL_LIGHTING, osg::StateAttribute::ON);
	rootState->setMode(GL_LIGHT1, osg::StateAttribute::ON);
	rootState->setMode(GL_LIGHT2, osg::StateAttribute::ON);
	rootState->setMode(GL_LIGHT3, osg::StateAttribute::ON);


	//��ӵ��������ڵ�
	root->addChild(node.get());
	root->addChild(lightSource0.get());
	root->addChild(lightSource1.get());

	//root->addChild(map.get());
	//root->addChild(earth.get());
	root->addChild(earthPos.get());

	//root->addChild(Wave.get());
	root->addChild(pos3.get());

	//�Ż���������
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	//����ڵ㵽�ļ�
	//osgDB::Registry::instance()->writeNode(*(root.get()), "I:\\Leehomwang\\OSG\\code\\Point_Radar\\MyRadar.ive", osgDB::Registry::instance()->getOptions());


	//���״̬�¼�
	//L�����Ƶƹ�
	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));

	//���ڴ�С�仯�¼�
	//F�����ƴ���ȫ������С��
	viewer->addEventHandler(new osgViewer::WindowSizeHandler);

	//���һЩ����״̬����
	//S����ʾ֡�ʣ�W���л��߿�ͼ�͵�ͼ

	viewer->addEventHandler(new osgViewer::ThreadingHandler);
	viewer->addEventHandler(new osgViewer::StatsHandler);
	//viewer->addEventHandler(new osgViewer::HelpHandler(arguments.getApplicationUsage()));
	viewer->addEventHandler(new osgViewer::RecordCameraPathHandler);
	viewer->addEventHandler(new osgViewer::LODScaleHandler);
	viewer->addEventHandler(new osgViewer::ScreenCaptureHandler);

	//��ʾ
	viewer->setSceneData(root.get());
	viewer->realize();

	return viewer->run();
}

