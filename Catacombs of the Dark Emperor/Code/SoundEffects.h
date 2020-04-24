#pragma once

class SoundEffects
{
public:

	Sound swordSound;
	SoundBuffer swordBuffer;

	Sound damageSound;
	SoundBuffer damageBuffer;

	Sound bowSound;
	SoundBuffer bowBuffer;

	Sound chestSound;
	SoundBuffer chestBuffer;

	Sound fireballSound;
	SoundBuffer fireballBuffer;

	Sound bossSound;
	SoundBuffer bossBuffer;

	SoundEffects() {

		//Initialize sound and sound buffer pairing for each sound effect

		swordBuffer = SoundBuffer();
		if (!swordBuffer.loadFromFile("Assets/swordSlash.wav"))
		{
	
		}
		swordSound = Sound();
		swordSound.setBuffer(swordBuffer);


		bowBuffer = SoundBuffer();
		if (!bowBuffer.loadFromFile("Assets/bowAttack.wav"))
		{

		}
		bowSound = Sound();
		bowSound.setBuffer(bowBuffer);

		chestBuffer = SoundBuffer();
		if (!chestBuffer.loadFromFile("Assets/chestOpen.wav"))
		{

		}
		chestSound = Sound();
		chestSound.setBuffer(chestBuffer);

		damageBuffer = SoundBuffer();
		if (!damageBuffer.loadFromFile("Assets/takeDamage.wav"))
		{

		}
		damageSound = Sound();
		damageSound.setBuffer(damageBuffer);

		fireballBuffer = SoundBuffer();
		if (!fireballBuffer.loadFromFile("Assets/fireball.wav"))
		{

		}
		fireballSound = Sound();
		fireballSound.setBuffer(fireballBuffer);

		bossBuffer = SoundBuffer();
		if (!bossBuffer.loadFromFile("Assets/bossLaugh.wav"))
		{

		}
		bossSound = Sound();
		bossSound.setBuffer(bossBuffer);
	}
	//Methods to play every sound effect

	void playSwordSound() 
	{
		swordSound.play();
	}

	void playBowSound()
	{
		bowSound.play();
	}

	void playChestSound()
	{
		chestSound.play();
	}

	void playDamageSound()
	{
		damageSound.play();
	}

	void playFireball()
	{
		fireballSound.play();
	}

	void playBossSound() 
	{
		bossSound.play();
	}

};


