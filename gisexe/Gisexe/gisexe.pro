TEMPLATE      = app
TARGET	 = gisexe

CONFIG	+= qt warn_off qaxserver

QT += opengl

RC_FILE	 += src/qaxserver.rc

HEADERS	 += src/app/configuration.h\
		src/io/shp/shapefil.h\
		src/io/dbfloader.h\
		src/io/rasterloader.h\
		src/io/shploader.h\
		src/io/loader.h\
		src/model/seidel/interface.h\
		src/model/seidel/mytri.h\
		src/model/seidel/triangulate.h\
		src/model/chinarastermodel.h\
		src/model/fan.h\
		src/model/ladder.h\
		src/model/model.h\
		src/model/pie.h\
		src/model/stackedbar.h\
		src/model/symbolmodel.h\
		src/model/worldshpmodel.h\
		src/painter/earthball.h\
		src/painter/mesh.h\
		src/painter/painter.h\
		src/painter/projector.h\
		src/painter/seaplane.h\
		src/painter/skybox.h\
		src/painter/sphere.h\
		src/parameter/parameter.h\
		src/ui/arcball.h\
		src/ui/glwidget.h\
		src/ui/InfoDialog.h\
		src/ui/scene.h\
		src/util/common.h\
		src/util/console.h\
		src/util/linearcolor.h\
		src/util/texture.h\
		src/util/util.h\
		src/util/vec.h\
	   
SOURCES  +=src/app/configuration.cpp\ 
		src/io/shp/dbfopen.cpp\
		src/io/shp/shpopen.cpp\
		src/io/dbfloader.cpp\
		src/io/rasterloader.cpp\
		src/io/shploader.cpp\
		src/io/loader.cpp\
		src/model/seidel/construct.c\
		src/model/seidel/misc.c\
		src/model/seidel/monotone.c\
		src/model/seidel/mytri.cpp\
		src/model/seidel/tri.c\
		src/model/chinarastermodel.cpp\
		src/model/fan.cpp\
		src/model/ladder.cpp\
		src/model/model.cpp\
		src/model/pie.cpp\
		src/model/stackedbar.cpp\
		src/model/symbolmodel.cpp\
		src/model/worldshpmodel.cpp\
		src/painter/earthball.cpp\
		src/painter/mesh.cpp\
		src/painter/painter.cpp\
		src/painter/projector.cpp\
		src/painter/seaplane.cpp\
		src/painter/skybox.cpp\
		src/painter/sphere.cpp\
		src/parameter/parameter.cpp\
		src/ui/arcball.cpp\
		src/ui/glwidget.cpp\
		src/ui/InfoDialog.cpp\
		src/ui/scene.cpp\
		src/util/console.cpp\
		src/util/linearcolor.cpp\
		src/util/texture.cpp\
		src/util/util.cpp\
		src/main.cpp\

# install
#target.path = D:\GIS\Codes\gisexe\Gisexe
#sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS gisexe.pro
#sources.path = D:\GIS\Codes\gisexe\Gisexe
#INSTALLS += target sources