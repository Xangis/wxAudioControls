#pragma once

/*
* Edit dialog for an ADSR envelope.
*/
#include "wx/wx.h"
#include "wxSwitch.h"
#include "AdsrParameters.h"
#include "ADSRCallback.h"
#include "wxBitmapSlider.h"

#define ID_ADSR_DLG 7000
#define SYMBOL_ADSRDLG_STYLE wxNO_BORDER|wxWANTS_CHARS
#define SYMBOL_ADSRDLG_IDNAME ID_ADSR_DLG
#define SYMBOL_ADSRDLG_SIZE wxSize(400, 440)
#define SYMBOL_ADSRDLG_POSITION wxDefaultPosition
#define ID_ADSR_ATTACK 7004
#define ID_ADSR_DECAY 7005
#define ID_ADSR_SUSTAIN 7006
#define ID_ADSR_RELEASE 7007
#define ID_TXT_ATTACK 7008
#define ID_TXT_DECAY 7009
#define ID_TXT_SUSTAIN 7010
#define ID_TXT_RELEASE 7011

//class wxADSRDlg : public wxPanel
class wxADSRDlg : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( wxADSRDlg )
    DECLARE_EVENT_TABLE()
public:
    wxADSRDlg();
    ~wxADSRDlg();
    wxADSRDlg( wxWindow* parent, wxWindowID id = SYMBOL_ADSRDLG_IDNAME, const wxPoint& pos = SYMBOL_ADSRDLG_POSITION, const wxSize& size = SYMBOL_ADSRDLG_SIZE, long style = SYMBOL_ADSRDLG_STYLE );
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ADSRDLG_IDNAME, const wxPoint& pos = SYMBOL_ADSRDLG_POSITION, const wxSize& size = SYMBOL_ADSRDLG_SIZE, long style = SYMBOL_ADSRDLG_STYLE );
    void CreateControls();
	void OnAttack( wxScrollEvent& event );
	void OnDecay( wxScrollEvent& event );
	void OnSustain( wxScrollEvent& event );
	void OnRelease( wxScrollEvent& event );
	bool SetForegroundColour(const wxColour &colour);
	bool SetBackgroundColour(const wxColour &colour);
	AdsrParameters GetAdsrParameters();
	void SetAdsrParameters(AdsrParameters params);
	void SetADSRCallback(ADSRCallback* callback);
private:
	ADSRCallback* _callback;
	wxBitmapSlider* _slAttack;
	wxBitmapSlider* _slDecay;
	wxBitmapSlider* _slSustain;
	wxBitmapSlider* _slRelease;
    wxColour _backgroundColour;
    wxColour _textColour;
	wxStaticText* _staticText1;
	wxStaticText* _staticText2;
	wxStaticText* _staticText3;
	wxStaticText* _staticText4;
	wxStaticText* _txtAttack;
	wxStaticText* _txtDecay;
	wxStaticText* _txtSustain;
	wxStaticText* _txtRelease;
};
