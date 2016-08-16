#pragma once

#include <wx/wx.h>
#include "wxWavePanel.h"

/**
* Simplest possible use of the wxWavePanel -- showing a single dialog with a single panel to visualize data.  Meant to be used
  for debugging audio applications, but it may have other uses.
*/
class wxWaveVisualizer : public wxDialog
{
public:
	wxWaveVisualizer( wxWindow* parent, WaveFile* waveFile );
	//wxWaveVisualizer( wxWindow* parent, void* data, int length, int bytesPerSample, int numChannels  );
	~wxWaveVisualizer();
    void CreateControls();
private:
	wxWaveVisualizer();
	wxWavePanel* _panel;
};