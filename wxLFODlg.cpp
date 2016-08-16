#include "wxLFODlg.h"
#include "../StreamingAudioLib/Wavetable.h"
#include "wx/stdpaths.h"

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "wxLFODlg.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

IMPLEMENT_DYNAMIC_CLASS( wxLFODlg, wxPanel )

BEGIN_EVENT_TABLE( wxLFODlg, wxPanel )
	EVT_COMMAND_SCROLL( ID_LFO_FREQUENCY, wxLFODlg::OnFrequency )
END_EVENT_TABLE()

wxLFODlg::wxLFODlg( )
{
}

wxLFODlg::~wxLFODlg()
{
}

wxLFODlg::wxLFODlg( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, pos, size, style);
}

bool wxLFODlg::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    // Set member variables here
    _textColour.Set( 150, 150, 250 );
    _backgroundColour.Set( 0, 8, 40 );
	_slFrequency = NULL;
	_chLFOWaveform = NULL;
	_staticText1 = NULL;
	_staticText2 = NULL;
	_txtFrequency = NULL;
	_callback = NULL;

    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
    return true;
}

void wxLFODlg::CreateControls()
{    
    wxLFODlg* itemDialog1 = this;

    wxImage sliderBk;
    sliderBk.LoadFile( _("hsliderbk.bmp"), wxBITMAP_TYPE_BMP );
    wxImage sliderInd;
    sliderInd.LoadFile( _("hsliderind.bmp"), wxBITMAP_TYPE_BMP );

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxFlexGridSizer* itemBoxSizer3 = new wxFlexGridSizer(4, 3, 0, 0);
    itemBoxSizer2->Add(itemBoxSizer3, 0, 0, 0 );

    _staticText1 = new wxStaticText( itemDialog1, wxID_STATIC, _("LFO Freq (Hz):"), wxDefaultPosition, wxDefaultSize, 0 );
    _staticText1->SetForegroundColour(_textColour);
    itemBoxSizer3->Add(_staticText1, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	_slFrequency = new wxBitmapSlider( itemDialog1, ID_LFO_FREQUENCY, 0, 0, 200, wxDefaultPosition, wxSize(211,24) );
	_slFrequency->SetBitmaps(&sliderBk, &sliderInd);
	itemBoxSizer3->Add(_slFrequency, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	_txtFrequency = new wxStaticText( itemDialog1, ID_TXT_FREQUENCY, _("0.0"), wxDefaultPosition, wxSize(32, -1));
    _txtFrequency->SetForegroundColour(_textColour);
	itemBoxSizer3->Add(_txtFrequency, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _staticText2 = new wxStaticText( itemDialog1, wxID_STATIC, _("LFO Waveform:"), wxDefaultPosition, wxDefaultSize, 0 );
    _staticText2->SetForegroundColour(_textColour);
    itemBoxSizer3->Add(_staticText2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	wxArrayString choices;
	choices.Add(_("Sine"));
	choices.Add(_("Square"));
	choices.Add(_("Saw"));
	choices.Add(_("Triangle"));
	choices.Add(_("Sinc"));
	choices.Add(_("Pulse"));
	_chLFOWaveform = new wxKeylessChoice( itemDialog1, ID_LFO_WAVEFORM, wxDefaultPosition, wxSize(200,-1), choices);
	_chLFOWaveform->SetSelection(0);
	itemBoxSizer3->Add(_chLFOWaveform, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	itemBoxSizer3->AddSpacer(1);

}

bool wxLFODlg::SetForegroundColour(const wxColour &colour)
{
	_textColour = colour;
    _slFrequency->SetForegroundColour(_textColour);
    _chLFOWaveform->SetForegroundColour(_textColour);
	_staticText1->SetForegroundColour(_textColour);
	_staticText2->SetForegroundColour(_textColour);
	_txtFrequency->SetForegroundColour(_textColour);
	Refresh();
	return true;
}

bool wxLFODlg::SetBackgroundColour(const wxColour &colour)
{
	_backgroundColour = colour;
	_slFrequency->SetBackgroundColour(_backgroundColour);
	_chLFOWaveform->SetBackgroundColour(_backgroundColour);
	wxPanel::SetBackgroundColour(colour);
	Refresh();
	return true;
}

void wxLFODlg::SetLFOCallback(LFOCallback* callback)
{
	_callback = callback;
}

LFOParameters wxLFODlg::GetLFOParameters()
{
	LFOParameters parameters;
	memset(&parameters, 0, sizeof(LFOParameters));
	parameters.enabled = true;
	parameters.lfoFrequency = ((float)_slFrequency->GetValue() / 10.0f);
	parameters.lfoWaveform = _chLFOWaveform->GetSelection();
	return parameters;
}

void wxLFODlg::SetLFOParameters(LFOParameters parameters)
{
	_slFrequency->SetValue(parameters.lfoFrequency * 10.0f);
	_chLFOWaveform->SetSelection(parameters.lfoWaveform);
	_txtFrequency->SetLabel( wxString::Format(_("%2.1f"), ((float)_slFrequency->GetValue() / 10.0f )));
}

void wxLFODlg::OnFrequency( wxScrollEvent& event )
{
	if( _callback != NULL )
	{
		_callback->OnLfoChanged((GetLFOParameters()));
	}
	_txtFrequency->SetLabel( wxString::Format(_("%2.1f"), ((float)_slFrequency->GetValue() / 10.0f )));
	event.Skip();
}