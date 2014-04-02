
#include <QMessageBox>
#include <stdarg.h>
#include "console.h"

void Console::alert( const char* format, ... )
{
	printf("Error : ");

	char buf[1024];
	va_list args;
	va_start( args, format );
	vsprintf( buf, format, args );
	va_end( args );
	printf(buf);

	QMessageBox::warning(NULL, "Invalid Operation !", buf);
}

void Console::log( const char* format, ... )
{
	printf("Log : ");

	char buf[1024];
	va_list args;
	va_start( args, format );
	vsprintf( buf, format, args );
	va_end( args );
	printf(buf);
}

void Console::debug( const char* format, ... )
{
	printf("Debug : ");

	char buf[1024];
	va_list args;
	va_start( args, format );
	vsprintf( buf, format, args );
	va_end( args );
	printf(buf);
}


