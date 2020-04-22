#pragma once

class SoundEffects
{
public:

	sf::Sound sound;

	SoundEffects() {

		sf::SoundBuffer buffer;
		if (!buffer.loadFromFile("Assets/bark.wav"))
		{

		}
		sound = sf::Sound::Sound();
		sound.setBuffer(buffer);
	}

	void playSound() {
		sound.play();
	}


};


