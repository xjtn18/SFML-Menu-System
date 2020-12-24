#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Debug.h>
#include <Sound.h>
#include <Button.h>
#include <Menu.h>



void centerCircle(sf::CircleShape& s, sf::Window* win){
	sf::Vector2<unsigned int> winsize = win->getSize();
	float rad = s.getRadius();
	float centerX = winsize.x/2;
	float centerY = winsize.y/2;
	s.setPosition(centerX, centerY);
}

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



int main(){
	// main window
	int winw = 1000, winh = 1000;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(winw, winh), "GetCrunked", sf::Style::Default, settings);

	// sounds
	aud::Sound snare("res/snare.wav");
	aud::Sound kick("res/kick.wav");
	aud::Sound hat("res/hat.wav");

	// menu circle
	std::map<int, sf::Color> cmap {{0, sf::Color::Magenta}, {1, sf::Color::Cyan}, {2, sf::Color::Yellow}};
	int rad = 300;
	sf::CircleShape c = sf::CircleShape(rad, 100);
	centerCircle(c, &window);
	c.setOrigin(rad, rad); // set transformation origin point to the circle's center
	c.setFillColor(cmap[0]);

	Menu menu(20, winw/2, winh/2, {
		Button(300, 50, "start"),
		Button(300, 50, "options"),
		Button(300, 50, "exit")
	});
	menu.setButtonColor(sf::Color(179, 215, 47, 255));


	
	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed){
				window.close();

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
					window.close();
				}
				
			// mouse input
			} else if (event.type == sf::Event::MouseButtonPressed){

				if (event.mouseButton.button == sf::Mouse::Button::Left){
					menu.checkPress(event.mouseButton.x, event.mouseButton.y);
				}
			}

			window.clear(sf::Color(30,30,30,255)); // clear and set bg color
			window.draw(c);
			window.draw(menu);
			window.display();
		}
	}

	return 0;
}

