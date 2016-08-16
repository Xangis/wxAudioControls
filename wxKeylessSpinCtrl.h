#ifndef _WXKEYLESSSPINCTRL_H_
#define _WXKEYLESSSPINCTRL_H_

#include "wx/spinctrl.h"

class wxKeylessSpinCtrl : public wxSpinCtrl
{
public:
	wxKeylessSpinCtrl() : wxSpinCtrl() {}
	~wxKeylessSpinCtrl() {}
    wxKeylessSpinCtrl( wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString,
		const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxSP_ARROW_KEYS,
		int min = 0, int max = 100, int initial = 0)
    {
        Create( parent, id, value, pos, size, style, min, max, initial );
    }
    void Create( wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString,
        const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxSP_ARROW_KEYS,
		int min = 0, int max = 100, int initial = 0);
	void OnPaint( wxPaintEvent& event );
	void OnKeyDown( wxKeyEvent& event );
	void OnKeyUp( wxKeyEvent& event );
	DECLARE_EVENT_TABLE();
};

#endif