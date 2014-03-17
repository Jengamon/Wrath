#ifndef WRATH_INPUTMANAGER_H
#define WRATH_INPUTMANAGER_H

#include "RenderManager.h"
#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>
#include <string>
#include <functional>
#include <map>

enum class Keys
{
	L,
	R,
	A,
	B,
	C,
	X,
	Y,
	Z,
	ESC,
	START,
	SELECT,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

using InputCallback = std::function<void(thor::ActionContext<Keys>)>;

class InputManager;

class InputListener
{
public:
	virtual void setupInput(InputManager*) = 0;
};

class InputManager
{
public:
	InputManager(RenderManager*);
	void handleEvents();
	void setupDefaultKeys();

	void setCloseKey(sf::Keyboard::Key);
	void setKey(Keys, sf::Keyboard::Key, thor::Action::ActionType = thor::Action::PressOnce);
	sf::Keyboard::Key getPKey(Keys);
	thor::Action::ActionType getActionType(Keys);
	void setRawKey(Keys, thor::Action);
	thor::Action getKey(Keys);
	void setupListener(InputListener*);
	thor::Connection registerCallback(Keys, InputCallback);
	void setListenToCallbacks(bool);
	bool getListenToCallbacks() const;
private:
	thor::ActionMap<Keys> keypad;
	thor::ActionMap<Keys>::CallbackSystem triggers;
	sf::RenderWindow* win;
	std::map<Keys, std::pair<sf::Keyboard::Key, thor::Action::ActionType>> keyData;
	bool listenCallback;
};

#endif // WRATH_INPUTMANAGER_H