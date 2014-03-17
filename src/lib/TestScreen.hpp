#ifndef WRATH_TESTSCREEN_HPP
#define WRATH_TESTSCREEN_HPP

#include "RenderManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Display.h"
#include <iostream>

class TestScreen : public RenderListener, public InputListener, public AudioListener
{
public:
	TestScreen() : sx(30), sy(30), sc(sf::Color(30,2,100)) {}
	virtual void render(RenderManager* rm)
	{
		sf::Image spr;
		spr.create(30, 30, sc);

		Display disp(rm->getWindow().getSize());
		disp.addImage(spr, sf::Vector2u(sx, sy));

		Screen* scr = rm->getCurrentScreen();
		disp.compileImages(scr, 0);
		//std::cout << std::boolalpha << res[0] << "<" << res[1] << ":" << res[2] << std::noboolalpha << std::endl;
	}

	virtual void setupInput(InputManager* im)
	{
		InputCallback down = [&] (thor::ActionContext<Keys> cxt) {
			if(sy < cxt.window->getSize().y - 30)
				sy += 30;
		};

		InputCallback up = [&] (thor::ActionContext<Keys>) {
			if(sy > 0)
				sy -= 30;
		};

		InputCallback left = [&] (thor::ActionContext<Keys>) {
			if(sx > 0)
				sx -= 30;
		};

		InputCallback right = [&] (thor::ActionContext<Keys> cxt) {
			if(sx < cxt.window->getSize().x - 30)
				sx += 30;
		};

		InputCallback a = [&] (thor::ActionContext<Keys>) {
			if(sc == sf::Color(30,2,100))
				sc = sf::Color(100,2,30);
			else
				sc = sf::Color(30,2,100);
		};

		downCon = im->registerCallback(Keys::DOWN, down);
		upCon = im->registerCallback(Keys::UP, up);
		leftCon = im->registerCallback(Keys::LEFT, left);
		rightCon = im->registerCallback(Keys::RIGHT, right);
		aCon = im->registerCallback(Keys::A, a);
	}

	virtual void setupAudio(AudioManager* _am) {}

	virtual ~TestScreen()
	{
		downCon.disconnect();
		upCon.disconnect();
		leftCon.disconnect();
		rightCon.disconnect();
		aCon.disconnect();
		bCon.disconnect();
	}
private:
	thor::Connection downCon;
	thor::Connection upCon;
	thor::Connection leftCon;
	thor::Connection rightCon;
	thor::Connection aCon;
	thor::Connection bCon;
	int sy;
	int sx;
	sf::Color sc;
};

#endif // WRATH_TESTSCREEN_HPP