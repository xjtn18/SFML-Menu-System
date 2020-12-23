#pragma once
#include <SFML/Audio.hpp>


namespace aud {
	
	class Sound {

		sf::SoundBuffer buf;
		sf::Sound sound;

	public:
		Sound(const char* filename){
			buf = sf::SoundBuffer();
			buf.loadFromFile(filename);
			sound = sf::Sound(buf);
		}

		void play(){
			sound.play();
		}

	};
};

