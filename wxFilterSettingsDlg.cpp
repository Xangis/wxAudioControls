#include "wxFilterSettingsDlg.h"
#include "wx/stdpaths.h"


// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

// Image resources
#include "greenbtn.xpm"
#include "darkbtn.xpm"

IMPLEMENT_DYNAMIC_CLASS( wxFilterSettingsDlg, wxDialog )

BEGIN_EVENT_TABLE( wxFilterSettingsDlg, wxDialog )
    EVT_CLOSE( wxFilterSettingsDlg::OnClose )
    EVT_BUTTON( ID_BTN_OK, wxFilterSettingsDlg::OnOK )
END_EVENT_TABLE()

wxFilterSettingsDlg::wxFilterSettingsDlg( )
{
}

wxFilterSettingsDlg::~wxFilterSettingsDlg()
{
}

wxFilterSettingsDlg::wxFilterSettingsDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

bool wxFilterSettingsDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    // Set member variables here
    _textColour.Set( 150, 150, 250 );
    _backgroundColour.Set( 0, 8, 40 );
    _filterType = NULL;
    _btnOK = NULL;
	_slFrequency = NULL;
	_slQFactor = NULL;
	_filterEnabled = NULL;

    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
    return true;
}

void wxFilterSettingsDlg::CreateControls()
{    
    wxFilterSettingsDlg* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxFlexGridSizer* itemBoxSizer3 = new wxFlexGridSizer(4, 2, 0, 0);
    itemBoxSizer2->Add(itemBoxSizer3, 0, 0, 0 );

    wxStaticText* itemStaticText3 = new wxStaticText( itemDialog1, wxID_STATIC, _("Filter Type:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText3->SetForegroundColour(_textColour);
    itemBoxSizer3->Add(itemStaticText3, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	wxArrayString filterTypes;
	filterTypes.Add(_("Low Pass"));
	filterTypes.Add(_("Band Pass"));
	filterTypes.Add(_("High Pass"));
	filterTypes.Add(_("Notch"));
    _filterType = new wxChoice( itemDialog1, ID_FILTER_TYPE, wxDefaultPosition, wxDefaultSize, filterTypes );
	_filterType->SetSelection(0);
    itemBoxSizer3->Add(_filterType, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText16 = new wxStaticText( itemDialog1, wxID_STATIC, _("Filter Frequency:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText16->SetForegroundColour(_textColour);
    itemBoxSizer3->Add(itemStaticText16, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	_slFrequency = new wxSlider( itemDialog1, ID_FILTER_FREQUENCY, 0, 0, 200, wxDefaultPosition, wxSize(200,-1) );
	itemBoxSizer3->Add(_slFrequency, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText46 = new wxStaticText( itemDialog1, wxID_STATIC, _("Filter Q:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText46->SetForegroundColour(_textColour);
    itemBoxSizer3->Add(itemStaticText46, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	_slQFactor = new wxSlider( itemDialog1, ID_FILTER_Q, 0, 0, 200, wxDefaultPosition, wxSize(200,-1));
	itemBoxSizer3->Add(_slQFactor, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText56 = new wxStaticText( itemDialog1, wxID_STATIC, _("Filter Enabled:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText56->SetForegroundColour(_textColour);
    itemBoxSizer3->Add(itemStaticText56, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	wxBitmap* bitmap1 = new wxBitmap(greenbtn_xpm, wxBITMAP_TYPE_XPM );
	wxBitmap* bitmap2 = new wxBitmap(darkbtn_xpm, wxBITMAP_TYPE_XPM );
	_filterEnabled = new wxSwitch( itemDialog1, ID_FILTER_ENABLED, _T(""), wxDefaultPosition, wxSize(22,22) );
	if( bitmap1->Ok() && bitmap2->Ok() )
	{
		_filterEnabled->SetBitmaps(bitmap1, bitmap2);
	}
	itemBoxSizer3->Add(_filterEnabled, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer7, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 0 );

    _btnOK = new wxButton( itemDialog1, ID_BTN_OK, _T("OK" ));
    itemBoxSizer7->Add(_btnOK, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

}

bool wxFilterSettingsDlg::SetForegroundColour(const wxColour &colour)
{
	_textColour = colour;
	_filterType->SetForegroundColour(_textColour);
	_btnOK->SetForegroundColour(_textColour);
    _slFrequency->SetForegroundColour(_textColour);
    _slQFactor->SetForegroundColour(_textColour);
	_filterEnabled->SetForegroundColour(_textColour);
	wxDialog::SetForegroundColour(colour);
	Refresh();
	return true;
}

bool wxFilterSettingsDlg::SetBackgroundColour(const wxColour &colour)
{
	_backgroundColour = colour;
	_filterType->SetBackgroundColour(_backgroundColour);
	_btnOK->SetBackgroundColour(_backgroundColour);
	_slFrequency->SetBackgroundColour(_backgroundColour);
	_slQFactor->SetBackgroundColour(_backgroundColour);
	_filterEnabled->SetBackgroundColour(_backgroundColour);
	wxDialog::SetBackgroundColour(colour);
	Refresh();
	return true;
}

void wxFilterSettingsDlg::OnOK( wxCommandEvent& event )
{
	EndModal(0);
    event.Skip();
}

void wxFilterSettingsDlg::OnClose( wxCloseEvent& event )
{
    EndModal(0);
    event.Skip();
}

void wxFilterSettingsDlg::SetEnabled( bool enabled )
{
	_filterEnabled->SetValue(enabled);
}

bool wxFilterSettingsDlg::GetEnabled()
{
	return _filterEnabled->GetValue();
}

XAUDIO2_FILTER_PARAMETERS wxFilterSettingsDlg::GetFilterParameters()
{
	XAUDIO2_FILTER_PARAMETERS parameters;
	switch( _filterType->GetSelection() )
	{
	case 0:
		parameters.Type = LowPassFilter;
	case 1:
		parameters.Type = BandPassFilter;
	case 2:
		parameters.Type = HighPassFilter;
	case 3:
		parameters.Type = NotchFilter;
	}
	parameters.Frequency = ((float)_slFrequency->GetValue() / (float)_slFrequency->GetMax());
	parameters.OneOverQ = ((float)_slQFactor->GetValue() / (float)_slQFactor->GetMax());
	return parameters;
}

void wxFilterSettingsDlg::SetFilterParameters(XAUDIO2_FILTER_PARAMETERS parameters)
{
	switch( parameters.Type )
	{
	case LowPassFilter:
		_filterType->SetSelection(0);
	case BandPassFilter:
		_filterType->SetSelection(1);
	case HighPassFilter:
		_filterType->SetSelection(2);
	case NotchFilter:
		_filterType->SetSelection(3);
	}
	_slFrequency->SetValue(parameters.Frequency * (float)_slFrequency->GetMax());
	_slQFactor->SetValue(parameters.OneOverQ * (float)_slQFactor->GetMax());
}
