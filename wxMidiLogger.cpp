#include "wxMidiLogger.h"
#include "wx/stdpaths.h"

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

// Image resources
#include "greenbtn.xpm"
#include "darkbtn.xpm"
#include "spin.xpm"

IMPLEMENT_DYNAMIC_CLASS( wxMidiLogger, wxDialog )

BEGIN_EVENT_TABLE( wxMidiLogger, wxDialog )
    EVT_CLOSE( wxMidiLogger::OnClose )
    EVT_BUTTON( ID_BUTTON_CLOSE, wxMidiLogger::OnCloseButton )
	EVT_BUTTON( ID_CLEARINPUT, wxMidiLogger::ClearInput )
	EVT_BUTTON( ID_CLEAROUTPUT, wxMidiLogger::ClearOutput )
END_EVENT_TABLE()

wxMidiLogger::wxMidiLogger( )
{
}

wxMidiLogger::~wxMidiLogger()
{
}

wxMidiLogger::wxMidiLogger( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

bool wxMidiLogger::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    // Set member variables here
    _btnClose = NULL;

    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();

    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
    return true;
}

void wxMidiLogger::CreateControls()
{
    wxMidiLogger* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(3, 2, 0, 0);
    itemBoxSizer2->Add(gridSizer, 0, 0, 0 );

    _inputChannelText = new wxStaticText( itemDialog1, wxID_STATIC, _("MIDI In Messages:"), wxDefaultPosition, wxDefaultSize, 0 );
    gridSizer->Add(_inputChannelText, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    _outputChannelText = new wxStaticText( itemDialog1, wxID_STATIC, _("MIDI Out Messages:"), wxDefaultPosition, wxDefaultSize, 0 );
    gridSizer->Add(_outputChannelText, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	_inputMessages = new wxListBox( itemDialog1, ID_INPUTMESSAGES, wxDefaultPosition, wxSize(240, 240) );
    gridSizer->Add(_inputMessages, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
	_outputMessages = new wxListBox( itemDialog1, ID_OUTPUTMESSAGES, wxDefaultPosition, wxSize(240, 240) );
    gridSizer->Add(_outputMessages, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
	_btnClearInput = new wxButton( itemDialog1, ID_CLEARINPUT, _("Clear"));
	gridSizer->Add(_btnClearInput, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	_btnClearOutput = new wxButton( itemDialog1, ID_CLEAROUTPUT, _("Clear"));
	gridSizer->Add(_btnClearOutput, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _btnClose = new wxButton( itemDialog1, ID_BUTTON_CLOSE, _("Close"));
    itemBoxSizer2->Add(_btnClose, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
}

void wxMidiLogger::AddInMessage( wxString& message )
{
	_inputMessages->Append(message);
}

void wxMidiLogger::AddOutMessage( wxString& message )
{
	_outputMessages->Append(message);
}

bool wxMidiLogger::SetForegroundColour(const wxColour &colour)
{
	_textColour = colour;
    _inputChannelText->SetForegroundColour(_textColour);
    _outputChannelText->SetForegroundColour(_textColour);
	_btnClose->SetForegroundColour(_textColour);
	wxDialog::SetForegroundColour(colour);
	Refresh();
	return true;
}

bool wxMidiLogger::SetBackgroundColour(const wxColour &colour)
{
	_backgroundColour = colour;
	_btnClose->SetBackgroundColour(_backgroundColour);
	wxDialog::SetBackgroundColour(colour);
	Refresh();
	return true;
}

void wxMidiLogger::ClearInput( wxCommandEvent& event )
{
    _inputMessages->Clear();
    event.Skip();
}

void wxMidiLogger::ClearOutput( wxCommandEvent& event )
{
    _outputMessages->Clear();
    event.Skip();
}

void wxMidiLogger::OnClose( wxCloseEvent& event )
{
    Hide();
    event.Skip();
}

void wxMidiLogger::OnCloseButton( wxCommandEvent& event )
{
    Hide();
    event.Skip();
}

