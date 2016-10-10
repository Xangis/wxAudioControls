#ifndef _MIDISETTINGSINTERFACE_H_
#define _MIDISETTINGSINTERFACE_H_

#include "RtMidi.h"

class MidiSettingsInterface
{
public:
	virtual void SelectMidiInputDevice(int number) = 0;
	virtual void SelectMidiOutputDevice(int number) = 0;
	virtual void SelectMidiInputChannel(int number) = 0;
	virtual void SelectMidiOutputChannel(int number) = 0;
	virtual void EnableMidiOutput(bool enabled) = 0;
    RtMidiIn* _midiInDevice;
    RtMidiOut* _midiOutDevice;
};

#endif
