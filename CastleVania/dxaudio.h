#pragma once
#include "dsutil.h"

extern CSoundManager *sound;

class dxaudio
{
public:
	dxaudio();
	~dxaudio();

	int Init_DirectSound(HWND hwnd);
	CSound *LoadSound(LPTSTR fileName);
	void PlaySound(CSound* sound);
	void LoopSound(CSound* sound);
	void StopSound(CSound* sound);
};

