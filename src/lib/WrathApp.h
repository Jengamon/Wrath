#ifndef WRATH_WRATHAPP_H
#define WRATH_WRATHAPP_H

#include "RenderManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "ScriptManager.h"
#include <Pluma/Pluma.hpp>

class ScriptManager;

class WrathApp
{
public:
	WrathApp() : renderManager(nullptr), inputManager(nullptr), audioManager(nullptr), scriptManager(nullptr), managerLoader(nullptr) {}
	int run(std::string audio, std::string script, std::string folder, unsigned int width, unsigned int height, std::string title, std::string managerFolder);

	RenderManager* renderManager;
	InputManager* inputManager;
	AudioManager* audioManager;
	ScriptManager* scriptManager;
	void update();
	void updatePlugins();
private:
	bool initApp(std::string audio, std::string script, unsigned int width, unsigned int height, std::string title, std::string managerFolder);
	int runApp(std::string folderName);
	void cleanupApp();

	pluma::Pluma* managerLoader;
};

#endif // WRATH_WRATHAPP_H