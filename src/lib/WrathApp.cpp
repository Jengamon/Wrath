#include "WrathApp.h"
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Display.h"

#include "TestScreen.hpp"
#include <iostream>

// Start on the SFML stuff

int WrathApp::run(std::string audio, std::string script, std::string folder, unsigned int width, unsigned int height, std::string title, std::string managerFolder)
{
	if(!initApp(audio, script, width, height, title, managerFolder))
	{
		return -1; // Failed to initialize error code
	}
	int i = runApp(folder);
	cleanupApp();
	return i; // Return code
}

bool WrathApp::initApp(std::string audio, std::string script, unsigned int width, unsigned int height, std::string title, std::string managerFolder)
{
	renderManager = new RenderManager(width, height, title);
	inputManager = new InputManager(renderManager);

	managerLoader = new pluma::Pluma;
	managerLoader->acceptProviderType<AudioManagerProvider>();
	managerLoader->acceptProviderType<ScriptManagerProvider>();
	// Load the plugins
	managerLoader->loadFromFolder("managers", true);

	std::vector<AudioManagerProvider*> audioManagers;
	managerLoader->getProviders(audioManagers);
	for(auto i = audioManagers.begin(); i != audioManagers.end(); i++)
	{
		AudioManager* audmn = (*i)->create();
		if(audmn->getName() == audio)
		{
			audioManager = audmn;
		}
	}
	if(audioManager == nullptr)
	{
		std::cout << "Audio manager not found: " << audio << std::endl;
		return false;
	}
	std::cout << "* Audio Manager: " << audioManager->getName() << std::endl;
	audioManager->init();

	#ifdef _COMPILE_IN_DEMO
		auto testscr = new TestScreen();
		renderManager->addListener(testscr);
		inputManager->setupListener(testscr);
		audioManager->setupListener(testscr);
	#endif
	
	std::vector<ScriptManagerProvider*> scriptManagers;
	managerLoader->getProviders(scriptManagers);
	for(auto i = scriptManagers.begin(); i != scriptManagers.end(); i++)
	{
		ScriptManager* scrptmn = (*i)->create();
		if(scrptmn->getName() == script)
		{
			scriptManager = scrptmn;
		}
	}
	if(scriptManager == nullptr)
	{
		std::cout << "Script manager not found: " << script << std::endl;
		return false;
	}
	std::cout << "* Script Manager: " << scriptManager->getName() << std::endl;
	scriptManager->init();
	scriptManager->createBinding(this);
	
	return true;
}

int WrathApp::runApp(std::string folderName)
{
	return scriptManager->executeScript(folderName, "main");
}

void WrathApp::update()
{
	sf::RenderWindow& win = renderManager->getWindow();
	inputManager->handleEvents();
	win.clear();
	Screen* renderScreen = renderManager->nextFrame();
	sf::Texture* tex = renderScreen->compileImages();
	win.draw(sf::Sprite(*tex), renderScreen->getShader());
	delete renderScreen;
	win.display();
	delete tex;
	updatePlugins();
}

void WrathApp::updatePlugins()
{
	audioManager->update();
	scriptManager->update();
}

void WrathApp::cleanupApp()
{
	scriptManager->deinit();

	delete inputManager;
	delete renderManager;
	delete audioManager;
	delete scriptManager;
	delete managerLoader;
}