#ifndef HEADER_UTIL_H
#define HEADER_UTIL_H

#include <SFML/Audio.hpp>
#include "Vec2.h"

namespace Utility
{

	inline bool isOnBoard(const Vec2<int>& position)
	{
		return position.getX() >= 0 && position.getX() < 8
			&& position.getY() >= 0 && position.getY() < 8;
	}

	inline void playSound(const char* soundUrl) {
		sf::SoundBuffer buffer;
		buffer.loadFromFile(soundUrl);
		sf::Sound sound;
		sound.setBuffer(buffer);
		sound.play();
		while (sound.getStatus() == sf::Sound::Playing)
		{
		}
	}

}

#endif