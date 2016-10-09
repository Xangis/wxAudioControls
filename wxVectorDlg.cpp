#include "wxVectorDlg.h"
#include "wx/stdpaths.h"
#include "large_reticle.xpm"

IMPLEMENT_DYNAMIC_CLASS( wxVectorDlg, wxDialog )

BEGIN_EVENT_TABLE( wxVectorDlg, wxDialog )
    EVT_CLOSE( wxVectorDlg::OnClose )
    EVT_BUTTON( ID_BUTTON_CLOSE, wxVectorDlg::OnCloseButton )
END_EVENT_TABLE()

wxVectorDlg::wxVectorDlg( )
{
}

wxVectorDlg::~wxVectorDlg()
{
}

wxVectorDlg::wxVectorDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

bool wxVectorDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
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

void wxVectorDlg::CreateControls()
{
    wxVectorDlg* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

	wxBitmap reticleBitmap(large_reticle_xpm, wxBITMAP_TYPE_XPM);
	_vectorPanel = new wxStaticBitmap( itemDialog1, ID_INPUTMESSAGES, reticleBitmap, wxDefaultPosition, wxSize(500, 500) );
    itemBoxSizer2->Add(_vectorPanel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
	_vectorPanel->SetBackgroundColour(wxColour(16, 32, 96));
	
    _btnClose = new wxButton( itemDialog1, ID_BUTTON_CLOSE, _("Close"));
    itemBoxSizer2->Add(_btnClose, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
}

bool wxVectorDlg::SetForegroundColour(const wxColour &colour)
{
	_textColour = colour;
    _inputChannelText->SetForegroundColour(_textColour);
    _outputChannelText->SetForegroundColour(_textColour);
	_btnClose->SetForegroundColour(_textColour);
	wxDialog::SetForegroundColour(colour);
	Refresh();
	return true;
}

bool wxVectorDlg::SetBackgroundColour(const wxColour &colour)
{
	_backgroundColour = colour;
	_btnClose->SetBackgroundColour(_backgroundColour);
	wxDialog::SetBackgroundColour(colour);
	Refresh();
	return true;
}

void wxVectorDlg::OnClose( wxCloseEvent& event )
{
    Hide();
    event.Skip();
}

void wxVectorDlg::OnCloseButton( wxCommandEvent& event )
{
    Hide();
    event.Skip();
}

