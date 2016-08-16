#include "wxWaveVisualizer.h"

wxWaveVisualizer::wxWaveVisualizer(wxWindow* parent, WaveFile *waveFile): wxDialog(parent, wxID_ANY, _(""), wxDefaultPosition)
{
	_panel = new wxWavePanel(this, 12345, wxDefaultPosition, wxSize(630, 460), 0);
	_panel->SetWaveFile(waveFile);
	CreateControls();
}
//
//wxWaveVisualizer::wxWaveVisualizer(wxWindow* parent, void* data, int length, int bytesPerSample, int numChannels): wxDialog(parent, wxID_ANY, _(""), wxDefaultPosition)
//{
//	_panel = new wxWavePanel(this, 12345, wxDefaultPosition, wxSize(630, 460), 0);
//	_panel->SetData(data, length, bytesPerSample, numChannels);
//	CreateControls();
//}

void wxWaveVisualizer::CreateControls()
{
    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer);
	boxSizer->Add(_panel, 0, 0, 5);
	Fit();
}

wxWaveVisualizer::~wxWaveVisualizer()
{
	if( _panel != NULL )
	{
		delete _panel;
	}
}