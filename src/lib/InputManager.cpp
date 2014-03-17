#include "InputManager.h"
#include <cassert>

InputManager::InputManager(RenderManager* rm) : listenCallback(true)
{
	assert(rm != nullptr);
	win = &rm->getWindow();

	// Setup Keys!
	setCloseKey(sf::Keyboard::Escape);//way to close the window
	setupDefaultKeys();
}

void InputManager::setupDefaultKeys()
{
	// The rest are editable by the user
	// TODO Add a way for this

	setKey(Keys::L, sf::Keyboard::Q);
	setKey(Keys::R, sf::Keyboard::P);

	setKey(Keys::A, sf::Keyboard::A);
	setKey(Keys::B, sf::Keyboard::S);
	setKey(Keys::C, sf::Keyboard::Z);

	setKey(Keys::X, sf::Keyboard::K);
	setKey(Keys::Y, sf::Keyboard::L);
	setKey(Keys::Z, sf::Keyboard::M);

	setKey(Keys::UP, sf::Keyboard::Up);
	setKey(Keys::DOWN, sf::Keyboard::Down);
	setKey(Keys::LEFT, sf::Keyboard::Left);
	setKey(Keys::RIGHT, sf::Keyboard::Right);

	setKey(Keys::START, sf::Keyboard::Return);
	setKey(Keys::SELECT, sf::Keyboard::Space);
}

void InputManager::setCloseKey(sf::Keyboard::Key key)
{
	keypad[Keys::ESC] = thor::Action(key, thor::Action::PressOnce) || thor::Action(sf::Event::Closed);
	// Avoid not saving the connection! This is only done to ensure that the window closes!
	registerCallback(Keys::ESC, [&] (thor::ActionContext<Keys>) { win->close(); });
}

void InputManager::setKey(Keys vkey, sf::Keyboard::Key pkey, thor::Action::ActionType actyp)
{
	if(vkey != Keys::ESC)
	{
		setRawKey(vkey, thor::Action(pkey, actyp));
		std::pair<sf::Keyboard::Key, thor::Action::ActionType> pair(pkey, actyp);
		keyData[vkey] = pair;
	}
}

sf::Keyboard::Key InputManager::getPKey(Keys vkey)
{
	if(keyData.find(vkey) != keyData.end())
	{
		return keyData[vkey].first;
	}
}

thor::Action::ActionType InputManager::getActionType(Keys vkey)
{
	if(keyData.find(vkey) != keyData.end())
	{
		return keyData[vkey].second;
	}
}

void InputManager::setRawKey(Keys vkey, thor::Action act)
{
	if(vkey != Keys::ESC)
	{
		keypad[vkey] = act;
		keyData.erase(vkey);
	}
}

thor::Action InputManager::getKey(Keys vkey)
{
	return keypad[vkey];
}

thor::Connection InputManager::registerCallback(Keys vkey, InputCallback call)
{
	return triggers.connect(vkey, call);
}

void InputManager::setupListener(InputListener* listen)
{
	listen->setupInput(this);
}

void InputManager::setListenToCallbacks(bool in)
{
	listenCallback = in;
}

bool InputManager::getListenToCallbacks() const
{
	return listenCallback;
}

void InputManager::handleEvents()
{
	keypad.update(*win);

	if(listenCallback)
		keypad.invokeCallbacks(triggers, win);
}