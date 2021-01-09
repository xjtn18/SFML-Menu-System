#pragma once
#include <SFML/Audio.hpp>


namespace aud {
	
	class Sound {

		sf::SoundBuffer buf;
		sf::Sound sound;

	public:
		Sound(const char* filename, float vol = 100.0f, bool loop = false){
			buf = sf::SoundBuffer();
			buf.loadFromFile(filename);
			sound = sf::Sound(buf);
			sound.setVolume(vol);
			sound.setLoop(loop);
		}

		void play(){
			sound.play();
		}

	};
};

