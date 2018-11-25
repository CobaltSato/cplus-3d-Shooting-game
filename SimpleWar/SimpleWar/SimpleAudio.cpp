//***************************************************************************************
// SimpleAudio.cpp by Cobalt Sato.
//***************************************************************************************
#include "SimpleAudio.h"
SimpleAudio::SimpleAudio() {
	// Initialize Audio
	// =======================================================================================
		// Create DirectXTK for Audio objects
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | AudioEngine_Debug;
#endif

	mAudEngine = std::make_unique<AudioEngine>(eflags);

	mAudioEvent = 0;
	mAudioTimerAcc = 10.f;
	mRetryAudio = false;

	//m_waveBank = std::make_unique<WaveBank>(mAudEngine.get(), L"adpcmdroid.xwb");
	mSounds = std::make_unique<WaveBank>(mAudEngine.get(), L"sounds.xwb");

	//m_explode = std::make_unique<SoundEffect>(mAudEngine.get(), L"Explo1.wav");
	//m_ambient = std::make_unique<SoundEffect>(mAudEngine.get(), L"fuyugomori.wav");

	mExplode = mSounds->CreateInstance("Explo1");
	mNightLoop = mSounds->CreateInstance("rao");
	//mNightLoop = mSounds->CreateInstance(0);
	mNightLoop->Play(true);

	std::random_device rd;
	mRandom = std::make_unique<std::mt19937>(rd());
}

SimpleAudio::~SimpleAudio() {
	if (mAudEngine)
	{
		mAudEngine->Suspend();
	}
	mNightLoop.reset();
}

void SimpleAudio::explode() {
	std::uniform_int_distribution<unsigned int> dist2(0, 3);
	mSounds->Play(dist2(*mRandom));
	std::uniform_real_distribution<float> dist(1.f, 10.f);
}

void SimpleAudio::retry() {
	if (mRetryAudio)
	{
		mRetryAudio = false;
		if (mAudEngine->Reset())
		{
			if (mNightLoop)
				mNightLoop->Play(true);
		}
	}
}
