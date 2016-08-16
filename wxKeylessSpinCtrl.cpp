#include "wxKeylessSpinCtrl.h"

BEGIN_EVENT_TABLE(wxKeylessSpinCtrl,wxSpinCtrl)
    EVT_KEY_DOWN(wxKeylessSpinCtrl::OnKeyDown)
    EVT_KEY_UP(wxKeylessSpinCtrl::OnKeyUp)
    EVT_PAINT(wxKeylessSpinCtrl::OnPaint)
END_EVENT_TABLE()

void wxKeylessSpinCtrl::Create(wxWindow* parent, wxWindowID id, const wxString& value,
        const wxPoint &pos, const wxSize &size, long style,
		int min, int max, int initial)
{
    wxSpinCtrl::Create( parent, id, value, pos, size, style, min, max, initial );
}

#ifndef linux
void wxKeylessSpinCtrl::OnPaint( wxPaintEvent& event )
{
	wxSpinCtrl::OnPaint(event);
	event.Skip();
}
#endif

void wxKeylessSpinCtrl::OnKeyDown( wxKeyEvent& event )
{
	wxWindow* parent = this->GetParent();
	if( parent )
	{
		parent->ProcessEvent( event );
	}
	//event.Skip(true);
}

void wxKeylessSpinCtrl::OnKeyUp( wxKeyEvent& event )
{
	wxWindow* parent = this->GetParent();
	if( parent )
	{
		parent->ProcessEvent( event );
	}
	//event.Skip(true);
}
