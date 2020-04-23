#pragma once

class SoundEffects
{
public:

	Sound sound;

	SoundEffects() {

		sf::SoundBuffer buffer;
		buffer.loadFromFile("Assets/bark.wav");

		sound = sf::Sound::Sound();
		sound.setBuffer(buffer);
		
		
		
	}

	void playSound() {
		sound.play();
	}


};


