#pragma once

//#include "wx/ctrlsub.h"
#include "wx/radiobox.h"
#include "wx/image.h"

class wxBitmapRadioBox : public wxRadioBox
{
public:
	wxBitmapRadioBox() : wxRadioBox() {}
	~wxBitmapRadioBox() {}
    wxBitmapRadioBox( wxWindow* parent, wxWindowID id, const wxString &label, const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize, wxArrayString choices = wxArrayString(), int majorDimension = 0, long style = wxRA_SPECIFY_COLS )
    {
        Create( parent, id, label, pos, size, choices, majorDimension, style );
    }
    void Create( wxWindow* parent, wxWindowID id, const wxString &label, const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize, wxArrayString choices = wxArrayString(), int majorDimension = 0, long style = wxRA_SPECIFY_COLS);
	// We can pass in a bitmap or an image in order to create custom indicators.
	void SetBitmaps( wxBitmap * onImage, wxBitmap * offImage);
	void SetBitmaps( wxImage * onImage, wxImage * offImage);
	void OnPaint( wxPaintEvent& event );
	void OnKeyDown( wxKeyEvent& event );
	void OnKeyUp( wxKeyEvent& event );
 //   void Clear();
 //   void Delete(unsigned int);
 //   int DoAppend(const wxString&);
 //   int DoInsert(const wxString&, unsigned int);
	//int DoInsertItems(const wxArrayStringsAdapter &,unsigned int,void **,wxClientDataType);
	//void DoClear(void);
	//void DoDeleteOneItem(unsigned int);
 //   void DoSetItemClientData(unsigned int,void *);
 //   void *DoGetItemClientData(unsigned int) const;
 //   void DoSetItemClientObject(unsigned int,wxClientData *);
 //   wxClientData *DoGetItemClientObject(unsigned int) const;
    wxSize DoGetBestSize() const;
    void OnClick(wxMouseEvent& event);
 //   // wxControlWithItems overrides.
 //   unsigned int GetCount() const;
 //   wxString GetString(unsigned int) const;
 //   void SetString(unsigned int, const wxString&);
 //   void SetSelection(int);
 //   int GetSelection() const;
    // wxControlWithItems overrides end.
	DECLARE_EVENT_TABLE();
private:
    //int _style;
    wxString _label;
    //bool _showBorder;
    //int _numItems;
    wxArrayString _itemList;
    //int _selectedItem;
   	wxImage _onImage;
	wxImage _offImage;
};
