#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <Debug.h>
#include <Sound.h>
#include <cmath>


class Button : public sf::Drawable {

	int x,y,w,h;
	sf::Rect<int> zone; // the interactable zone of the button
	sf::RectangleShape box; // the visual of the button
	sf::Color idleColor = sf::Color(194, 221, 95, 255);
	sf::Color hoverColor = sf::Color(179, 215, 47, 255);
	sf::Text bText;
	std::function<void(void)> onPress;
	bool isHovered = false;

public:
	static aud::Sound pressSound;
	static aud::Sound hoverSound;
	static sf::Font font;

	Button(int _w, int _h, const std::string _text, std::function<void(void)> _onPress) : w(_w), h(_h), onPress(_onPress){
		box = sf::RectangleShape(sf::Vector2f(w,h));
		box.setFillColor(sf::Color::Black);
		box.setOutlineThickness(1);
		box.setOutlineColor(sf::Color::Black);

		font.loadFromFile("res/sansation.ttf");
		// center rectangles pivot
		box.setOrigin(w/2, h/2);

		bText = sf::Text(_text, Button::font, (unsigned int) (h/1.5)); // font size a function of button height
		bText.setFillColor(sf::Color::Black); // set font color
		sf::FloatRect textBounds = bText.getLocalBounds();
		bText.setOrigin((int)(textBounds.width/2), (int)(h/2.1));

	}


	void setXY(int _x, int _y) {
		x = _x;
		y = _y;
		zone = sf::Rect<int>(x-w/2,y-h/2,w,h);
		box.setPosition(x, y);
		bText.setPosition(x,y);
	};

	int getWidth() const {
		return w;
	};

	int getHeight() const {
		return h;
	};


	void setColor(sf::Color c){
		box.setFillColor(c);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(box); // draw the button box
		target.draw(bText); // draw the button text
	}

	void checkPress(int mouseX, int mouseY){
		if (zone.contains(mouseX, mouseY)){ // this button was pressed
			Button::pressSound.play();
			this->onPress();
		}
	}

	void checkHover(int mouseX, int mouseY){
		if (isHovered == false && zone.contains(mouseX, mouseY)){ // this button was pressed
			isHovered = true;
			Button::hoverSound.play();
			box.setFillColor(hoverColor);
			(new sf::Thread(&grow, this))->launch();

		} else if (isHovered == true && !zone.contains(mouseX, mouseY)){
			isHovered = false;
			box.setFillColor(idleColor);
			(new sf::Thread(&shrink, this))->launch();
		}
	}

	static void grow(void* _button){
		Button* button = static_cast<Button*>(_button);

		for (int i = 0; i < 10; ++i){
			button->box.setSize(button->box.getSize() + sf::Vector2f(i,0));
			button->box.setPosition(button->box.getPosition() - sf::Vector2f(i/2,0));
			sf::sleep(sf::milliseconds(3));
		}
	}

	static void shrink(void* _button){
		Button* button = static_cast<Button*>(_button);

		for (int i = 0; i < 10; ++i){
			button->box.setSize(button->box.getSize() - sf::Vector2f(i,0));
			button->box.setPosition(button->box.getPosition() + sf::Vector2f(i/2,0));
			sf::sleep(sf::milliseconds(3));
		}
	}

};


