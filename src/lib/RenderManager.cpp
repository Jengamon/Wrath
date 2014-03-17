#include "RenderManager.h"
#include <iostream>

Screen* RenderManager::getCurrentScreen()
{
	return currentScreen;
}

sf::RenderWindow& RenderManager::getWindow()
{
	return win;
}

ListenerHandle RenderManager::addListener(RenderListener* listener)
{
	listeners.push_back(listener);
	return --listeners.end();
}

void RenderManager::deleteListener(ListenerHandle hndl)
{
	delete *hndl;
	removeListener(hndl);
}

void RenderManager::removeListener(ListenerHandle hndl)
{
	listeners.erase(hndl);
}

Screen* RenderManager::nextFrame()
{
	Screen* oldScreen = currentScreen;
	if(shader != nullptr)
	{
		oldScreen->setShader(*shader);
	}
	createNewScreen(0);
	for(auto i = listeners.begin(); i != listeners.end(); i++)
	{
		(*i)->render(this);
	}
	if(oldScreen != nullptr)
		return oldScreen;
	else
		return nextFrame();
}

void RenderManager::createNewScreen(unsigned int sz)
{
	currentScreen = new Screen(sz, win.getSize());
}

RenderManager::~RenderManager()
{
	for(auto i = listeners.begin(); i != listeners.end(); i++)
	{
		delete *i;
	}
	listeners.clear();
	delete shader;
}