#include <QMessageBox>
#include <QApplication>
#include <QAxFactory>
#include <QtOpenGL>
#include <QDir>
#include "ui/glwidget.h"
#include <iostream>


QAXFACTORY_DEFAULT( GLWidget,
	"{19B8F36A-6B41-41c2-948A-4A08DF148CAC}",
	"{E5C700A4-99E6-414c-8B63-A165F29FCD56}",
	"{22EE5C0C-6874-4399-9DC1-46864A38DBF4}",
	"{2205B8AC-0967-4bbd-9BBE-AA6B53E3C997}",
	"{53592D1B-89CB-4720-9BEF-E4F1E5409F11}"
	)

int main(int argc, char *argv[])
{
	
	QApplication app(argc, argv);

	if ( !QGLFormat::hasOpenGL() ) {
		qWarning( "This system has no OpenGL support. Exiting." );
		return -1;
	}

	if ( !QAxFactory::isServer() ) {
		//QMessageBox::about(NULL,"About","the application is not a server!");
		GLWidget a;
		a.show();
		return app.exec();
	}
	else 
		return app.exec();
}
