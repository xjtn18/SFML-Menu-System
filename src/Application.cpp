#include <Application.h>

bool Application::running = true;

WindowWrapper Application::windowWrapper = WindowWrapper(1000, 1000); // create the window
Menu* Application::currentMenu = &mainMenu;


//
// Menus
//
Menu Application::mainMenu = Menu(20, Application::windowWrapper.getWindowWidth()/2, Application::windowWrapper.getWindowHeight()/2, {
	Button(300, 50, "start", [](){
			log("start pressed");
	}),

	Button(300, 50, "options", [](){
			Application::changeMenu(&(Application::optionsMenu));
	}),

	Button(300, 50, "exit", [](){
			Application::stop();
	})
});


Menu Application::optionsMenu = Menu(20, Application::windowWrapper.getWindowWidth()/2, Application::windowWrapper.getWindowHeight()/2, {
	Button(300, 50, "option 1", [](){
			log("option 1");
	}),

	Button(300, 50, "option 2", [](){
			log("option 2");
	}),

	Button(300, 50, "option 3", [](){
			log("option 3");
	}),

	Button(300, 50, "<", [](){
			Application::changeMenu(&(Application::mainMenu));
	})
});





bool stopRunning;

void circleQuickExpand(void* _c){
	//
	// param: CircleShape
	//
	stopRunning = false;
	sf::CircleShape* c = static_cast<sf::CircleShape*>(_c);
	float newScale = 1.0;
	
	//grow
	for (int i = 1; i < 30 && stopRunning == false; ++i){
		newScale = newScale + .001;
		c->setScale(sf::Vector2f(newScale, newScale));
		sf::sleep(sf::milliseconds(1));
	}

	//shrink
	for (int i = 1; i < 30 && stopRunning == false; ++i){
		newScale = newScale - .001;
		c->setScale(sf::Vector2f(newScale, newScale));
		sf::sleep(sf::milliseconds(1));
	}
	c->setScale(sf::Vector2f(1, 1)); // reset scale if stopRunning turned true before animation ended
}




//
// Change what menu is displayed
// 
void Application::changeMenu(Menu* newMenu){
	Application::currentMenu = newMenu;
}


//
// Stop the program
// 
void Application::stop(){
	sf::sleep(sf::milliseconds(200));
	Application::windowWrapper.getWindow()->close();
}



//
// Main program loop
// 
void Application::eventLoop(){

	sf::RenderWindow* window = Application::windowWrapper.getWindow();
	int winw = Application::windowWrapper.getWindowWidth();
	int winh = Application::windowWrapper.getWindowHeight();
	//sf::Vector2<unsigned int> winsize = window->getSize();

	// sounds
	aud::Sound snare("res/snare.wav");
	aud::Sound kick("res/kick.wav");
	aud::Sound hat("res/hat.wav");

	//images
	img::Image bg("res/forest.jpg");
	bg.setXY(0, winh - bg.getHeight());

	// menu circle
	std::map<int, sf::Color> cmap {{0, sf::Color::Magenta}, {1, sf::Color::Cyan}, {2, sf::Color::Yellow}};
	int rad = 300;
	sf::CircleShape c = sf::CircleShape(rad, 100);
	c.setOrigin(rad, rad); // set transformation origin point to the circle's center
	c.setFillColor(cmap[0]);
	c.setPosition(winw/2, winh/2);


	Application::mainMenu.setButtonColor(sf::Color(194, 221, 95, 255)); // light green
	Application::optionsMenu.setButtonColor(sf::Color(194, 221, 95, 255)); // light green


	// run the program as long as the window is open
	while (window->isOpen()) {
		// check all the windows events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window->pollEvent(event)) {
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed){
				Application::stop();

			// keyboard input
			} else if (event.type == sf::Event::KeyPressed){

				if (event.key.code == sf::Keyboard::K){
					kick.play();
					c.setFillColor(cmap[0]);
					(new sf::Thread(&circleQuickExpand, &c))->launch();

				} else if (event.key.code == sf::Keyboard::S){
					snare.play();
					c.setFillColor(cmap[1]);
					(new sf::Thread(&circleQuickExpand, &c))->launch();

				} else if (event.key.code == sf::Keyboard::H){
					hat.play();
					c.setFillColor(cmap[2]);

				} else if (event.key.code == sf::Keyboard::Escape){
					Application::stop();
				}
				
			// mouse input
			} else if (event.type == sf::Event::MouseButtonPressed){

				if (event.mouseButton.button == sf::Mouse::Button::Left){
					Application::currentMenu->checkPress(event.mouseButton.x, event.mouseButton.y);
				}
			}

			if (window->hasFocus()){
				sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
				Application::currentMenu->checkHover(mousePos.x, mousePos.y);
			}

			window->clear(sf::Color(228,240,238,255)); // clear and set bg color
			window->draw(bg);
			window->draw(c);
			window->draw(*(Application::currentMenu));
			window->display();
		}
	}
}


//
// Start the program
//
void Application::init(){
	Application::eventLoop();
}

