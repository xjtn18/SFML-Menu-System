#include <Button.h>


sf::Font Button::font;

aud::Sound Button::pressSound = aud::Sound("res/click.wav");
aud::Sound Button::hoverSound = aud::Sound("res/hover.wav");

int Button::hoverScaleAmount = 30;
int Button::hoverScaleSpeed = 1;
