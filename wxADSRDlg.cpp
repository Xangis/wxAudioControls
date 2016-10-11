#include "wxADSRDlg.h"
#include "wx/stdpaths.h"

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "wxADSRDlg.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "sliderbk.xpm"
#include "sliderind.xpm"

IMPLEMENT_DYNAMIC_CLASS( wxADSRDlg, wxDialog )

BEGIN_EVENT_TABLE( wxADSRDlg, wxDialog )
	EVT_COMMAND_SCROLL( ID_ADSR_ATTACK, wxADSRDlg::OnAttack )
	EVT_COMMAND_SCROLL( ID_ADSR_DECAY, wxADSRDlg::OnDecay )
	EVT_COMMAND_SCROLL( ID_ADSR_SUSTAIN, wxADSRDlg::OnSustain )
	EVT_COMMAND_SCROLL( ID_ADSR_RELEASE, wxADSRDlg::OnRelease )
END_EVENT_TABLE()

wxADSRDlg::wxADSRDlg( )
{
}

wxADSRDlg::~wxADSRDlg()
{
}

wxADSRDlg::wxADSRDlg( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, pos, size, style);
}

bool wxADSRDlg::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    // Set member variables here
    _textColour.Set( 150, 150, 250 );
    _backgroundColour.Set( 0, 8, 40 );
	_slAttack = NULL;
	_slDecay = NULL;
    _slSustain = NULL;
    _slRelease = NULL;
	_staticText1 = NULL;
	_staticText2 = NULL;
	_staticText3 = NULL;
	_staticText4 = NULL;
	_txtAttack = NULL;
	_txtDecay = NULL;
	_txtSustain = NULL;
	_txtRelease = NULL;
	_callback = NULL;

    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    //wxPanel::Create( parent, id, pos, size, style );
    wxDialog::Create( parent, id, _("ADSR Settings"), pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
    return true;
}

void wxADSRDlg::CreateControls()
{    
    wxADSRDlg* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxFlexGridSizer* itemBoxSizer3 = new wxFlexGridSizer(4, 3, 0, 0);
    itemBoxSizer2->Add(itemBoxSizer3, 0, 0, 0 );

    _staticText1 = new wxStaticText( itemDialog1, wxID_STATIC, _("Attack (msec):"), wxDefaultPosition, wxDefaultSize, 0 );
    _staticText1->SetForegroundColour(_textColour);
    itemBoxSizer3->Add(_staticText1, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	_slAttack = new wxBitmapSlider( itemDialog1, ID_ADSR_ATTACK, 0, 0, 1000, wxDefaultPosition, wxSize(211,24) );
	_slAttack->SetXpmBitmaps(sliderbk_xpm, sliderind_xpm);
	itemBoxSizer3->Add(_slAttack, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _txtAttack = new wxStaticText( itemDialog1, wxID_STATIC, _("0"), wxDefaultPosition, wxSize(32,-1), 0 );
    _txtAttack->SetForegroundColour(_textColour);
    itemBoxSizer3->Add(_txtAttack, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _staticText2 = new wxStaticText( itemDialog1, wxID_STATIC, _("Decay (msec):"), wxDefaultPosition, wxDefaultSize, 0 );
    _staticText2->SetForegroundColour(_textColour);
    itemBoxSizer3->Add(_staticText2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	_slDecay = new wxBitmapSlider( itemDialog1, ID_ADSR_DECAY, 0, 0, 1000, wxDefaultPosition, wxSize(211,24));
	_slDecay->SetXpmBitmaps(sliderbk_xpm, sliderind_xpm);
	itemBoxSizer3->Add(_slDecay, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _txtDecay = new wxStaticText( itemDialog1, wxID_STATIC, _("0"), wxDefaultPosition, wxSize(32,-1), 0 );
    _txtDecay->SetForegroundColour(_textColour);
    itemBoxSizer3->Add(_txtDecay, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	_staticText3 = new wxStaticText( itemDialog1, wxID_STATIC, _("Sustain (percent):"), wxDefaultPosition, wxDefaultSize, 0 );
    _staticText3->SetForegroundColour(_textColour);
    itemBoxSizer3->Add(_staticText3, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	_slSustain = new wxBitmapSlider( itemDialog1, ID_ADSR_SUSTAIN, 0, 0, 100, wxDefaultPosition, wxSize(211,24));
	_slSustain->SetXpmBitmaps(sliderbk_xpm, sliderind_xpm);
	itemBoxSizer3->Add(_slSustain, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _txtSustain = new wxStaticText( itemDialog1, wxID_STATIC, _("0"), wxDefaultPosition, wxSize(32,-1), 0 );
    _txtSustain->SetForegroundColour(_textColour);
    itemBoxSizer3->Add(_txtSustain, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	_staticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("Release (msec):"), wxDefaultPosition, wxDefaultSize, 0 );
    _staticText4->SetForegroundColour(_textColour);
    itemBoxSizer3->Add(_staticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	_slRelease = new wxBitmapSlider( itemDialog1, ID_ADSR_RELEASE, 0, 0, 500, wxDefaultPosition, wxSize(211,24));
	_slRelease->SetXpmBitmaps(sliderbk_xpm , sliderind_xpm);
	itemBoxSizer3->Add(_slRelease, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _txtRelease = new wxStaticText( itemDialog1, wxID_STATIC, _("0"), wxDefaultPosition, wxSize(32,-1), 0 );
    _txtRelease->SetForegroundColour(_textColour);
    itemBoxSizer3->Add(_txtRelease, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);
}

bool wxADSRDlg::SetForegroundColour(const wxColour &colour)
{
	_textColour = colour;
    _slAttack->SetForegroundColour(_textColour);
    _slDecay->SetForegroundColour(_textColour);
	_slSustain->SetForegroundColour(_textColour);
	_slRelease->SetForegroundColour(_textColour);
	_staticText1->SetForegroundColour(_textColour);
	_staticText2->SetForegroundColour(_textColour);
	_staticText3->SetForegroundColour(_textColour);
	_staticText4->SetForegroundColour(_textColour);
	_txtAttack->SetForegroundColour(_textColour);
	_txtDecay->SetForegroundColour(_textColour);
	_txtSustain->SetForegroundColour(_textColour);
	_txtRelease->SetForegroundColour(_textColour);
	Refresh();
	return true;
}

bool wxADSRDlg::SetBackgroundColour(const wxColour &colour)
{
	_backgroundColour = colour;
	_slAttack->SetBackgroundColour(_backgroundColour);
	_slDecay->SetBackgroundColour(_backgroundColour);
	_slSustain->SetBackgroundColour(_backgroundColour);
	_slRelease->SetBackgroundColour(_backgroundColour);
	//wxPanel::SetBackgroundColour(colour);
	wxDialog::SetBackgroundColour(colour);
	Refresh();
	return true;
}

AdsrParameters wxADSRDlg::GetAdsrParameters()
{
	AdsrParameters parameters;
	memset(&parameters, 0, sizeof(AdsrParameters));
	parameters.attackTimeMsec = _slAttack->GetValue();
	parameters.decayTimeMsec = _slDecay->GetValue();
	parameters.sustainLevelPercent = _slSustain->GetValue();
	parameters.releaseTimeMsec = _slRelease->GetValue();
	parameters.enabled = true;
	return parameters;
}

void wxADSRDlg::SetADSRCallback(ADSRCallback* callback)
{
	_callback = callback;
}

void wxADSRDlg::SetAdsrParameters(AdsrParameters parameters)
{
	_slAttack->SetValue(parameters.attackTimeMsec);
	_slDecay->SetValue(parameters.decayTimeMsec);
	_slRelease->SetValue(parameters.releaseTimeMsec);
	_slSustain->SetValue(parameters.sustainLevelPercent);
	_txtAttack->SetLabel(wxString::Format(_("%3.0f"), _slAttack->GetValue() ));
	_txtDecay->SetLabel(wxString::Format(_("%3.0f"), _slDecay->GetValue() ));
	_txtSustain->SetLabel(wxString::Format(_("%3.0f"), _slSustain->GetValue() ));
	_txtRelease->SetLabel(wxString::Format(_("%3.0f"), _slRelease->GetValue() ));
}

void wxADSRDlg::OnAttack( wxScrollEvent& event )
{
	if( _callback != NULL )
	{
		_callback->OnEnvelopeChanged((GetAdsrParameters()));
	}
	_txtAttack->SetLabel(wxString::Format(_("%3.0f"), _slAttack->GetValue() ));
	event.Skip();
}

void wxADSRDlg::OnDecay( wxScrollEvent& event )
{
	if( _callback != NULL )
	{
		_callback->OnEnvelopeChanged((GetAdsrParameters()));
	}
	_txtDecay->SetLabel(wxString::Format(_("%3.0f"), _slDecay->GetValue() ));
	event.Skip();
}

void wxADSRDlg::OnSustain( wxScrollEvent& event )
{
	if( _callback != NULL )
	{
		_callback->OnEnvelopeChanged((GetAdsrParameters()));
	}
	_txtSustain->SetLabel(wxString::Format(_("%3.0f"), _slSustain->GetValue() ));
	event.Skip();
}

void wxADSRDlg::OnRelease( wxScrollEvent& event )
{
	if( _callback != NULL )
	{
		_callback->OnEnvelopeChanged((GetAdsrParameters()));
	}
	_txtRelease->SetLabel(wxString::Format(_("%3.0f"), _slRelease->GetValue() ));
	event.Skip();
}
