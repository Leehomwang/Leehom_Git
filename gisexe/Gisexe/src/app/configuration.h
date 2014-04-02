#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include "../util/vec.h"

class Configuration
{
public:
	Configuration();
protected:
};

class ConfigurationFactory
{
public:
	ConfigurationFactory();
	static Configuration& getConfiguration() { return _config; }
protected:
	static Configuration _config;
};
#endif 
