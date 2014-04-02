#ifndef __CREATEEARTH_H__
#define __CREATEEARTH_H__

#include <osg/Geometry>
#include <osg/Group>
#include <osg/Material>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osg/TexGen>
#include <osg/StateSet>
#include <osgDB/ReadFile>

osg::ref_ptr<osg::Group> createEarth(float radius, const std::string& textureName);

#endif //__CREATEEARTH_H__