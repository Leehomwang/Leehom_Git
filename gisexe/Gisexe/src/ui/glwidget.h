
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QAxBindable>
#include "scene.h"
#include "../model/chinarastermodel.h"
#include "../model/worldshpmodel.h"
#include "../model/symbolmodel.h"
#include "../painter/skybox.h"
#include "../painter/earthball.h"
#include "../painter/seaplane.h"
#include "../parameter/parameter.h"

class GLWidget : public QGLWidget, public QAxBindable // 绘制widget
{
  Q_OBJECT

public:
  GLWidget(QWidget *parent = 0);
  ~GLWidget();

  QSize sizeHint() const;
  QAxAggregated *createAggregate();

public slots:
	void SetChinaHeight(int SetChinaH);
	void SetChinaCorlor(int SetChinaC);
	void SetProjection(int SetProject);
	void ChooseIndexStyle(int IndexSty);
	//void ChooseIndex(int len,int Index,int count);
	void ChooseIndex(int Index);
	void ChooseIndexColor(int ColorType);
	void SetIndexColor(int r, int g, int b);

protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);

  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseDoubleClickEvent(QMouseEvent* event);
  void wheelEvent(QWheelEvent* event);
	void keyPressEvent(QKeyEvent* event);

	void BuildFont();
	void glPrint(int x, int y, const char *string);
private:
	Scene _scene;

	//中国DEM栅格数据
	gis::ChinaRasterModel _chinaRaster;
	//中国各省SHP数据
	gis::WorldShpModel _ZJShp;
	//
	gis::WorldShpModel _worldShp;
	gis::SymbolModel _symbol;
	gis::SkyBox _skybox;
	gis::EarthBall _earthball;
	gis::SeaPlane _seaplane;

	GLuint		base;												// Font Display List
};

#endif
