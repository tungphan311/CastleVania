#include "dxaudio.h"



dxaudio::dxaudio()
{
}


dxaudio::~dxaudio()
{
}

int dxaudio::Init_DirectSound(HWND hwnd)
{
	HRESULT hr;

	// creat directsound manager object
	sound = new CSoundManager();

	// initialize direct sound
	hr = sound->Initialize(hwnd, DSSCL_PRIORITY);
	if (hr != DS_OK)
		return 0;

	return 1; // success
}

CSound * dxaudio::LoadSound(LPTSTR fileName)
{
	HRESULT hr;

	// create local reference to wave data
	CSound *wave;

	// attempt to load the wave file
	hr = sound->Create(&wave, fileName);

	if (hr != DS_OK)
		return NULL;

	return wave;
}

void dxaudio::PlaySound(CSound *sound)
{
	sound->Play();
}

void dxaudio::LoopSound(CSound * sound)
{
	sound->Play(0, DSBPLAY_LOOPING);
}

void dxaudio::StopSound(CSound * sound)
{
	sound->Stop();
}


