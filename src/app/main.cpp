#include "lib/WrathApp.h"

// Test Image
#include <SFML/Graphics.hpp>
#include "lib/Screen.h"
#include <iostream>
#include <string>
#include <tclap/CmdLine.h>

int main(int argc, char* argv[])
{
	std::string audio;
	std::string script;
	std::string folder;
	unsigned int width;
	unsigned int height;
	std::string title;
	std::string managerFolder;
	try
	{
		TCLAP::CmdLine cmd("Wrath Game Interpreter", ' ', "0.1");
		TCLAP::ValueArg<std::string> audioArg("a", "audioManager", "AudioManager plugin to use", true, "", "string", cmd);
		TCLAP::ValueArg<std::string> scriptArg("s", "scriptManager", "ScriptManager plugin to use", true, "", "string", cmd);
		TCLAP::ValueArg<unsigned int> widthArg("w", "width", "Window width (Default 400)", false, 400, "positive integer", cmd);
		TCLAP::ValueArg<unsigned int> heightArg("t", "height", "Window height (Default 300)", false, 300, "positive integer", cmd);
		TCLAP::ValueArg<std::string> titleArg("n", "name", "Name of the game", false, "Unnamed Wrath Game", "string", cmd);
		TCLAP::ValueArg<std::string> managerFolderArg("m", "managerFolder", "Folder that contains the manager code", false, "managers", "string", cmd);
		TCLAP::UnlabeledValueArg<std::string> folderArg("folder", "Folder that contains the main script", true, "", "string", cmd);

		cmd.parse(argc, argv);

		audio = audioArg.getValue();
		script = scriptArg.getValue();
		folder = folderArg.getValue();
		width = widthArg.getValue();
		height = heightArg.getValue();
		title = titleArg.getValue();
		managerFolder = managerFolderArg.getValue();
	} catch(TCLAP::ArgException& e) {
		std::cerr << "ERROR: " << e.error() << " for arg " << e.argId() << std::endl;
	}
	WrathApp app;
	return app.run(audio, script, folder, width, height, title, managerFolder);
}