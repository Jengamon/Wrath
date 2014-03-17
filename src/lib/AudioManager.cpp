#include "AudioManager.h"

PLUMA_PROVIDER_SOURCE(AudioManager, 1, 1);

void AudioManager::setupListener(AudioListener* listen)
{
	listen->setupAudio(this);
}