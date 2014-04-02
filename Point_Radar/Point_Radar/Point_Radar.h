#ifndef __POINT_RADAR_H__
#define __POINT_RADAR_H__

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <osg/Image>
#include <osg/Texture2D>
#include <osg/Geometry>
#include <osg/TexGen>
#include <osg/TexEnv>
#include <osgDB/fstream>
#include <osgDB/FileUtils>
#include <osgDB/Input>
#include <osgDB/ReadFile>
#include <osgUtil/SmoothingVisitor>
#include <math.h>
#include <vector>
#include <fstream>

#include "MyPoint.h"

#ifdef _DEBUG
#pragma comment(lib,"osgViewerd.lib")
#pragma comment(lib,"osgDBd.lib")
#pragma comment(lib, "OpenThreadsd.lib")
#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgGAd.lib")
#pragma comment(lib, "osgUtild.lib")
//#pragma comment(lib,"opengl32d.lib")
//#pragma comment(lib,"glu32d.lib")
#else
#pragma comment(lib,"osgViewer.lib")
#pragma comment(lib,"osgDB.lib")
#pragma comment(lib, "OpenThreads.lib")
#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgGA.lib")
#pragma comment(lib, "osgUtil.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#endif


int IsWhiteSpace (char c);

//osg::ref_ptr<osg::Vec3Array> createPoints();
osg::ref_ptr<osg::Vec3Array> createPoints(const char* filename, int numbOfPoints);
osg::ref_ptr<osg::IntArray> createIndeies(int numbOfPoints);

#endif //__POINT_RADAR_H__