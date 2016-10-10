#include "wxAudioSettings.h"
#include "wx/stdpaths.h"
#include "portaudio.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "spin.xpm"

IMPLEMENT_DYNAMIC_CLASS( wxAudioSettings, wxDialog )

BEGIN_EVENT_TABLE( wxAudioSettings, wxDialog )
    EVT_CLOSE( wxAudioSettings::OnClose )
    EVT_BUTTON( ID_BUTTON_CLOSE, wxAudioSettings::OnCloseButton )
END_EVENT_TABLE()

wxAudioSettings::wxAudioSettings( )
{
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

    wxFlexGridSizer* itemBoxSizer3 = new wxFlexGridSizer(5, 2, 0, 0);
    itemBoxSizer2->Add(itemBoxSizer3, 0, 0, 0 );

    int numDevices;

    numDevices = Pa_GetDeviceCount();
    if( numDevices < 0 )
    {
        wxMessageBox( wxString::Format(_("ERROR: Pa_CountDevices returned 0x%x.\n"), numDevices ) );
    }

    const PaDeviceInfo *deviceInfo;
    wxArrayString empty;
    _outDevice = new wxKeylessChoice( itemDialog1, ID_MIDI_OUT_DEVICE, wxDefaultPosition, wxDefaultSize, empty );
    itemBoxSizer3->Add(_outDevice, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	if( numDevices == 0 )
	{
		_outDevice->Enable(false);
	}

    // Get the list of available APIs.  We can use this to select devices by category.
    //PaHostApiIndex numApis = Pa_GetHostApiCount();
    //const PaHostApiInfo* apiInfo;
    //for( int j = 0; j < numApis; j++ )
    //{
    //    apiInfo = Pa_GetHostApiInfo(j);
    //}

    for( int i = 0; i < numDevices; i++ )
    {
        deviceInfo = Pa_GetDeviceInfo( i );
        //int 	structVersion
        //const char * 	name
        //PaHostApiIndex 	hostApi
        //int 	maxInputChannels
        //int 	maxOutputChannels
        //PaTime 	defaultLowInputLatency
        //PaTime 	defaultLowOutputLatency
        //PaTime 	defaultHighInputLatency
        //PaTime 	defaultHighOutputLatency
        //double 	defaultSampleRate

        PaStreamParameters* outputParameters = new PaStreamParameters;
        memset( outputParameters, 0, sizeof( PaStreamParameters ) ); //not necessary if you are filling in all the fields
        outputParameters->channelCount = 2;
        outputParameters->device = i;
        outputParameters->hostApiSpecificStreamInfo = NULL;
        outputParameters->sampleFormat = paFloat32;
        outputParameters->suggestedLatency = deviceInfo->defaultLowOutputLatency;
        outputParameters->hostApiSpecificStreamInfo = NULL; //See you specific host's API docs for info on using this field

        int err = Pa_IsFormatSupported( NULL, outputParameters, 44100 );
        if( err == paFormatIsSupported )
        {
            int msec = deviceInfo->defaultLowOutputLatency * 1000.0;
		    // Add the device to a list box on the GUI.
            if( msec )
            {
                _outDevice->Insert(wxString::Format(_("%s (%d ms) [%s]"), wxString::FromAscii(deviceInfo->name).c_str(),
                    msec, wxString::FromAscii(Pa_GetHostApiInfo(deviceInfo->hostApi)->name).c_str()), 0, (void *)outputParameters );
            }
            else
            {
                _outDevice->Insert(wxString::Format(_("%s [%s]"), wxString::FromAscii(deviceInfo->name).c_str(),
                    wxString::FromAscii(Pa_GetHostApiInfo(deviceInfo->hostApi)->name).c_str()), 0, (void *)outputParameters );
            }
        }
    }

    _btnClose = new wxButton( itemDialog1, ID_BUTTON_CLOSE, _("Close"));
    itemBoxSizer2->Add(_btnClose, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
}

bool wxAudioSettings::SetForegroundColour(const wxColour &colour)
{
	_textColour = colour;
	_outDevice->SetForegroundColour(_textColour);
	//_inDevice->SetForegroundColour(_textColour);
	_btnClose->SetForegroundColour(_textColour);
	wxDialog::SetForegroundColour(colour);
	Refresh();
	return true;
}

bool wxAudioSettings::SetBackgroundColour(const wxColour &colour)
{
	_backgroundColour = colour;
	_outDevice->SetBackgroundColour(_backgroundColour);
	//_inDevice->SetBackgroundColour(_backgroundColour);
	_btnClose->SetBackgroundColour(_backgroundColour);
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
