#ifndef WRATH_SCREEN_H
#define WRATH_SCREEN_H

/**
@brief A collection of images.
This collects Images that will be rendererd, by merging them into one picture.
It is possible to shade the screen by giving this a shader.
*/

#include <SFML/Graphics.hpp>
#include <list>
// If you use the RT versions of compileImages, there's no need to get the shader to draw!
// Use the RT versions if you want real-time rendering, as it uses a RenderTexture rather
// than an Image. RT versions, though, return a RenderTexture, rather than a 
// simple Texture due to the fact that to return a texture, it would have to perform a slow copy.
class Screen
{
public:
	Screen(unsigned int imageLimit, sf::Vector2u sz) : imlim(imageLimit), wsize(sz), shd(nullptr) {}
	virtual ~Screen();
	bool addImage(sf::Image&, int ins = -1);
	void setShader(sf::Shader& shdr) { 
		if(sf::Shader::isAvailable())
			shd = &shdr; 
	}
	const sf::Shader* getShader() const { 
		if(sf::Shader::isAvailable())
			return shd;
	}
	sf::Texture* compileImagesND();
	sf::Texture* compileImages();
	sf::RenderTexture* compileImagesRTND();
	sf::RenderTexture* compileImagesRT();
private:
	unsigned int imlim;
	sf::Vector2u wsize;
	struct IImage
	{
		sf::Image im;
		int reqSpace;
	};
	sf::Shader* shd;
	std::list<IImage> images;
};

#endif // WRATH_SCREEN_H