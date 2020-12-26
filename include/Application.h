#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <WindowWrapper.h>
#include <Debug.h>
#include <Sound.h>
#include <Button.h>
#include <Menu.h>

class Application {

public:
	// main window
	static WindowWrapper windowWrapper;
	static bool running;
	static Menu mainMenu, optionsMenu;
	static Menu* currentMenu;


	static void init();
	static void stop();
	static void eventLoop();
	static void changeMenu(Menu* newMenu);
};

