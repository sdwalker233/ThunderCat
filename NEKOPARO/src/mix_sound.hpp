#ifndef mix_sound_hpp
#define mix_sound_hpp

#include "utility.h"

class BaseMixSound
{
private:
	static int MixNUM;
protected:
	BaseMixSound();
public:
	virtual ~BaseMixSound();
};

class EffectSound: public BaseMixSound
{
private:
	Mix_Chunk* sound;
public:
	EffectSound(const std::string& sound_fileName);
	~EffectSound();
	void play() const;
};

class MusicSound: public BaseMixSound
{
private:
	Mix_Music* music;
public:
	MusicSound(const std::string& music_fileName);
	~MusicSound();
	void play() const;
	void stop() const;
};

#endif /* Mix_Sound_hpp */
