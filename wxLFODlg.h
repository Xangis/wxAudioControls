#pragma once

/*
* Edit dialog for an ADSR envelope.
*/
#include "wx/wx.h"
#include "wxSwitch.h"
#include "LfoParameters.h"
#include "LFOCallback.h"
#include "wxBitmapSlider.h"
#include "wxKeylessChoice.h"

#define ID_LFOSETTINGS_DLG 7000
#define SYMBOL_LFODLG_STYLE wxNO_BORDER|wxWANTS_CHARS
#define SYMBOL_LFODLG_IDNAME ID_LFOSETTINGS_DLG
#define SYMBOL_LFODLG_SIZE wxSize(400, 440)
#define SYMBOL_LFODLG_POSITION wxDefaultPosition
#define ID_LFO_FREQUENCY 7004
#define ID_LFO_WAVEFORM 7005
#define ID_TXT_FREQUENCY 7006

class wxLFODlg : public wxPanel
{
    DECLARE_DYNAMIC_CLASS( wxLFODLG )
    DECLARE_EVENT_TABLE()
public:
    wxLFODlg();
    ~wxLFODlg();
    wxLFODlg( wxWindow* parent, wxWindowID id = SYMBOL_LFODLG_IDNAME, const wxPoint& pos = SYMBOL_LFODLG_POSITION, const wxSize& size = SYMBOL_LFODLG_SIZE, long style = SYMBOL_LFODLG_STYLE );
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_LFODLG_IDNAME, const wxPoint& pos = SYMBOL_LFODLG_POSITION, const wxSize& size = SYMBOL_LFODLG_SIZE, long style = SYMBOL_LFODLG_STYLE );
    void CreateControls();
	void OnFrequency( wxScrollEvent& event );
	bool SetForegroundColour(const wxColour &colour);
	bool SetBackgroundColour(const wxColour &colour);
	LFOParameters GetLFOParameters();
	void SetLFOParameters(LFOParameters params);
	void SetLFOCallback(LFOCallback* callback);
private:
	LFOCallback* _callback;
	wxBitmapSlider* _slFrequency;
	wxKeylessChoice* _chLFOWaveform;
    wxColour _backgroundColour;
    wxColour _textColour;
	wxStaticText* _staticText1;
	wxStaticText* _staticText2;
	wxStaticText* _txtFrequency;
};
