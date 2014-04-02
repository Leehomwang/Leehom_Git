#ifndef __MAP_H__
#define __MAP_H__

#include <osg/Geometry>
#include <osg/Group>
#include <osg/Material>
#include <osg/Texture2D>
#include <osg/TexGen>
#include <osg/StateSet>
#include <osgDB/ReadFile>


osg::ref_ptr<osg::Group> createMap();

#endif //__MAP_H__