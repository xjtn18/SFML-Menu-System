#pragma once
#include <SFML/Graphics.hpp>
#include <Debug.h>


class Button : public sf::Drawable {

	int x,y,w,h;
	sf::Rect<int> zone; // the interactable zone of the button
	sf::RectangleShape box; // the visual of the button

	static sf::Font font;
	sf::Text bText;

public:

	Button(int _w, int _h, const std::string _text) : w(_w), h(_h) {
		box = sf::RectangleShape(sf::Vector2f(w,h));
		box.setFillColor(sf::Color::Black);
		box.setOutlineThickness(1);
		box.setOutlineColor(sf::Color::Black);

		// center rectangles pivot
		box.setOrigin(w/2, h/2);

		font.loadFromFile("res/sansation.ttf");
		bText = sf::Text(_text, Button::font, (unsigned int) (h/1.5)); // font size a function of button height
		bText.setFillColor(sf::Color::Black); // set font color
		sf::FloatRect textBounds = bText.getLocalBounds();
		bText.setOrigin((int)(textBounds.width/2), (int)(h/2.1));

	}


	void setXY(int _x, int _y) {
		zone = sf::Rect<int>(_x-w/2,_y-h/2,w,h);
		box.setPosition(_x, _y);
		bText.setPosition(_x,_y);
	};

	int getWidth() const {
		return w;
	};

	int getHeight() const {
		return h;
	};

	void setWidth(int newWidth) {
		w = newWidth;
	};

	void setHeight(int newHeight) {
		h = newHeight;
	};

	void setColor(sf::Color c){
		box.setFillColor(c);
	}


	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(box, states); // draw the button box
		target.draw(bText, states); // draw the button text
	}

	void checkPress(int mouseX, int mouseY){
		if (zone.contains(mouseX, mouseY)){
			log(bText.getString().toAnsiString() + " pressed!");
		}
	}
};


