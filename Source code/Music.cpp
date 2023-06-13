#include "Music.h"
#include <thread>


void Music::playMusic(const char* soundUrl, bool isRepeat) {
	stopmusic = false;
	sf::SoundBuffer buffer;
	buffer.loadFromFile(soundUrl);

	sound.setBuffer(buffer);
	sound.setLoop(isRepeat);
	sound.play();
	while (!stopmusic && sound.getStatus() == sf::Sound::Playing)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

}

void Music::stopMusic() {
	sound.stop();
	stopmusic = true;
}
