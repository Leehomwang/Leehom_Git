#ifndef __CREATECOORDINATE_H__
#define __CREATECOORDINATE_H__
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/LineWidth>
#include <osg/Node>
#include <osg/PrimitiveSet>
#include <osgText/Text>


#ifdef _DEBUG
#pragma comment(lib,"osgViewerd.lib")
#pragma comment(lib,"osgDBd.lib")
#pragma comment(lib, "OpenThreadsd.lib")
#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgGAd.lib")
#pragma comment(lib, "osgUtild.lib")
#pragma comment(lib, "osgTextd.lib")
//#pragma comment(lib,"opengl32d.lib")
//#pragma comment(lib,"glu32d.lib")
#else
#pragma comment(lib,"osgViewer.lib")
#pragma comment(lib,"osgDB.lib")
#pragma comment(lib, "OpenThreads.lib")
#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgGA.lib")
#pragma comment(lib, "osgUtil.lib")
#pragma comment(lib, "osgText.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#endif



osg::ref_ptr<osg::Group> createCoordinate();

#endif //__CREATECOORDINATE_H__