#include "wxAudioSettings.h"
#include "wx/stdpaths.h"
#include "RtAudio.h"

#include "spin.xpm"

IMPLEMENT_DYNAMIC_CLASS( wxAudioSettings, wxDialog )

BEGIN_EVENT_TABLE( wxAudioSettings, wxDialog )
    EVT_CLOSE( wxAudioSettings::OnClose )
    EVT_BUTTON( ID_BUTTON_CLOSE, wxAudioSettings::OnCloseButton )
END_EVENT_TABLE()

wxAudioSettings::wxAudioSettings( )
{
    _inText = NULL;
    _inDevice = NULL;
    _outText = NULL;
    _outDevice = NULL;
}

wxAudioSettings::~wxAudioSettings()
{
}

wxAudioSettings::wxAudioSettings( wxWindow* parent, AudioSettingsInterface* callback, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, callback, id, caption, pos, size, style);
}

bool wxAudioSettings::Create( wxWindow* parent, AudioSettingsInterface* callback, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    if( callback == NULL )
    {
        printf("Cannot create wxAudioSettings dialog without a callback.\n");
    }
    // Set member variables here
    _callback = callback;
    _btnClose = NULL;
    _inDevice = NULL;
    _outDevice = NULL;
    _inText = NULL;
    _outText = NULL;

    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();

    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
    return true;
}

void wxAudioSettings::CreateControls()
{
    wxAudioSettings* itemDialog1 = this;

    wxImage spinImage(spin_xpm);

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxFlexGridSizer* itemBoxSizer3 = new wxFlexGridSizer(2, 2, 0, 0);
    itemBoxSizer2->Add(itemBoxSizer3, 0, 0, 0 );

    RtAudio audio;
    int numDevices = audio.getDeviceCount();
    if( numDevices < 0 )
    {
        wxMessageBox( wxString::Format(_("ERROR: Pa_CountDevices returned 0x%x.\n"), numDevices ) );
    }

    _outText = new wxStaticText( itemDialog1, wxID_STATIC, _("Audio Out Device: "), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add( _outText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxArrayString empty;
    _outDevice = new wxKeylessChoice( itemDialog1, ID_MIDI_OUT_DEVICE, wxDefaultPosition, wxDefaultSize, empty );
    itemBoxSizer3->Add(_outDevice, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
    if( numDevices == 0 )
    {
        _outDevice->Enable(false);
    }

    _inText = new wxStaticText( itemDialog1, wxID_STATIC, _("Audio In Device: "), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add( _inText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    _inDevice = new wxKeylessChoice( itemDialog1, ID_MIDI_IN_DEVICE, wxDefaultPosition, wxDefaultSize, empty );
    itemBoxSizer3->Add(_inDevice, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
    if( numDevices == 0 )
    {
        _inDevice->Enable(false);
    }

    // Get input and output device details.
    RtAudio::StreamParameters outputParameters;
    RtAudio::StreamParameters inputParameters;
    RtAudio::DeviceInfo deviceInfo;;
    outputParameters.nChannels = 2;
    outputParameters.firstChannel = 0;
    inputParameters.nChannels = 2;
    inputParameters.firstChannel = 0;
    for( int i = 0; i < numDevices; i++ )
    {
        deviceInfo = audio.getDeviceInfo( i );
        outputParameters.deviceId = i;
        inputParameters.deviceId = i;

        for( int i = 0; i < deviceInfo.sampleRates.size(); i++ )
        {
            if( deviceInfo.sampleRates[i] == 44100 )
            {
                //_outDevice->Insert(wxString::Format(_("%s"), wxString::FromAscii(deviceInfo.name)).c_str(), 0, (void *)&outputParameters );
                //_inDevice->Insert(wxString::Format(_("%s"), wxString::FromAscii(deviceInfo.name)).c_str(), 0, (void *)&inputParameters );
                _outDevice->Insert(deviceInfo.name, 0, (void *)&outputParameters );
                _inDevice->Insert(deviceInfo.name, 0, (void *)&inputParameters );
            }
        }
    }

    _btnClose = new wxButton( itemDialog1, ID_BUTTON_CLOSE, _("Close"));
    itemBoxSizer2->Add(_btnClose, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
}

void wxAudioSettings::ShowInputDevice(bool state)
{
    if( _inDevice != NULL )
    {
        _inDevice->Show(state);
    }
    if( _inText != NULL )
    {
        _inText->Show(state);
    }
}

bool wxAudioSettings::SetForegroundColour(const wxColour &colour)
{
	_textColour = colour;
	_outDevice->SetForegroundColour(_textColour);
	_inDevice->SetForegroundColour(_textColour);
	_btnClose->SetForegroundColour(_textColour);
	wxDialog::SetForegroundColour(colour);
	Refresh();
	return true;
}

bool wxAudioSettings::SetBackgroundColour(const wxColour &colour)
{
    _backgroundColour = colour;
    if( _outDevice != NULL ) _outDevice->SetBackgroundColour(_backgroundColour);
    if( _inDevice != NULL ) _inDevice->SetBackgroundColour(_backgroundColour);
    if( _btnClose != NULL ) _btnClose->SetBackgroundColour(_backgroundColour);
    wxDialog::SetBackgroundColour(colour);
    Refresh();
    return true;
}

void wxAudioSettings::OnClose( wxCloseEvent& event )
{
    // TODO: On close, populate values back into MIDI settings data.
	EndModal(0);
    //Destroy();
    event.Skip();
}

void wxAudioSettings::OnCloseButton( wxCommandEvent& event )
{
    // TODO: On close, populate values back into MIDI settings data.
    EndModal(0);
    event.Skip();
}
