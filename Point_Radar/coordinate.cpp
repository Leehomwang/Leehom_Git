int main()

{

   //Begin draw Axis

   osg::Geometry* Axis=new osg::Geometry;

   osg::Vec3Array* vecArray=new osg::Vec3Array;

   vecArray->push_back(osg::Vec3(0.0,0.0,0.0));

   vecArray->push_back(osg::Vec3(100.0,0.0,0.0));

   vecArray->push_back(osg::Vec3(0.0,100.0,0.0));

   vecArray->push_back(osg::Vec3(0.0,0.0,100.0));

 

   osg::Vec3Array* color=new osg::Vec3Array;

   color->push_back(osg::Vec3(1.0,0.0,0.0));

   color->push_back(osg::Vec3(0.0,1.0,0.0));

   color->push_back(osg::Vec3(0.0,0.0,1.0));

 

   osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType,4,4> *colorIndexArray

      =new osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType,4,4>;

   colorIndexArray->push_back(0);

   colorIndexArray->push_back(1);

   colorIndexArray->push_back(2);

 

   Axis->setVertexArray(vecArray);

   Axis->setColorArray(color);

   Axis->setColorIndices(colorIndexArray);

   Axis->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);

 

   osg::DrawElementsUInt* pXaxisPrimitiveSet=new osg::DrawElementsUInt(osg::PrimitiveSet::LINES);

   pXaxisPrimitiveSet->push_back(0);

   pXaxisPrimitiveSet->push_back(1);

   osg::DrawElementsUInt* pYaxisPrimitiveSet=new osg::DrawElementsUInt(osg::PrimitiveSet::LINES);

   pYaxisPrimitiveSet->push_back(0);

   pYaxisPrimitiveSet->push_back(2);

   osg::DrawElementsUInt* pZaxisPrimitiveSet=new osg::DrawElementsUInt(osg::PrimitiveSet::LINES);

   pZaxisPrimitiveSet->push_back(0);

   pZaxisPrimitiveSet->push_back(3);

 

   Axis->addPrimitiveSet(pXaxisPrimitiveSet);

   Axis->addPrimitiveSet(pYaxisPrimitiveSet);

   Axis->addPrimitiveSet(pZaxisPrimitiveSet);

 

   osg::Geode* AxisGeode=new osg::Geode;

   AxisGeode->addDrawable(Axis);

 

   //set some attribute

   osg::LineWidth* lineW=new osg::LineWidth;

   lineW->setWidth(3.0);

 

   osg::StateSet* stateset=AxisGeode->getOrCreateStateSet();

   stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

   stateset->setAttribute(lineW,osg::StateAttribute::ON);

   //End Draw Axis

 

   //Begin add Text

   osg::Geode* HudGeode=new osg::Geode;

   osgText::Text* textx = new osgText::Text();

   HudGeode->addDrawable(textx);

   osgText::Text* texty=new osgText::Text();

   HudGeode->addDrawable(texty);

   osgText::Text* textz=new osgText::Text();

   HudGeode->addDrawable(textz);

 

   // 设置HUD文字的参数

   textx->setCharacterSize(5);

   textx->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//宋体

   textx->setText(L"x 轴");

   textx->setAxisAlignment(osgText::Text::XZ_PLANE);

   textx->setAlignment(osgText::Text::CENTER_TOP);

   textx->setPosition( osg::Vec3(100.0,0.0,0.0) );

   textx->setColor( osg::Vec4(1.0, 0.0, 0.0, 1) );

 

 

   texty->setCharacterSize(5);

   texty->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体

   texty->setText(L"y 轴");

   texty->setAxisAlignment(osgText::Text::YZ_PLANE);

   texty->setAlignment(osgText::Text::CENTER_TOP);

   texty->setPosition( osg::Vec3(0.0,100.0,0.0) );

   texty->setColor( osg::Vec4(0.0, 1.0, 0.0, 1) );

 

   textz->setCharacterSize(5);

   textz->setFont("C:/WINDOWS/Fonts/SIMKAI.ttf");//楷体

   textz->setText(L"z 轴");

   textz->setAxisAlignment(osgText::Text::XZ_PLANE);

   textz->setAlignment(osgText::Text::CENTER_TOP);

   textz->setPosition(osg::Vec3(0.0,0.0,100.0));

   textz->setColor(osg::Vec4(0.0, 0.0, 1.0, 1));

 

   osg::Group* temp=new osg::Group;

   temp->addChild(HudGeode);

   temp->addChild(AxisGeode);

 

   //set backgroud color

   osg::ClearNode* backgroupcolor=new osg::ClearNode;

   backgroupcolor->setClearColor(osg::Vec4(1.0,1.0,1.0,0.0));

   temp->addChild(backgroupcolor);

 

   osgViewer::Viewer viewer;

   viewer.setSceneData( temp );

   viewer.run();

 

}