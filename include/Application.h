#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <WindowWrapper.h>
#include <Debug.h>
#include <Sound.h>
#include <Button.h>
#include <Menu.h>
#include <Image.h>

class Application {

public:
	// main window
	static bool running;
	static WindowWrapper windowWrapper;
	static Menu mainMenu, optionsMenu;
	static Menu* currentMenu;


	static void init();
	static void stop();
	static void eventLoop();
	static void changeMenu(Menu* newMenu);
};

