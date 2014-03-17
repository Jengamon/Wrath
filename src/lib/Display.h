#ifndef WRATH_DISPLAY_H
#define WRATH_DISPLAY_H

#include "Screen.h"
#include <SFML/Graphics.hpp>
#include <queue>

class Display
{
public:
	Display(sf::Vector2u sz) : wsize(sz) {}
	void addImage(sf::Image&, sf::Vector2u, sf::IntRect = sf::IntRect(0,0,0,0));
	void compileImages(Screen*, unsigned int = -1);
private:
	sf::Vector2u wsize;
	std::queue<sf::Image> imgs;
};

#endif // WRATH_DISPLAY_H