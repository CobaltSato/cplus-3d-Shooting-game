//***************************************************************************************
// Simple.cpp by Cobalt Sato.
//  the class to keep easy access to audio engine.
//***************************************************************************************
#pragma once
#include "Audio.h"
#include <random>
using namespace DirectX;
class SimpleAudio {
public:
	SimpleAudio();
	~SimpleAudio();
	void explode();
	void retry();

private:
	SimpleAudio(const SimpleAudio& rhs) = delete;
	SimpleAudio& operator=(const SimpleAudio& rhs) = delete;
	std::unique_ptr<AudioEngine>                                   mAudEngine;
	std::unique_ptr<WaveBank>                                      mSounds;
	std::unique_ptr<SoundEffect>                                   mSoundEffect;
	std::unique_ptr<SoundEffectInstance>                           mNightLoop;
	std::unique_ptr<SoundEffectInstance>                           mExplode;
	uint32_t                                                                mAudioEvent;
	float                                                                   mAudioTimerAcc;
	bool                                                                    mRetryAudio;
	std::unique_ptr<std::mt19937> mRandom;
};