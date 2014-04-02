#ifndef __CREATERADAR_H__
#define __CREATERADAR_H__

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

osg::ref_ptr<osg::Group> CreateRadar(const char* filename, osg::Vec4 color, int numbOfPoints);

osg::ref_ptr<osg::Texture2D> texture2D (const char* imagefile);

#endif //__CREATERADAR_H__