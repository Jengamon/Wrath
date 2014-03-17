#ifndef WRATH_SCRIPTMANAGER_H
#define WRATH_SCRIPTMANAGER_H

#include <Pluma/Pluma.hpp>
#include <string>
#include "WrathApp.h"

class WrathApp;

class ScriptManager
{
public:
	virtual std::string getName() const = 0;
	virtual void init() = 0;
	virtual void createBinding(WrathApp*) = 0;
	virtual int executeScript(std::string, std::string) = 0;
	virtual void deleteBinding(WrathApp*) = 0;
	virtual void deinit() = 0;
	virtual void update() = 0;
};

PLUMA_PROVIDER_HEADER(ScriptManager);

#endif // WRATH_SCRIPTMANAGER_H