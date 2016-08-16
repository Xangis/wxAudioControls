#pragma once

#include "wx/ctrlsub.h"
#include "wx/image.h"

class wxBitmapRadioBox : public wxControlWithItems
{
public:
	wxBitmapRadioBox() : wxControlWithItems() {}
	~wxBitmapRadioBox() {}
    wxBitmapRadioBox( wxWindow* parent, wxWindowID id, const wxString &label, wxArrayString choices, const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize, int majorDimension = 0, long style = wxRA_SPECIFY_COLS )
    {
        Create( parent, id, label, choices, pos, size, majorDimension, style );
    }
    void Create( wxWindow* parent, wxWindowID id, const wxString &label, wxArrayString choices, const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize, int majorDimension = 0, long style = wxRA_SPECIFY_COLS);
	// We can pass in a bitmap or an image in order to create custom indicators.
	void SetBitmaps( wxBitmap * onImage, wxBitmap * offImage);
	void SetBitmaps( wxImage * onImage, wxImage * offImage);
	void OnPaint( wxPaintEvent& event );
	void OnKeyDown( wxKeyEvent& event );
	void OnKeyUp( wxKeyEvent& event );
    void Clear();
    void Delete(unsigned int);
    int DoAppend(const wxString&);
    int DoInsert(const wxString&, unsigned int);
    void DoSetItemClientData(unsigned int,void *);
    void *DoGetItemClientData(unsigned int) const;
    void DoSetItemClientObject(unsigned int,wxClientData *);
    wxClientData *DoGetItemClientObject(unsigned int) const;
    wxSize DoGetBestSize() const;
    void OnClick(wxMouseEvent& event);
    // wxControlWithItems overrides.
    unsigned int GetCount() const;
    wxString GetString(unsigned int) const;
    void SetString(unsigned int, const wxString&);
    void SetSelection(int);
    int GetSelection() const;
    // wxControlWithItems overrides end.
	DECLARE_EVENT_TABLE();
private:
    int _style;
    wxString _label;
    bool _showBorder;
    int _numItems;
    wxArrayString _itemList;
    int _selectedItem;
   	wxImage _onImage;
	wxImage _offImage;
};
