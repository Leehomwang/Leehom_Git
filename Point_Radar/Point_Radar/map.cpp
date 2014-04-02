#include "map.h"


osg::ref_ptr<osg::Texture2D> createTexture2D(const std::string& imageFile)
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



osg::ref_ptr<osg::Group> createMap()
{
	osg::ref_ptr<osg::Geometry> Map = new osg::Geometry;

	osg::ref_ptr<osg::Vec3Array> vecArray = new osg::Vec3Array;
	vecArray->push_back(osg::Vec3(-120.0,-60.0,-1.0));
	vecArray->push_back(osg::Vec3(120.0,-60.0,-1.0));
	vecArray->push_back(osg::Vec3(120.0,60.0,-1.0));
	vecArray->push_back(osg::Vec3(-120.0,60.0,-1.0));

	osg::ref_ptr<osg::IntArray> vecIndexArray = new osg::IntArray;
	vecIndexArray->push_back(0);
	vecIndexArray->push_back(1);
	vecIndexArray->push_back(2);
	vecIndexArray->push_back(3);

	osg::Vec3Array* normals = new osg::Vec3Array;
	normals->push_back(osg::Vec3(0.0f,0.0f,1.0f));
	
	//设置纹理
	osg::ref_ptr<osg::Texture2D> tex1 = createTexture2D("Images/AsiaMap.jpg");
	//设置纹理坐标
	osg::ref_ptr<osg::Vec2Array>vt=new osg::Vec2Array();
	vt->push_back(osg::Vec2(0.0f,0.0f));
	vt->push_back(osg::Vec2(1.0f,0.0f));
	vt->push_back(osg::Vec2(1.0f,1.0f));
	vt->push_back(osg::Vec2(0.0f,1.0f));

	Map->setVertexArray(vecArray);

	Map->setVertexIndices(vecIndexArray);

	Map->setNormalArray(normals);
	Map->setNormalBinding(osg::Geometry::BIND_OVERALL);

	Map->setTexCoordArray(0, vt.get());

	Map->addPrimitiveSet((new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4)));

	//osg::ref_ptr<osg::Material> material1 = creatMaterial(osg::Vec4f(1.0,1.0,1.0,1.0),osg::Vec4f(1.0,1.0,1.0,0.5),osg::Vec4f(0.0,0.0,1.0,1.0),0.5);
	//stateSet1->setAttributeAndModes(material1.get(),osg::StateAttribute::ON);

	//设置状态
	osg::ref_ptr<osg::StateSet> texState = Map->getOrCreateStateSet();
	//设置纹理状态
	//texState->setAttributeAndModes(material1.get(), osg::StateAttribute::ON);
	texState->setTextureAttributeAndModes(0, tex1.get(), osg::StateAttribute::ON);
	//texState->setTextureAttributeAndModes(1, texGen.get(), osg::StateAttribute::ON);

	osg::ref_ptr<osg::Geode> MapGeode=new osg::Geode;

	MapGeode->addDrawable(Map);

	osg::ref_ptr<osg::Group> map = new osg::Group;

	map->addChild(MapGeode);

	return map;
}