#include <QMouseEvent>
#include <QMessageBox>
#include <QAxAggregated>
#include <objsafe.h>
#include <QUuid>
#include <QtGui>
#include "glwidget.h"
#include "../io/rasterloader.h"
#include "../io/shploader.h"
#include "InfoDialog.h"

using namespace gis;

static std::vector<int> fieldIndices;
static std::vector<float3> colors;


GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
	
}

GLWidget::~GLWidget()
{

}

QSize GLWidget::sizeHint() const
{
	//return QSize(985, 575); // 默认大小
	return QSize(912, 572);
}

void GLWidget::initializeGL()
{
    _scene.init();

	//if (!ChinaLadder)
	//{
		// raster 加载中国DEM栅格数据
		RasterLoader* rasterLoader = new RasterLoader;
		rasterLoader->load("E:\\GIS\\data\\raster\\rastert_raster31.txt");
		//rasterLoader->load("E:\\GIS\\data\\raster\\ProvincialDEM\\山东省.txt");

		if (ChooseProjection)
		{
			Projector* projector = new SphereProjector(rasterLoader->getBBox()); // SphereProjector
			Painter::setProjector(projector);
		} 
		else
		{
			Projector* projector = new PlaneProjector(rasterLoader->getBBox()); // PlaneProjector
			Painter::setProjector(projector);
		}
		_chinaRaster.setRasterLoader(rasterLoader);
		//_chinaRaster.setLinearScaler(LinearScaler(0, 0.1));
		_chinaRaster.setLinearScaler(LinearScaler(0, ChinaHeight1));
		_chinaRaster.init();
	//} 
	//else
	//{
		//加载各省市SHP
		/*ShpLoader* ZJLoader = new ShpLoader;
		ZJLoader->load("E:\\GIS\\data\\shp\\ProvinceShp\\001.shp");

		_ZJShp.setShpLoader(ZJLoader);
		_ZJShp.setLinearScaler(LinearScaler(0,0.1));
		_ZJShp.init();*/

		//if (ChooseProjection)
		//{
		//	Projector* projector = new SphereProjector(ZJLoader->getBBox()); // SphereProjector
		//	Painter::setProjector(projector);
		//} 
		//else
		//{
		//	Projector* projector = new PlaneProjector(ZJLoader->getBBox()); // PlaneProjector
		//	Painter::setProjector(projector);
		//}

		
	//}
	
	
	
	

	// shape全球SHP数据
	ShpLoader* shpLoader = new ShpLoader;
	shpLoader->load("E:\\GIS\\data\\shp\\world\\ok0.shp");
	//shpLoader->load("E:\\GIS\\data\\shp\\ProvinceShp\\001.shp");
	_worldShp.setShpLoader(shpLoader);
	_worldShp.setLinearScaler(LinearScaler(-0.03, 0));
	_worldShp.init();
	
	// symbol
	if (DrawData)
	{
		ShpLoader* shpLoader1 = new ShpLoader;
		shpLoader1->load("E:\\GIS\\data\\shp\\sixxian\\point.shp");

		DbfLoader* dbfLoader = new DbfLoader;
		dbfLoader->load("E:\\GIS\\data\\shp\\sixxian\\point.dbf");

		_symbol.setShpLoader(shpLoader1);
		_symbol.setDbfLoader(dbfLoader);

		_symbol.setLinearScaler(LinearScaler(0, 0.2));


		switch(IndexStyle)
		{
		case 1:
			{
				_symbol.setChartType(SymbolModel::SPHERE); // SymbolModel::SPHERE 球
				//std::vector<int> fieldIndices;
				//fieldIndices.push_back(9);
				//std::vector<float3> colors;
				//float red[] = { 1, 0, 0 };
				//colors.push_back(red);
				/*GLWidget::ChooseIndex(5);
				GLWidget::SetIndexColor(58,89,129);*/
				_symbol.setColors(colors);
				colors.clear();
				_symbol.setFieldIndices(fieldIndices);
				fieldIndices.clear();
				_symbol.init();
			}
			break;
		case 2:
			{
				_symbol.setChartType(SymbolModel::BAR); // SymbolModel::BAR 圆柱
				/*std::vector<int> fieldIndices;
				fieldIndices.push_back(3);*/
				//std::vector<float3> colors;
				//float c1[] = { 0.8, 0.1, 0.3 };
				//colors.push_back(c1);
				_symbol.setColors(colors);
				colors.clear();
				_symbol.setFieldIndices(fieldIndices);
				fieldIndices.clear();
				_symbol.init();
			}
			break;
		case 3:
			{
				_symbol.setChartType(SymbolModel::STACKEDBAR); // SymbolModel::STACKEDBAR 层叠
				/*std::vector<int> fieldIndices;
				fieldIndices.push_back(9); 
				fieldIndices.push_back(7);
				fieldIndices.push_back(6);
				std::vector<float3> colors;
				float c1[] = { 0.8, 0.1, 0.3 };
				float c2[] = {.2, .6, 0.9};
				float c3[] = {.1, .7, .3};
				colors.push_back(c1);
				colors.push_back(c2);
				colors.push_back(c3);*/
				/*GLWidget::ChooseIndex(5);
				GLWidget::ChooseIndex(6);
				GLWidget::ChooseIndex(7);
				ChooseIndexColor(4);*/
				_symbol.setColors(colors);
				colors.clear();
				_symbol.setFieldIndices(fieldIndices);
				//int size = fieldIndices.size();
				fieldIndices.clear();
				_symbol.init();
			}
			break;
		case 4:
			{
				_symbol.setChartType(SymbolModel::PIE); // SymbolModel::PIE 饼状
				/*std::vector<int> fieldIndices;
				fieldIndices.push_back(4); 
				fieldIndices.push_back(5);
				fieldIndices.push_back(6);*/
				//std::vector<float3> colors;
				//float c1[] = { 0.8, 0.1, 0.3 };
				//float c2[] = {.2, .6, 0.9};
				//float c3[] = {.1, .7, .3};
				//colors.push_back(c1);
				//colors.push_back(c2);
				//colors.push_back(c3);
				_symbol.setColors(colors);
				colors.clear();
				_symbol.setFieldIndices(fieldIndices);
				fieldIndices.clear();
				_symbol.init();
			}
			break;
		}
	
	}
	//BuildFont();												// Build Our Font Display List
}

void GLWidget::paintGL()
{
	
	_scene.modelMatrix();
	
	glScaled(1.8,1.8,1.8);
	if (ChooseProjection)
	{
		glRotated(110, 1, 0, 0);
		glRotated(-65, 0, 0, 1);
		glPushMatrix();
		glRotated(180,1,0,0);
		glRotated(180,0,0,1);
		_earthball.paint();
		glPopMatrix();
		
	}
	else
	{
		glPushMatrix();
		glRotated(-90,1,0,0);
		_seaplane.paint(); 
		glPopMatrix();
		
	}
	_skybox.paint();
	if (!ChinaLadder)
	{
		//画中国DEM栅格数据
		_chinaRaster.paint();
	} 
	else
	{
		//画各省市SHP数据
		_ZJShp.paint();
	}
	
	_worldShp.paint();
	_symbol.paint();
	
	/*glRotated(-90, 1, 0, 0);
	if (ChooseProjection)
	{
		_earthball.paint();
	}
	else
		_seaplane.paint();
	_skybox.paint();*/
}

void GLWidget::resizeGL(int width, int height)
{
	_scene.resize(width, height);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() & Qt::LeftButton)
	{
		_scene.update(Scene::LBUTTONDOWN, event->x(), event->y());
	}
	if (event->button() & Qt::MidButton)
	{
		_scene.update(Scene::MBUTTONDOWN, event->x(), event->y());
	}
	if (event->button() & Qt::RightButton)
	{
		_scene.update(Scene::RBUTTONDOWN, event->x(), event->y());
	}
	updateGL();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (_scene.update(Scene::MOUSEMOVE, event->x(), event->y()))
	{
		updateGL();
	}
}

void GLWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() & Qt::LeftButton)
	{
		_scene.update(Scene::LBUTTONUP, event->x(), event->y());
	}
	if (event->button() & Qt::MidButton)
	{
		_scene.update(Scene::MBUTTONUP, event->x(), event->y());
	}
	if (event->button() & Qt::RightButton)
	{
		_scene.update(Scene::RBUTTONUP, event->x(), event->y());
	}
	updateGL();
}

void GLWidget::wheelEvent(QWheelEvent* event) 
{
	if (_scene.update(Scene::MOUSEWHEEL, event->delta()))
	{
		updateGL();
	}
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (event->button() & Qt::LeftButton)
	{
		InfoDialog *dialog = new InfoDialog;
		dialog->show();
		//Console::debug("X: %d Height: %d Y: %d\n", event->x(), height(), event->y());
		_symbol.pick(event->x(), height() - event->y());
		_worldShp.pick(event->x(), height() - event->y());
		//glPrint(event->x(),event->y(),"NeHe Productions");
	}
	else
	{
		_scene.update(Scene::RBUTTONDOUBLECLICK);
	}
	updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
	case Qt::Key_1:
		{
			std::vector<gis::float3> colors;
			int cn = rand() % 5 + 2;

			while (cn--)
			{
				float c[3] = { rand() % 256 / 255.0, rand() % 256 / 255.0, rand() % 256 / 255.0 };
				colors.push_back(c);
			}
			_chinaRaster.setColorMap(colors); // 颜色
		}
		break;
	case Qt::Key_2:
		{
			float h = rand() % 10 / 5.0;
			_chinaRaster.setDemHScaler(h); // 高度缩放
		}
		break;
	case Qt::Key_3:
		{
		}
		break;
	case Qt::Key_4:
		{
		}
		break;
	case Qt::Key_Escape:
		close();
		break;
	default:
		break;
	}

	_chinaRaster.paint(); // 显示调用，强制更新显示列表
	updateGL(); // 更新
}

void GLWidget::BuildFont()
{
	base=glGenLists(95);										// Creating 95 Display Lists
	//glBindTexture(GL_TEXTURE_2D, textures[9].texID);			// Bind Our Font Texture
	for (int loop=0; loop<95; loop++)							// Loop Through All 95 Lists
	{
		float cx=float(loop%16)/16.0f;							// X Position Of Current Character
		float cy=float(loop/16)/8.0f;							// Y Position Of Current Character

		glNewList(base+loop,GL_COMPILE);						// Start Building A List
		glBegin(GL_QUADS);									// Use A Quad For Each Character
		glTexCoord2f(cx,         1.0f-cy-0.120f); glVertex2i(0,0);	// Texture / Vertex Coord (Bottom Left)
		glTexCoord2f(cx+0.0625f, 1.0f-cy-0.120f); glVertex2i(16,0);	// Texutre / Vertex Coord (Bottom Right)
		glTexCoord2f(cx+0.0625f, 1.0f-cy);		  glVertex2i(16,16);// Texture / Vertex Coord (Top Right)
		glTexCoord2f(cx,         1.0f-cy);		  glVertex2i(0,16);	// Texture / Vertex Coord (Top Left)
		glEnd();											// Done Building Our Quad (Character)
		glTranslated(10,0,0);								// Move To The Right Of The Character
		glEndList();											// Done Building The Display List
	}	
}


void GLWidget::glPrint(GLint x, GLint y, const char *string)
{
	char		text[256];										// Holds Our String
	va_list		ap;												// Pointer To List Of Arguments

	if (string == NULL)											// If There's No Text
		return;													// Do Nothing

	va_start(ap, string);										// Parses The String For Variables
	vsprintf(text, string, ap);								// And Converts Symbols To Actual Numbers
	va_end(ap);													// Results Are Stored In Text

	//glBindTexture(GL_TEXTURE_2D, textures[9].texID);			// Select Our Font Texture
	glPushMatrix();												// Store The Modelview Matrix
	glLoadIdentity();											// Reset The Modelview Matrix
	glTranslated(x,y,0);										// Position The Text (0,0 - Bottom Left)
	glListBase(base-32);										// Choose The Font Set
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);			// Draws The Display List Text
	glPopMatrix();
}

void GLWidget::SetChinaHeight(int SetChinaH)
{
	DrawData = false;
	ChinaHeight1 = (float)SetChinaH/100;
	//_chinaRaster.setDemHScaler(ChinaHeight1);
	//_chinaRaster.paint(); // 显示调用，强制更新显示列表
	updateGL();
}

void GLWidget::SetChinaCorlor(int SetChianC)
{
	if (SetChianC == 1)
	{
		C1[0] = 1;C1[1] = 1;C1[2] = 1;
		C2[0] = 1;C2[1] = 0;C2[2] = 0;
		C3[0] = 1;C3[1] = 1;C3[2] = 0;
		C4[0] = 0;C4[1] = 1;C4[2] = 0;
		C5[0] = 0;C5[1] = 0;C5[2] = 1;
		//updateGL();
	}
	else if (SetChianC == 2)
	{
		C1[0] = 1;C1[1] = 0.87;C1[2] = 0.82;
		C2[0] = 0.06;C2[1] = 0.06;C2[2] = 0.06;
		C3[0] = 0.19;C3[1] = 0.18;C3[2] = 0.24;
		C4[0] = 0.16;C4[1] = 0.15;C4[2] = 0.11;
		C5[0] = 0.28;C5[1] = 0.75;C5[2] = 1;	
	}
	else if (SetChianC == 3)
	{
		C1[0] = 1.00;C1[1] = 0.53;C1[2] = 0.2;
		C2[0] = 1.00;C2[1] = 0.73;C2[2] = 0.2;
		C3[0] = 1.00;C3[1] = 0.93;C3[2] = 0.2;
		C4[0] = 0.87;C4[1] = 1.00;C4[2] = 0.2;
		C5[0] = 0.67;C5[1] = 1.00;C5[2] = 0.2;
	}
	else if (SetChianC == 4)
	{
		C1[0] = 0.36;C1[1] = 0.63;C1[2] = 0.84;
		C2[0] = 0.62;C2[1] = 0.84;C2[2] = 0.84;
		C3[0] = 0.96;C3[1] = 0.77;C3[2] = 0.65;
		C4[0] = 1.00;C4[1] = 0.62;C4[2] = 0.39;
		C5[0] = 0.45;C5[1] = 0.34;C5[2] = 0.27;
	}
	else if (SetChianC == 5)
	{
		C1[0] = 0.89;C1[1] = 0.81;C1[2] = 0.62;
		C2[0] = 0.69;C2[1] = 0.66;C2[2] = 0.55;
		C3[0] = 0.43;C3[1] = 0.54;C3[2] = 0.50;
		C4[0] = 0.35;C4[1] = 0.47;C4[2] = 0.52;
		C5[0] = 0.47;C5[1] = 0.37;C5[2] = 0.38;
	}
	else if (SetChianC == 6)
	{
		C1[0] = 0.6;C1[1] = 0.65;C1[2] = 0.72;
		C2[0] = 0.86;C2[1] = 0.88;C2[2] = 0.91;
		C3[0] = 0.75;C3[1] = 0.86;C3[2] = 0.87;
		C4[0] = 0.47;C4[1] = 0.69;C4[2] = 0.72;
		C5[0] = 0.57;C5[1] = 0.31;C5[2] = 0.44;
	}
}

void GLWidget::SetProjection(int SetProject)
{
	if (SetProject == 1)
	{
		ChooseProjection = true;
	} 
	else
	{
		ChooseProjection = false;
	}
}

void GLWidget::ChooseIndexStyle(int IndexSty)
{
	DrawData = true;
	IndexStyle = IndexSty;
}

//void GLWidget::ChooseIndex(int len,int Index, int count)
void GLWidget::ChooseIndex(int Index)//数据从4--14，其中4-11为万以上，12-14都是个位数
{
		fieldIndices.push_back(Index);
}

void GLWidget::ChooseIndexColor(int ColorType)//协商确定颜色类别
{
	switch(ColorType)
	{
	case 1:
		{
			float red[] = { 0.1, 0.8, 0.3 };//黄绿
			colors.push_back(red);
		}
	case 2:
		{
			float green[] = {0.8, 0.7, 0.3};//棕色
			colors.push_back(green);
		}
	case 3:
		{
			float c1[] = {0.8, 0.1, 0.3};//紫色
			float c2[] = {0.2, 0.6, 0.9};//蓝色
			colors.push_back(c1);
			colors.push_back(c2);
		}
	case 4:
		{
			float c1[] = {0.1, 0.7, 0.3};//绿色
			float c2[] = {0.2, 0.6, 0.9};//蓝色
			float c3[] = {0.8, 0.1, 0.3};//紫色
			colors.push_back(c1);
			colors.push_back(c2);
			colors.push_back(c3);
		}
	
	default:
		break;
		
	}
		

}

void GLWidget::SetIndexColor(int r, int g, int b)
{
	float _r = (float)r/255;
	float _g = (float)g/255;
	float _b = (float)b/255;
	float cc[] = {_r, _g, _b};
	colors.push_back(cc);
}

class ObjectSafetyImpl : public QAxAggregated, 
	public IObjectSafety
{
public:
	//! [1] //! [2]
	ObjectSafetyImpl() {}

	long queryInterface( const QUuid &iid, void **iface )
	{
		*iface = 0;
		if ( iid == IID_IObjectSafety )
			*iface = (IObjectSafety*)this;
		else
			return E_NOINTERFACE;

		AddRef();
		return S_OK;
	}

	//! [2] //! [3]
	QAXAGG_IUNKNOWN;

	//! [3] //! [4]
	HRESULT WINAPI GetInterfaceSafetyOptions( REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions )
	{
		*pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA | INTERFACESAFE_FOR_UNTRUSTED_CALLER;
		*pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA | INTERFACESAFE_FOR_UNTRUSTED_CALLER;
		return S_OK;
	}
	HRESULT WINAPI SetInterfaceSafetyOptions( REFIID riid, DWORD pdwSupportedOptions, DWORD pdwEnabledOptions )
	{
		return S_OK;
	}
};
//! [4] //! [5]

QAxAggregated *GLWidget::createAggregate()
{
	return new ObjectSafetyImpl();
}
//! [5]