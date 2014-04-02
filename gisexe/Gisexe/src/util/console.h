#ifndef _CONSOLE_H_
#define _CONSOLE_H_

class Console
{
public:
	static void alert(const char* format, ...);
	static void debug(const char* format, ...);
	static void log(const char* format, ...);
};

#endif