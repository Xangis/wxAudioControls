#ifndef _WXVECTORDLG_H_
#define _WXVECTORDLG_H_

// wxWidgets dialog used for changing MIDI settings.

#include "wx/wx.h"

#define ID_VECTOR_DLG 19000
#define SYMBOL_WXVECTORDLG_STYLE wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_WXVECTORDLG_TITLE _("Vector Control")
#define SYMBOL_WXVECTORDLG_IDNAME ID_MIDISETTINGS_DLG
#define SYMBOL_WXVECTORDLG_SIZE wxSize(400, 300)
#define SYMBOL_WXVECTORDLG_POSITION wxDefaultPosition
#define ID_VBUTTON_CLOSE 19001
#define ID_VECTORPANEL 19002

class wxVectorDlg : public wxDialog
{
    DECLARE_DYNAMIC_CLASS( wxVectorDlg )
    DECLARE_EVENT_TABLE()
public:
    wxVectorDlg();
    ~wxVectorDlg();
    wxVectorDlg( wxWindow* parent, wxWindowID id = ID_VECTOR_DLG, const wxString& caption = SYMBOL_WXVECTORDLG_TITLE, const wxPoint& pos = SYMBOL_WXVECTORDLG_POSITION, const wxSize& size = SYMBOL_WXVECTORDLG_SIZE, long style = SYMBOL_WXVECTORDLG_STYLE );
    bool Create( wxWindow* parent, wxWindowID id = ID_VECTOR_DLG, const wxString& caption = SYMBOL_WXVECTORDLG_TITLE, const wxPoint& pos = SYMBOL_WXVECTORDLG_POSITION, const wxSize& size = SYMBOL_WXVECTORDLG_SIZE, long style = SYMBOL_WXVECTORDLG_STYLE );
    void CreateControls();
    void OnClose( wxCloseEvent& event );
    void OnCloseButton( wxCommandEvent& event );
    bool SetForegroundColour(const wxColour &colour);
    bool SetBackgroundColour(const wxColour &colour);
private:
    wxStaticBitmap* _vectorPanel;
    wxButton* _btnClose;
    wxColour _backgroundColour;
    wxColour _textColour;
    wxStaticText* _inputChannelText;
    wxStaticText* _outputChannelText;
};

#endif
