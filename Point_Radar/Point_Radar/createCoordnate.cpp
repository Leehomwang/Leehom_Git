#include "createCoordinate.h"

osg::ref_ptr<osg::Group> createCoordinate()
{
	/*//创建保存几何信息的对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	//创建四个顶点
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(40.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(0.0f, 40.0f, 0.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 40.0f));
	geom->setVertexArray(v.get());

	//为每个顶点指定一种颜色
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();
	c->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); //坐标原点为白色
	c->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)); //x red
	c->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); //坐标原点为白色
	c->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f)); //y green
	c->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); //坐标原点为白色
	c->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f)); //z blue
	//如果没指定颜色则会变为黑色
	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX); 

	//三个轴
	//geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4)); //XZ
	geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2)); //X
	geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, 2, 2)); //Y
	geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, 4, 2)); //Z

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::StateSet> geodeState = geode->getOrCreateStateSet();
	geodeState->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	geode->addDrawable(geom.get());

	osg::ref_ptr<osg::Group> newroot = new osg::Group();
	newroot->addChild(geode.get());

	return newroot;*/

	//Begin draw Axis
	
	float length = 45.0f;//坐标轴总长度
	int segments = 5;//坐标轴段数
	float perLength = length/segments;//每段长度

	osg::ref_ptr<osg::Geometry> Axis = new osg::Geometry;

	osg::ref_ptr<osg::Vec3Array> vecArray = new osg::Vec3Array;

	vecArray->push_back(osg::Vec3(0.0,0.0,0.0));//原点
	vecArray->push_back(osg::Vec3(length,0.0,0.0));//X轴
	vecArray->push_back(osg::Vec3(length-5.0,3.0,0.0));
	vecArray->push_back(osg::Vec3(length-5.0,-3.0,0.0));
	vecArray->push_back(osg::Vec3(0.0,length,0.0));//Y轴
	vecArray->push_back(osg::Vec3(3.0,length-5.0,0.0));
	vecArray->push_back(osg::Vec3(-3.0,length-5.0,0.0));
	vecArray->push_back(osg::Vec3(0.0,0.0,length));//Z轴
	vecArray->push_back(osg::Vec3(3.0,0.0,length-5.0));
	vecArray->push_back(osg::Vec3(-3.0,0.0,length-5.0));
	
	//X轴断点
	for (int i = 1; i < segments; i++)
	{
		vecArray->push_back(osg::Vec3(perLength*i,0.0,0.0));
		vecArray->push_back(osg::Vec3(perLength*i,2.0,0.0));
	}
	//Y轴断点
	for (int i = 1; i < segments; i++)
	{
		vecArray->push_back(osg::Vec3(0.0,perLength*i,0.0));
		vecArray->push_back(osg::Vec3(2.0,perLength*i,0.0));
	}
	//Z轴断点
	for (int i = 1; i < segments; i++)
	{
		vecArray->push_back(osg::Vec3(0.0,0.0,perLength*i));
		vecArray->push_back(osg::Vec3(2.0,0.0,perLength*i));
	}


	osg::ref_ptr<osg::IntArray> vecIndexArray = new osg::IntArray;
	vecIndexArray->push_back(0);//X轴
	vecIndexArray->push_back(1);
	vecIndexArray->push_back(1);
	vecIndexArray->push_back(2);
	vecIndexArray->push_back(1);
	vecIndexArray->push_back(3);
	vecIndexArray->push_back(0);//Y轴
	vecIndexArray->push_back(4);
	vecIndexArray->push_back(4);
	vecIndexArray->push_back(5);
	vecIndexArray->push_back(4);
	vecIndexArray->push_back(6);
	vecIndexArray->push_back(0);//Z轴
	vecIndexArray->push_back(7);
	vecIndexArray->push_back(7);
	vecIndexArray->push_back(8);
	vecIndexArray->push_back(7);
	vecIndexArray->push_back(9);
	//XYZ轴断点下标
	for (int i = 10; i <10+(segments-1)*6; i++)
	{
		vecIndexArray->push_back(i);
	}

	osg::ref_ptr<osg::Vec4Array> colArray = new osg::Vec4Array;

	colArray->push_back(osg::Vec4(1.0,0.0,0.0,1.0));

	colArray->push_back(osg::Vec4(0.0,1.0,0.0,1.0));

	colArray->push_back(osg::Vec4(0.0,0.0,1.0,1.0));



	osg::ref_ptr<osg::IntArray> colorIndexArray = new osg::IntArray;

	colorIndexArray->push_back(0);//X轴颜色
	colorIndexArray->push_back(0);
	colorIndexArray->push_back(0);

	colorIndexArray->push_back(1);//Y轴颜色
	colorIndexArray->push_back(1);
	colorIndexArray->push_back(1);

	colorIndexArray->push_back(2);//Z轴颜色
	colorIndexArray->push_back(2);
	colorIndexArray->push_back(2);
	//XYZ轴分段颜色
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < segments-1; j++)
		{
			colorIndexArray->push_back(i);
		}
	}


	Axis->setVertexArray(vecArray);

	Axis->setVertexIndices(vecIndexArray);

	Axis->setColorArray(colArray);

	Axis->setColorIndices(colorIndexArray);

	Axis->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);

	Axis->addPrimitiveSet((new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, (9+(segments-1)*3)*2)));



	osg::ref_ptr<osg::Geode> AxisGeode=new osg::Geode;

	AxisGeode->addDrawable(Axis);



	//set some attribute

	osg::ref_ptr<osg::LineWidth> lineW=new osg::LineWidth;

	lineW->setWidth(3.0);



	osg::ref_ptr<osg::StateSet> stateset=AxisGeode->getOrCreateStateSet();

	stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

	stateset->setAttribute(lineW,osg::StateAttribute::ON);

	//End Draw Axis



	//Begin add Text

	osg::ref_ptr<osg::Geode> HudGeode=new osg::Geode;

	osg::ref_ptr<osgText::Text> textx = new osgText::Text();
	HudGeode->addDrawable(textx);
	osg::ref_ptr<osgText::Text> x1 = new osgText::Text();
	HudGeode->addDrawable(x1);
	osg::ref_ptr<osgText::Text> x2 = new osgText::Text();
	HudGeode->addDrawable(x2);
	osg::ref_ptr<osgText::Text> x3 = new osgText::Text();
	HudGeode->addDrawable(x3);
	osg::ref_ptr<osgText::Text> x4 = new osgText::Text();
	HudGeode->addDrawable(x4);
	osg::ref_ptr<osgText::Text> texty = new osgText::Text();
	HudGeode->addDrawable(texty);
	osg::ref_ptr<osgText::Text> y1 = new osgText::Text();
	HudGeode->addDrawable(y1);
	osg::ref_ptr<osgText::Text> y2 = new osgText::Text();
	HudGeode->addDrawable(y2);
	osg::ref_ptr<osgText::Text> y3 = new osgText::Text();
	HudGeode->addDrawable(y3);
	osg::ref_ptr<osgText::Text> y4 = new osgText::Text();
	HudGeode->addDrawable(y4);
	osg::ref_ptr<osgText::Text> textz = new osgText::Text();
	HudGeode->addDrawable(textz);
	osg::ref_ptr<osgText::Text> z1 = new osgText::Text();
	HudGeode->addDrawable(z1);
	osg::ref_ptr<osgText::Text> z2 = new osgText::Text();
	HudGeode->addDrawable(z2);
	osg::ref_ptr<osgText::Text> z3 = new osgText::Text();
	HudGeode->addDrawable(z3);
	osg::ref_ptr<osgText::Text> z4 = new osgText::Text();
	HudGeode->addDrawable(z4);



	// 设置HUD文字的参数
	//X轴
	textx->setCharacterSize(5);
	textx->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体
	textx->setText(L"Length/Km");
	textx->setAxisAlignment(osgText::Text::XY_PLANE);
	textx->setAlignment(osgText::Text::CENTER_TOP);
	textx->setPosition( osg::Vec3(length+5.0,0.0,0.0) );
	textx->setColor( osg::Vec4(1.0, 0.0, 0.0, 1) );
	//X1
	x1->setCharacterSize(3);
	x1->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体
	x1->setText(L"5");
	x1->setAxisAlignment(osgText::Text::XY_PLANE);
	x1->setAlignment(osgText::Text::CENTER_TOP);
	x1->setPosition( osg::Vec3(perLength*1,0.0,0.0) );
	x1->setColor( osg::Vec4(1.0, 0.0, 0.0, 1) );
	//X2
	x2->setCharacterSize(3);
	x2->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体
	x2->setText(L"10");
	x2->setAxisAlignment(osgText::Text::XY_PLANE);
	x2->setAlignment(osgText::Text::CENTER_TOP);
	x2->setPosition( osg::Vec3(perLength*2,0.0,0.0) );
	x2->setColor( osg::Vec4(1.0, 0.0, 0.0, 1) );
	//X3
	x3->setCharacterSize(3);
	x3->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体
	x3->setText(L"15");
	x3->setAxisAlignment(osgText::Text::XY_PLANE);
	x3->setAlignment(osgText::Text::CENTER_TOP);
	x3->setPosition( osg::Vec3(perLength*3,0.0,0.0) );
	x3->setColor( osg::Vec4(1.0, 0.0, 0.0, 1) );
	//X4
	x4->setCharacterSize(3);
	x4->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体
	x4->setText(L"20");
	x4->setAxisAlignment(osgText::Text::XY_PLANE);
	x4->setAlignment(osgText::Text::CENTER_TOP);
	x4->setPosition( osg::Vec3(perLength*4,0.0,0.0) );
	x4->setColor( osg::Vec4(1.0, 0.0, 0.0, 1) );



	//Y轴
	texty->setCharacterSize(5);
	texty->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体
	texty->setText(L"Length/Km");
	texty->setAxisAlignment(osgText::Text::XY_PLANE);
	texty->setAlignment(osgText::Text::CENTER_TOP);
	texty->setPosition( osg::Vec3(0.0,length+5.0,0.0) );
	texty->setColor( osg::Vec4(0.0, 1.0, 0.0, 1.0) );
	//Y1
	y1->setCharacterSize(3);
	y1->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体
	y1->setText(L"5");
	y1->setAxisAlignment(osgText::Text::XY_PLANE);
	y1->setAlignment(osgText::Text::RIGHT_CENTER);
	y1->setPosition( osg::Vec3(0.0,perLength*1,0.0) );
	y1->setColor( osg::Vec4(0.0, 1.0, 0.0, 1.0) );
	//Y2
	y2->setCharacterSize(3);
	y2->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体
	y2->setText(L"10");
	y2->setAxisAlignment(osgText::Text::XY_PLANE);
	y2->setAlignment(osgText::Text::RIGHT_CENTER);
	y2->setPosition( osg::Vec3(0.0,perLength*2,0.0) );
	y2->setColor( osg::Vec4(0.0, 1.0, 0.0, 1.0) );
	//Y3
	y3->setCharacterSize(3);
	y3->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体
	y3->setText(L"15");
	y3->setAxisAlignment(osgText::Text::XY_PLANE);
	y3->setAlignment(osgText::Text::RIGHT_CENTER);
	y3->setPosition( osg::Vec3(0.0,perLength*3,0.0) );
	y3->setColor( osg::Vec4(0.0, 1.0, 0.0, 1.0) );
	//Y4
	y4->setCharacterSize(3);
	y4->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体
	y4->setText(L"20");
	y4->setAxisAlignment(osgText::Text::XY_PLANE);
	y4->setAlignment(osgText::Text::RIGHT_CENTER);
	y4->setPosition( osg::Vec3(0.0,perLength*4,0.0) );
	y4->setColor( osg::Vec4(0.0, 1.0, 0.0, 1.0) );

	//Z轴
	textz->setCharacterSize(5);
	textz->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体
	textz->setText(L"Height/Km");
	textz->setAxisAlignment(osgText::Text::XZ_PLANE);
	textz->setAlignment(osgText::Text::CENTER_TOP);
	textz->setPosition(osg::Vec3(0.0,0.0,length+5.0));
	textz->setColor(osg::Vec4(0.0, 0.0, 1.0, 1));
	//Z1
	z1->setCharacterSize(3);
	z1->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体
	z1->setText(L"5");
	z1->setAxisAlignment(osgText::Text::XZ_PLANE);
	z1->setAlignment(osgText::Text::RIGHT_CENTER);
	z1->setPosition( osg::Vec3(0.0,0.0,perLength*1) );
	z1->setColor( osg::Vec4(0.0, 0.0, 1.0, 1.0) );
	//Z2
	z2->setCharacterSize(3);
	z2->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体
	z2->setText(L"10");
	z2->setAxisAlignment(osgText::Text::XZ_PLANE);
	z2->setAlignment(osgText::Text::RIGHT_CENTER);
	z2->setPosition( osg::Vec3(0.0,0.0,perLength*2) );
	z2->setColor( osg::Vec4(0.0, 0.0, 1.0, 1.0) );
	//Z3
	z3->setCharacterSize(3);
	z3->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体
	z3->setText(L"15");
	z3->setAxisAlignment(osgText::Text::XZ_PLANE);
	z3->setAlignment(osgText::Text::RIGHT_CENTER);
	z3->setPosition( osg::Vec3(0.0,0.0,perLength*3) );
	z3->setColor( osg::Vec4(0.0, 0.0, 1.0, 1.0) );
	//Z4
	z4->setCharacterSize(3);
	z4->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体
	z4->setText(L"20");
	z4->setAxisAlignment(osgText::Text::XZ_PLANE);
	z4->setAlignment(osgText::Text::RIGHT_CENTER);
	z4->setPosition( osg::Vec3(0.0,0.0,perLength*4) );
	z4->setColor( osg::Vec4(0.0, 0.0, 1.0, 1.0) );


	osg::ref_ptr<osg::Group> coordinate=new osg::Group;

	coordinate->addChild(HudGeode);

	coordinate->addChild(AxisGeode);

	return coordinate;
}