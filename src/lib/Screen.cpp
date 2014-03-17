#include "Screen.h"
#include "types.h"
// We use a reference to redeuce copying, as this is a heavy resource, but we don't want pointers, as we can't be sure
// as whether we own it, or another part, such as the TilesetManager, owns it. I will change it once that get clearer in the future.
bool Screen::addImage(sf::Image& im, int ins)
{
	IImage img;
	img.im = im;
	img.reqSpace = ins;
	// Make sure we aren't going over the image limit. It's an arbitrary limit that can be set, but it helps limit calls to the amount of parts using the screen.
	// A ScreenManager is helpful, as it optimizes the image limit for each screen. You can turn it off by setting it to 0.
	if(images.size() + 1 <= imlim || imlim == 0)
	{
		if(ins == -1) // Request for bottom most space
		{
			images.push_front(img);
			return true;
		}
		for(auto i = images.begin(); i != images.end(); i++)
		{
			if(i->reqSpace < ins) // We found something that we go after!
			{
				images.insert(i++, img);
				return true;
			}
		}
		images.push_back(img);
		return true;
	}
	return false;
}

sf::Texture* Screen::compileImagesND()
{
	sf::Image itct;
	itct.create(wsize.x, wsize.y, ClearColor);
	for(auto i = images.begin(); i != images.end(); i++)
	{
		#ifdef _ALLOW_BLACK_MASK
			i->im.createMaskFromColor(sf::Color::Black);
			#warning Using black as a mask color may produce undesirable effects, as black is a common color.
		#else 
			i->im.createMaskFromColor(sf::Color::Black);
		#endif
		itct.copy(i->im, 0, 0, sf::IntRect(0,0,0,0), true);
	}
	// Create a texture on the heap. DROP CONTROL, AS USER WILL DELETE THE TEXTURE WHEN IT IS DONE WITH IT.
	sf::Texture* texture = new sf::Texture;
	texture->loadFromImage(itct);
	texture->setSmooth(true);
	if(shd != nullptr)
		shd->setParameter("texture", sf::Shader::CurrentTexture);
	return texture;
}

sf::Texture* Screen::compileImages()
{
	sf::Texture* tex = compileImagesND();
	images.clear(); // Clear all images, and prepare for a new frame
	return tex;
}

sf::RenderTexture* Screen::compileImagesRTND()
{
	sf::RenderTexture* itct = new sf::RenderTexture;
	if(!itct->create(wsize.x, wsize.y))
		return nullptr;

	if(shd != nullptr)
		shd->setParameter("texture", sf::Shader::CurrentTexture);

	itct->clear(ClearColor);
	for(auto i = images.begin(); i != images.end(); i++)
	{
		#ifdef _ALLOW_BLACK_MASK
			i->im.createMaskFromColor(sf::Color::Black);
			#warning Using black as a mask color may produce undesirable effects, as black is a common color.
		#else
			i->im.createMaskFromColor(sf::Color::Magenta);
		#endif
		sf::Texture tex;
		tex.loadFromImage(i->im);
		tex.setSmooth(true);
		itct->draw(sf::Sprite(tex), shd);
	}

	itct->display();

	return itct;
}

sf::RenderTexture* Screen::compileImagesRT()
{
	sf::RenderTexture* tex = compileImagesRTND();
	images.clear(); // Clear all images, and prepare for a new frame
	return tex;
}

Screen::~Screen()
{
	// delete shd;
}