#ifndef _WXMIDILOGGER_H_
#define _WXMIDILOGGER_H_

// wxWidgets dialog used for changing MIDI settings.

#include "wx/wx.h"
#include "wx/listctrl.h"

#define ID_MIDILOGGER_DLG 14000
#define SYMBOL_WXMIDILOGGER_STYLE wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_WXMIDILOGGER_TITLE _("MIDI Log")
#define SYMBOL_WXMIDILOGGER_IDNAME ID_MIDISETTINGS_DLG
#define SYMBOL_WXMIDILOGGER_SIZE wxSize(400, 300)
#define SYMBOL_WXMIDILOGGER_POSITION wxDefaultPosition
#define ID_BUTTON_CLOSE 14001
#define ID_CHK_MIDIOUT 14002
#define ID_MIDI_IN_DEVICE 14003
#define ID_MIDI_OUT_DEVICE 14004
#define ID_INPUTCHANNELSPIN 14005
#define ID_OUTPUTCHANNELSPIN 14006
#define ID_INPUTCHANNELTEXT 14008
#define ID_OUTPUTCHANNELTEXT 14009
#define ID_INPUTMESSAGES 14010
#define ID_OUTPUTMESSAGES 14011
#define ID_CLEARINPUT 14012
#define ID_CLEAROUTPUT 14013

class wxMidiLogger : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( wxMidiLogger )
    DECLARE_EVENT_TABLE()
public:
    wxMidiLogger();
    ~wxMidiLogger();
    wxMidiLogger( wxWindow* parent, wxWindowID id = ID_MIDILOGGER_DLG, const wxString& caption = SYMBOL_WXMIDILOGGER_TITLE, const wxPoint& pos = SYMBOL_WXMIDILOGGER_POSITION, const wxSize& size = SYMBOL_WXMIDILOGGER_SIZE, long style = SYMBOL_WXMIDILOGGER_STYLE );
    bool Create( wxWindow* parent, wxWindowID id = ID_MIDILOGGER_DLG, const wxString& caption = SYMBOL_WXMIDILOGGER_TITLE, const wxPoint& pos = SYMBOL_WXMIDILOGGER_POSITION, const wxSize& size = SYMBOL_WXMIDILOGGER_SIZE, long style = SYMBOL_WXMIDILOGGER_STYLE );
    void CreateControls();
    void OnClose( wxCloseEvent& event );
    void OnCloseButton( wxCommandEvent& event );
    void ClearInput( wxCommandEvent& event );
    void ClearOutput( wxCommandEvent& event );
    bool SetForegroundColour(const wxColour &colour);
    bool SetBackgroundColour(const wxColour &colour);
	void AddInMessage( wxString& message );
	void AddOutMessage( wxString& message );
private:
    wxListBox* _inputMessages;
    wxListBox* _outputMessages;
    wxButton* _btnClose;
	wxButton* _btnClearInput;
	wxButton* _btnClearOutput;
    wxColour _backgroundColour;
    wxColour _textColour;
    wxStaticText* _inputChannelText;
    wxStaticText* _outputChannelText;
};

#endif
