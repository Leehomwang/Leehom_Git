#include "createRadar.h"
#include "Point_Radar.h"

osg::ref_ptr<osg::Texture2D> texture2D(const char* imageFile)
{
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile(imageFile);
	if (image.valid())
	{
		osg::ref_ptr<osg::Texture2D> texture2D = new osg::Texture2D;
		texture2D->setImage(image.get());
		return texture2D.get();
	}
	return 0;
}

osg::ref_ptr<osg::Group> CreateRadar(const char* filename, osg::Vec4 color, int numbOfPoints)
{
	osg::ref_ptr<osg::Geometry> myRadar = new osg::Geometry;

	osg::ref_ptr<osg::Vec3Array> Vertices = createPoints(filename, numbOfPoints);//��������
	osg::ref_ptr<osg::IntArray> Indeices = createIndeies(numbOfPoints);//������������
	osg::ref_ptr<osg::Vec4Array> Colors = new osg::Vec4Array;//��ɫ����
	osg::ref_ptr<osg::IntArray> Icolor = new osg::IntArray;//��ɫ��������


	myRadar->setVertexArray(Vertices.get());
	myRadar->setVertexIndices(Indeices.get());

	//Colors->push_back(osg::Vec4(0.6, 0.8, 0.0, 0.3));
	Colors->push_back(color);
	myRadar->setColorArray(Colors.get());
	myRadar->setColorBinding(osg::Geometry::BIND_OVERALL);

	myRadar->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, Indeices->size()));

	//�Զ����ɶ��㷨��
	osgUtil::SmoothingVisitor::smooth(*myRadar);

	//��������
	//osg::ref_ptr<osg::Texture2D> tex1 = texture2D("Images/green.jpg");
	//�����Զ�������������
	//osg::ref_ptr<osg::TexGen> texGen = new osg::TexGen();
	//texGen->setMode(osg::TexGen::SPHERE_MAP);
	//������������ģʽΪBlend
	//osg::ref_ptr<osg::TexEnv> texEnv = new osg::TexEnv;
	//texEnv->setMode(osg::TexEnv::Mode::ADD);
	//texEnv->setColor(osg::Vec4(0.6,0.6,0.6,0.5));

	//����״̬
	//osg::ref_ptr<osg::StateSet> texState = myRadar->getOrCreateStateSet();
	//��������״̬
	//texState->setTextureAttributeAndModes(1, tex1.get(), osg::StateAttribute::ON);
	//texState->setTextureAttributeAndModes(1, texGen.get(), osg::StateAttribute::ON);
	//texState->setTextureAttribute(1,texEnv.get(), osg::StateAttribute::ON);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(myRadar.get());

	//����״̬
	osg::ref_ptr<osg::StateSet> stateSet = geode->getOrCreateStateSet();

	stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED );
	stateSet->setRenderBinDetails(11, "RenderBin");//������Ⱦ���ȼ�------�������������� ���㱳����node������У�û���ù�����-1.

	osg::ref_ptr<osg::Group> radar = new osg::Group;

	radar->addChild(geode.get());

	return radar;
}