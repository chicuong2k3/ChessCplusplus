#pragma once

#include <SFML/Audio.hpp>

class Music
{
	
public:
	sf::Sound sound;
	std::atomic<bool> stopmusic;
	void playMusic(const char* soundUrl, bool isRepeat = false);
	void stopMusic();
};
