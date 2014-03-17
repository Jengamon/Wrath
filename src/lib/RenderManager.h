#ifndef WRATH_RENDERMANAGER_H
#define WRATH_RENDERMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "Screen.h"

class RenderManager;

class RenderListener
{
public:
	virtual void render(RenderManager*) = 0;
	virtual ~RenderListener() {}
};

using ListenerHandle = std::list<RenderListener*>::iterator;
class RenderManager
{
public:
	RenderManager(unsigned int w, unsigned int h, std::string n) : win(sf::VideoMode(w, h), n), currentScreen(nullptr), shader(nullptr) {}
	virtual ~RenderManager();
	Screen* getCurrentScreen();
	sf::RenderWindow& getWindow();
	ListenerHandle addListener(RenderListener*);
	void deleteListener(ListenerHandle);
	void removeListener(ListenerHandle);
	Screen* nextFrame();

	void setShader(sf::Shader* shd) { if(sf::Shader::isAvailable()) shader = shd; }
	bool isShaderSet() { return shader != nullptr; }
	sf::Shader* getShader() { return shader; }
	void createNewScreen(unsigned int);
private:

	sf::RenderWindow win;
	std::list<RenderListener*> listeners;
	Screen* currentScreen;
	sf::Shader* shader;
};

#endif // WRATH_RENDERMANAGER_H