#pragma once

#include "RtAudio.h"

class AudioSettingsInterface
{
public:
	virtual void SelectAudioInputDevice(RtAudio::StreamParameters* device) = 0;
	virtual void SelectAudioOutputDevice(RtAudio::StreamParameters* device) = 0;
};
