#include "wxBitmapRadioBox.h"
#include "wx/dc.h"
#include "wx/dcclient.h"
#include "wx/dcmemory.h"

BEGIN_EVENT_TABLE(wxBitmapRadioBox, wxRadioBox)
    EVT_KEY_DOWN(wxBitmapRadioBox::OnKeyDown)
    EVT_KEY_UP(wxBitmapRadioBox::OnKeyUp)
    EVT_PAINT(wxBitmapRadioBox::OnPaint)
    EVT_LEFT_DOWN(wxBitmapRadioBox::OnClick)
END_EVENT_TABLE()

void wxBitmapRadioBox::Create(wxWindow* parent, wxWindowID id, const wxString &label, const wxPoint &pos, const wxSize &size, wxArrayString choices, int, long style)
{
    _itemList = choices;
	_label = label;
    wxRadioBox::Create( parent, id, label, pos, size, choices, 0, style|wxBORDER_NONE);
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
    for( int count = 0; count < GetCount(); count++ )
    {
	    // Figure out whether to draw the on image or the off image.
	    if( GetSelection() == count )
	    {
            if( _onImage.Ok() )
            {
                wxBitmap buttonBitmap( _onImage );
			    dc.DrawBitmap( buttonBitmap, 3, (count*20+16), true );
            }
            else
            {
                dc.SetPen(fg);
                dc.SetBrush(bg);
                dc.DrawCircle(13, 7, (count*20+26));
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
                dc.SetPen(fg);
                dc.SetBrush(bg);
                dc.DrawCircle(13, 7, (count*20+26));
            }
	    }
        dc.SetPen(fg);
        dc.SetBrush(bg);
        dc.DrawText(_itemList[count], 25, (count*20+19));
    }
	event.Skip(true);
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
    if( item >= 0 && item < this->GetCount() )
    {
        SetSelection(item);
        Refresh();
    }

    // Send radio box selected event.
    wxCommandEvent evt(wxEVT_COMMAND_RADIOBOX_SELECTED, m_windowId);
    evt.SetInt( item );
    if( item >= 0 && item < this->GetCount() )
    {
        evt.SetString(this->_itemList[item]);
    }
    evt.SetEventObject( this );
    ProcessCommand(evt);
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
    for( int count = 0; count < GetCount(); count++ )
    {
        dc.GetTextExtent(_itemList[count], &x, &y, 0, 0, &font);
        if( x > width )
            width = x;
    }
    y = GetCount() * 20 + 24;
    x = width + 34;
       return wxSize(x, y);
}

