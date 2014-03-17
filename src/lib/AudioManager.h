#ifndef WRATH_AUDIOMANAGER_H
#define WRATH_AUDIOMANAGER_H

#include <Pluma/Pluma.hpp>
#include <string>

enum class Status
{
	PLAYING,
	PAUSED,
	STOPPED
};

struct AudioData
{
	void* data;
};

class AudioManager;

class AudioListener
{
public:
	virtual void setupAudio(AudioManager*) = 0;
	virtual ~AudioListener() {}
};

class AudioManager
{
public:
	virtual std::string getName() const = 0;
	virtual void init() = 0;
	virtual AudioData* createSound(std::string) = 0;
	virtual void playSound(AudioData*) = 0;
	virtual void pauseSound(AudioData*) = 0;
	virtual void stopSound(AudioData*) = 0;
	virtual Status getStatus(AudioData*) const = 0;
	virtual void setLoop(AudioData*, bool) = 0;
	virtual void setPitch(AudioData*, double) = 0;
	virtual void setVolume(AudioData*, double) = 0;
	virtual void setPosition(AudioData*, int) = 0;
	virtual bool getLoop(AudioData*) const = 0;
	virtual double getPitch(AudioData*) const = 0;
	virtual double getVolume(AudioData*) const = 0;
	virtual int getPosition(AudioData*) const = 0;
	virtual void destroySound(AudioData*) = 0;
	virtual void update() = 0;

	virtual AudioData* createSSound(std::string) = 0;
	virtual void playSSound(AudioData*) = 0;
	virtual void pauseSSound(AudioData*) = 0;
	virtual void stopSSound(AudioData*) = 0;
	virtual Status getSStatus(AudioData*) const = 0;
	virtual void setSLoop(AudioData*, bool) = 0;
	virtual void setSPitch(AudioData*, double) = 0;
	virtual void setSVolume(AudioData*, double) = 0;
	virtual void setSPosition(AudioData*, int) = 0;
	virtual bool getSLoop(AudioData*) const = 0;
	virtual double getSPitch(AudioData*) const = 0;
	virtual double getSVolume(AudioData*) const = 0;
	virtual int getSPosition(AudioData*) const = 0;
	virtual void destroySSound(AudioData*) = 0;

	void setupListener(AudioListener*);
};

PLUMA_PROVIDER_HEADER(AudioManager);

#endif // WRATH_AUDIOMANAGER_H