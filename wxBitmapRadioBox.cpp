#include "wxBitmapRadioBox.h"
#include "wx/dc.h"
#include "wx/dcclient.h"
#include "wx/dcmemory.h"

BEGIN_EVENT_TABLE(wxBitmapRadioBox, wxControlWithItems)
    EVT_KEY_DOWN(wxBitmapRadioBox::OnKeyDown)
    EVT_KEY_UP(wxBitmapRadioBox::OnKeyUp)
    EVT_PAINT(wxBitmapRadioBox::OnPaint)
    EVT_LEFT_DOWN(wxBitmapRadioBox::OnClick)
END_EVENT_TABLE()

void wxBitmapRadioBox::Create(wxWindow* parent, wxWindowID id, const wxString &label, wxArrayString choices, const wxPoint &pos, const wxSize &size, int, long style)
{
    _label = label;
    _selectedItem = -1;
    _style = style;
    _showBorder = true;
    _numItems = choices.Count();
    _itemList = choices;
    wxControlWithItems::Create( parent, id, pos, size, wxBORDER_NONE );
}

void wxBitmapRadioBox::OnPaint( wxPaintEvent& event )
{
    // Draw the image if we have one, otherwise draw a default graphic.
    wxPaintDC dc(this);
    wxColour bg = GetBackgroundColour();
    wxColour fg = GetForegroundColour();
    dc.SetTextForeground(fg);
    dc.SetTextBackground(bg);
    wxColour borderColour((fg.Red() + bg.Red() + bg.Red()) / 3, (fg.Green() + bg.Green() + bg.Green()) / 3,
        (fg.Blue() + bg.Blue() + bg.Blue()) / 3, (fg.Alpha() + bg.Alpha() + bg.Alpha()) / 3);
    dc.SetPen(wxPen(borderColour,2));
    dc.SetBrush(bg);
    dc.DrawRoundedRectangle(1, 7, (dc.GetSize().GetWidth() -2), (dc.GetSize().GetHeight()-7), 4 );
    dc.SetPen(wxPen(bg, 2));
    wxFont font(8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, _("Arial"));
    dc.SetFont(font); 
    int x = 0;
    int y = 0;
    dc.GetTextExtent(_label, &x, &y, 0, 0, &font);
    dc.DrawRectangle(9, 0, x+2, y );
    dc.DrawText(_label, 9, 0);
    for( int count = 0; count < _numItems; count++ )
    {
	    // Figure out whether to draw the on image or the off image.
	    if( _selectedItem == count )
	    {
            if( _onImage.Ok() )
            {
                wxBitmap buttonBitmap( _onImage );
			    dc.DrawBitmap( buttonBitmap, 3, (count*20+16), true );
            }
            else
            {
                dc.SetPen(*wxBLACK_PEN);
                dc.SetBrush(*wxRED_BRUSH);
                dc.DrawCircle(13, (count*20+26), 7);
            }
	    }
	    else
	    {
            if( _offImage.Ok() )
            {
			    wxBitmap buttonBitmap( _offImage );
			    dc.DrawBitmap( buttonBitmap, 3, (count*20+16), true );
            }
            else
            {
                dc.SetPen(*wxBLACK_PEN);
                dc.SetBrush(*wxGREY_BRUSH);
                dc.DrawCircle(13, (count*20+26), 7);
            }
	    }
        dc.DrawText(_itemList[count], 25, (count*20+19));
    }
	event.Skip(true);
}

/**
* This is required to prevent the control from defaulting to size 80,100.
*/
wxSize wxBitmapRadioBox::DoGetBestSize() const
{
    wxFont font(8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, _("Arial"));
    int x = 0;
    int y = 0;
    int width = 0;
    wxMemoryDC dc;
    for( int count = 0; count < _numItems; count++ )
    {
        dc.GetTextExtent(_itemList[count], &x, &y, 0, 0, &font);
        if( x > width )
            width = x;
    }
    y = _numItems * 20 + 24;
    x = width + 34;
	return wxSize(x, y);
}

void wxBitmapRadioBox::OnKeyDown( wxKeyEvent& event )
{
	wxWindow* parent = this->GetParent();
	if( parent )
	{
		parent->GetEventHandler()->ProcessEvent( event );
	}
	//event.Skip(true);
}

void wxBitmapRadioBox::OnKeyUp( wxKeyEvent& event )
{
	wxWindow* parent = this->GetParent();
	if( parent )
	{
		parent->GetEventHandler()->ProcessEvent( event );
	}
	//event.Skip(true);
}

/**
    @brief  Set bitmap for drawing button.
*/
void wxBitmapRadioBox::SetBitmaps( wxImage * onImage, wxImage * offImage )
{
    if( !onImage || !offImage )
    {
        return;
    }
    //_lightLock.lock();
	_onImage = *onImage;
	_offImage = *offImage;
    //_lightLock.unlock();
}

/**
    @brief  Set bitmap for drawing button.
*/
void wxBitmapRadioBox::SetBitmaps( wxBitmap * onImage, wxBitmap * offImage )
{
    if( !onImage || !offImage )
    {
        return;
    }
    //_lightLock.lock();
	_onImage = onImage->ConvertToImage();
	_offImage = offImage->ConvertToImage();
    //_lightLock.unlock();
}

unsigned int wxBitmapRadioBox::GetCount() const
{
    return _numItems;
}

wxString wxBitmapRadioBox::GetString(unsigned int selection) const
{
    if( selection >= 0 && selection < _numItems )
    {
        return _itemList[selection];
    }
    return wxEmptyString;
}

void wxBitmapRadioBox::SetString(unsigned int selection, const wxString& string)
{
    if( selection >= 0 && selection < _numItems )
    {
        _itemList[selection] = string;
    }
    Refresh();
}

void wxBitmapRadioBox::SetSelection(int selection)
{
    if( selection >= -1 && selection < _numItems )
    {
        _selectedItem = selection;
    }
    Refresh();
}

int wxBitmapRadioBox::GetSelection() const
{
    return _selectedItem;
}

void wxBitmapRadioBox::Clear()
{
    _numItems = 0;
    _selectedItem = -1;
    _itemList.Clear();
    Refresh();
}

void wxBitmapRadioBox::Delete(unsigned int selection)
{
    if( selection >= -1 && selection < _numItems )
    {
        if( selection == _selectedItem )
        {
            _selectedItem = -1;
        }
        _itemList.RemoveAt(selection,1);
        --_numItems;
    }
    Refresh();
}

int wxBitmapRadioBox::DoAppend(const wxString& name)
{
    _itemList.Add(name);
    ++_numItems;
    Refresh();
    return _numItems;
}

int wxBitmapRadioBox::DoInsert(const wxString& name, unsigned int selection)
{
    if( selection >= -1 && selection < _numItems )
    {
        if( selection == _selectedItem )
        {
            _selectedItem = -1;
        }
        _itemList.Insert(name, selection);
        --_numItems;
    }
    Refresh();
    return _numItems;
}

// We're not bothering with client data.
void wxBitmapRadioBox::DoSetItemClientData(unsigned int,void *)
{
}

void *wxBitmapRadioBox::DoGetItemClientData(unsigned int) const
{
    return NULL;
}

void wxBitmapRadioBox::DoSetItemClientObject(unsigned int,wxClientData *)
{
}

wxClientData *wxBitmapRadioBox::DoGetItemClientObject(unsigned int) const
{
    return NULL;
}

void wxBitmapRadioBox::OnClick(wxMouseEvent& event)
{
    int x = 0;
    int y = 0;
    event.GetPosition(&x, &y);
    x -= 3;
    y -= 16;
    if( x < 0 || y < 0 )
    {
        return;
    }
    int item = y / 20;
    if( item >= 0 && item < _numItems )
    {
        _selectedItem = item;
        Refresh();
    }

    // Send radio box selected event.
    wxCommandEvent evt(wxEVT_COMMAND_RADIOBOX_SELECTED, m_windowId);
    evt.SetInt( _selectedItem );
    if( _selectedItem >= 0 && _selectedItem < _numItems )
    {
        evt.SetString(_itemList[_selectedItem]);
    }
    evt.SetEventObject( this );
    ProcessCommand(evt);
}