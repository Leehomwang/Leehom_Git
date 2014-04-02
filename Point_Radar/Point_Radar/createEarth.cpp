#include "createEarth.h"

osg::ref_ptr<osg::Material> creatMaterial(osg::Vec4f materialAmbi, osg::Vec4f materialDiff, osg::Vec4f materialSpec, float materialShin)
{
	osg::ref_ptr<osg::Material> material = new osg::Material;
	material->setAmbient(osg::Material::FRONT_AND_BACK, materialAmbi);
	material->setDiffuse(osg::Material::FRONT_AND_BACK, materialDiff);
	material->setSpecular(osg::Material::FRONT_AND_BACK, materialSpec);
	material->setShininess(osg::Material::FRONT_AND_BACK, materialShin);
	return material;
}

osg::ref_ptr<osg::Group> createEarth(float radius, const std::string& textureName)
{
	osg::ref_ptr<osg::Geometry> sPlanetSphere = new osg::Geometry;

	// set the single colour so bind overall
	//osg::ref_ptr<osg::Vec4Array> colours = new osg::Vec4Array(1);
	//(*colours)[0] = color;
	//sPlanetSphere->setColorArray(colours);
	//sPlanetSphere->setColorBinding(osg::Geometry::BIND_OVERALL);

	// now set up the coords, normals and texcoords for geometry 
	unsigned int numX = 100;
	unsigned int numY = 50;
	unsigned int numVertices = numX*numY;

	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array(numVertices);
	sPlanetSphere->setVertexArray(coords);

	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array(numVertices);
	sPlanetSphere->setNormalArray(normals);
	sPlanetSphere->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);

	osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array(numVertices);
	sPlanetSphere->setTexCoordArray(0,texcoords);
	sPlanetSphere->setTexCoordArray(1,texcoords);

	double delta_elevation = osg::PI / (double)(numY-1);
	double delta_azim = 2.0*osg::PI / (double)(numX-1);
	float delta_tx = 1.0 / (float)(numX-1);
	float delta_ty = 1.0 / (float)(numY-1);

	double elevation = -osg::PI*0.5;
	float ty = 0.0;
	unsigned int vert = 0;
	unsigned j;
	for(j=0; j<numY; ++j, elevation+=delta_elevation, ty+=delta_ty )
	{
		double azim = 0.0;
		float tx = 0.0;
		for(unsigned int i=0; i<numX; ++i, ++vert, azim+=delta_azim, tx+=delta_tx)
		{
			osg::Vec3 direction(cos(azim)*cos(elevation), sin(azim)*cos(elevation), sin(elevation));
			(*coords)[vert].set(direction*radius);
			(*normals)[vert].set(direction);
			(*texcoords)[vert].set(tx,ty);
		}
	}

	for(j=0; j<numY-1; ++j)
	{
		unsigned int curr_row = j*numX;
		unsigned int next_row = curr_row+numX;
		osg::DrawElementsUShort* elements = new osg::DrawElementsUShort(GL_QUAD_STRIP);
		for(unsigned int i=0;
			i<numX;
			++i)
		{
			elements->push_back(next_row + i);
			elements->push_back(curr_row + i);
		}
		sPlanetSphere->addPrimitiveSet(elements);
	}

	// create a geode object to as a container for our drawable sphere object
	osg::ref_ptr<osg::Geode> geodePlanet = new osg::Geode();
	//geodePlanet->setName( name );

	if( !textureName.empty() )
	{
		osg::Image* image = osgDB::readImageFile( textureName );
		if ( image )
		{
			osg::Texture2D* tex2d = new osg::Texture2D( image );
			tex2d->setWrap( osg::Texture::WRAP_S, osg::Texture::REPEAT );
			tex2d->setWrap( osg::Texture::WRAP_T, osg::Texture::REPEAT );
			geodePlanet->getOrCreateStateSet()->setTextureAttributeAndModes( 0, tex2d, osg::StateAttribute::ON );

			// reset the object color to white to allow the texture to set the colour.
			//sPlanetSphere->setColor( osg::Vec4(1.0f,1.0f,1.0f,1.0f) );
		}
	}
	osg::ref_ptr<osg::Material> material1 = creatMaterial(osg::Vec4f(1.0,1.0,1.0,1.0),osg::Vec4f(1.0,1.0,1.0,0.5),osg::Vec4f(0.0,0.0,1.0,1.0),0.5);
	//…Ë÷√◊¥Ã¨
	osg::ref_ptr<osg::StateSet> texState = geodePlanet->getOrCreateStateSet();
	//…Ë÷√Œ∆¿Ì◊¥Ã¨
	texState->setAttributeAndModes(material1.get(), osg::StateAttribute::ON);

	// add our drawable sphere to the geode container
	geodePlanet->addDrawable( sPlanetSphere );

	osg::ref_ptr<osg::Group> earth = new osg::Group;

	earth->addChild(geodePlanet);
	
	return( earth );
}