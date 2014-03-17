#include "Display.h"

void Display::addImage(sf::Image& im, sf::Vector2u loc, sf::IntRect rect)
{
	sf::Image newImage;
	newImage.create(wsize.x, wsize.y);
	newImage.copy(im, loc.x, loc.y);
	imgs.push(newImage);
}

void Display::compileImages(Screen* scr, unsigned int reqSpace)
{
	int creqSpace = reqSpace;
	while(!imgs.empty())
	{
		scr->addImage(imgs.front(), creqSpace);
		imgs.pop();
		if(reqSpace != -1)
			creqSpace++;
	}
}