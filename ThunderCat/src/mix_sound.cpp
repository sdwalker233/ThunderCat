#include "mix_sound.hpp"

//*******************************
//class BaseMixSound

int BaseMixSound::MixNUM = 0;

BaseMixSound::BaseMixSound()
{
	if ( MixNUM == 0 ){
		if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
			std::cerr << "Mix_Open ERROR" << std::endl;
			exit(-1);
		}
	}
	MixNUM++;
}

BaseMixSound::~BaseMixSound()
{
	MixNUM--;
	if ( MixNUM == 0 ){
		Mix_CloseAudio();
	}
}

//*******************************



//*******************************
//class EffectSound

EffectSound::EffectSound(const std::string& sound_fileName)
{
	sound = Mix_LoadWAV(sound_fileName.c_str());
	if ( sound == 0 ){
		std::cerr << sound_fileName << " : load failed!" << std::endl;
	}
}

EffectSound::~EffectSound()
{
	Mix_FreeChunk(sound);
}

void EffectSound::play() const
{
	if( Mix_PlayChannel(-1, sound, 0) == -1 ){
		std::cerr << "Mix_PlayChannel() ERROR" << std::endl;
	}
}

//*******************************



//*******************************
//class MusicSound

MusicSound::MusicSound(const std::string& music_fileName)
{
	music = Mix_LoadMUS(music_fileName.c_str());
	if (  music == 0 ){
		std::cerr << music_fileName << " : load failed!" << std::endl;
	}
}

MusicSound::~MusicSound()
{
	Mix_FreeMusic(music);
}

void MusicSound::play() const
{
	if( Mix_PlayingMusic() == false ){
		if( Mix_PlayMusic( music, -1 ) == -1 ){
			std::cerr << "Mix_PlayMusic() ERROR" << std::endl;
		}
	} else {
		if( Mix_PausedMusic() == 1) {
			Mix_ResumeMusic();
		}
		else {
			Mix_PauseMusic();
		}
	}
}

void MusicSound::stop() const
{
	Mix_HaltMusic();
}

//***************************************
