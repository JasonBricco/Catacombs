#pragma once

class SoundEffects
{
public:

	Sound swordSound;
	SoundBuffer swordBuffer;

	SoundEffects() {

		swordBuffer = SoundBuffer();

		if (!swordBuffer.loadFromFile("Assets/swordSlash.wav"))
		{
	
		}

		swordSound = Sound();
		swordSound.setBuffer(swordBuffer);

	}

	void playSwordSound() {
		swordSound.play();
	}


};


