#include <Application.h>


bool Application::running = true;

WindowWrapper Application::windowWrapper = WindowWrapper(1000, 1000); // create the window
Menu* Application::currentMenu = &mainMenu;


//
// Menus
//
Menu Application::mainMenu = Menu(1, Application::windowWrapper.getWindowWidth()/2, Application::windowWrapper.getWindowHeight()/2, {
	Button(300, 60, "start", [](){
			log("start pressed");
	}),

	Button(300, 60, "options", [](){
			Application::changeMenu(&(Application::optionsMenu));
	}),

	Button(300, 60, "exit", [](){
			Application::stop();
	})
});


Menu Application::optionsMenu = Menu(1, Application::windowWrapper.getWindowWidth()/2, Application::windowWrapper.getWindowHeight()/2, {
	Button(300, 60, "option 1", [](){
			log("option 1");
	}),

	Button(300, 60, "option 2", [](){
			log("option 2");
	}),

	Button(300, 60, "option 3", [](){
			log("option 3");
	}),

	Button(300, 60, "<", [](){
			Application::changeMenu(&(Application::mainMenu));
	})
});



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
	window->setFramerateLimit(120);
	window->setVerticalSyncEnabled(true);

	sf::View view;


	// sounds
	aud::Sound snare("res/snare.wav", 20);
	aud::Sound kick("res/kick.wav", 20);
	aud::Sound hat("res/hat.wav", 20);
	aud::Sound music_MainMenu("res/music_MainMenu.wav", 20, true);
	music_MainMenu.play();

	//images
	img::Image bg("res/forest2.jpg");
	bg.setXY(-150, winh - bg.getHeight() + 45);
	img::Image title("res/title.png");
	title.setXY(winw/2 - title.getWidth()/2, winh/2 - title.getHeight()/2 - 150);
	

	// menu circle
	int rad = 300;
	sf::CircleShape c(rad, 100);
	c.setOrigin(rad, rad); // set transformation origin point to the circle's center
	c.setFillColor(sf::Color(253, 218, 73, 255));
	c.setPosition(winw/2, winh/2);

	double rotateCountBg = 0;
	double xWaverCountBg = 0;
	double yWaverCountBg = 0;


	sf::Clock clock;
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

				if (event.key.code == sf::Keyboard::Escape){
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


			float dt = clock.restart().asSeconds();

			window->clear(sf::Color(228,240,238,255)); // clear and set bg color

			// waver camera
			view.rotate(cos(rotateCountBg) / 1.1 * dt);
			view.move(10 * cos(xWaverCountBg) * dt, 10 * cos(yWaverCountBg) * dt);

			// items affected by waver
			window->setView(view);
			window->draw(bg);

			// reset to standard view
			window->setView(window->getDefaultView());

			window->draw(c);
			window->draw(title);
			window->draw(*(Application::currentMenu));
			window->display();

			rotateCountBg += 0.005;
			xWaverCountBg += 0.004;
			yWaverCountBg += 0.007;
		}
	}
}


//
// Start the program
//
void Application::init(){
	Application::eventLoop();
}

