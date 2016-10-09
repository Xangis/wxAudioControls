#pragma once

#include "wx/wx.h"

#include "wx/image.h"

    #include "wx/control.h"
    #include "wx/settings.h"
    #include "wx/dc.h"
    #include "wx/dcclient.h"

/** 
     @brief     This class implements the wxKnob Control.
     A wxKnob is essentially a rotational slider.  The wxKnob can be provided
     with a bitmap to draw itself with.  If not provided with a bitmap, the
     wxKnob will draw itself as a circle with a hash mark.

     The wxKnob control catches mouse events and updates itself based on the
     angle, minimum, and maximum values.  It then forwards an EVT_SLIDER
     event that the application can catch in order to do any post processing.
     For instance, calling GetValue() to apply the value if the knob to some
     setting, i.e. volume.

     @note      This control could be improved - it is not very clear what
     value the knob is set to based on its rotation, especially where negative
     values are concerned.
*/
class wxKnob : public wxControl
{
public:
	wxKnob() : wxControl() { }

    wxKnob( wxWindow* parent, wxWindowID id, int value, int minValue,
		int maxValue, unsigned int minAngle = 240, unsigned int range = 300,
        const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize,
        long style = wxNO_BORDER, const wxValidator &validator = wxDefaultValidator,
        const wxString &name = wxT("knob"))
    {
        Create (parent, id, value, minValue, maxValue, minAngle, range, pos,
			size, style, validator, name );
    } 

	void Create( wxWindow* parent, wxWindowID id, int value, int minValue,
		int maxValue, unsigned int minAngle = 240, unsigned int range = 300,
		const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize( 30, 30 ),
		long style = 0, const wxValidator &validator = wxDefaultValidator,
		const wxString &name = wxT("knob"));

	virtual wxSize DoGetBestSize() const;
	void SetRange(int minValue, int maxValue );
	int GetMin()				{	return _min;							}
	int GetMax()				{	return _max;							}
	void SetMin( int minValue )	{	SetRange( minValue, GetMax());			}
	void SetMax( int maxValue )	{	SetRange( GetMin(), maxValue );			}
	unsigned int GetMinAngle()	{	return (_maxAngle - _range) % 360;	}
	int GetMaxAngle()			{	return _maxAngle;						}
	int GetValue()				{	return _setting;						}
	int SetValue( int value );

	/// We can pass in a bitmap or an image in order to create custom knobs.
	void SetBitmap( wxBitmap * image);
	void SetBitmap( wxImage * image);
	void SetDisabledBitmap( wxBitmap * image);
	void SetDisabledBitmap( wxImage * image);

private:
	int _min;
	int _max;
	int _setting;
	unsigned int _maxAngle;
	unsigned int _range;
	int _xSize;
	int _ySize;

	void GetCenter( int &x, int &y );
	void OnPaint( wxPaintEvent &event );
	void OnMouse( wxMouseEvent &event );

	wxImage _Image;

	DECLARE_EVENT_TABLE()
};
