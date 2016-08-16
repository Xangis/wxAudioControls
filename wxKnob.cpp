
#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma implementation "wxKnob.h"
#endif

#include "wxKnob.h"
#include <math.h>

#define PI 3.14159265358979323846

// ----------------------------------------------------------------------------
// the wxKnob class
// ----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(wxKnob,wxControl)
    EVT_PAINT       (wxKnob::OnPaint)
    EVT_LEFT_DOWN   (wxKnob::OnMouse)
    EVT_LEFT_UP     (wxKnob::OnMouse)
    EVT_MOTION      (wxKnob::OnMouse)
END_EVENT_TABLE()

/**
     @brief     Sets initial values on wxKnob control.
     Sets initial values on wxKnob control.
     @return
     void
*/
void wxKnob::Create (wxWindow* parent, wxWindowID id, int value,
                     int minValue, int maxValue,
                     unsigned int minAngle, unsigned int range,
                     const wxPoint &pos,
                     const wxSize &size,
                     long style,
                     const wxValidator &validator,
                     const wxString &name)
{
    _Image.Destroy();
    wxControl::Create (parent, id, pos, size, style, validator, name);
    _setting = 0; 
    _min = minValue;
    _max = maxValue;
	_xSize = size.GetX();
	_ySize = size.GetY();
    range %= 360;
    minAngle %= 360;
    _maxAngle = (minAngle + 360 - range) % 360;
   
    _range = range;
    SetValue (value);
}

/**
    @brief  Sets minimum and maximum values for wxKnob.
*/
void wxKnob::SetRange (int minValue, int maxValue)
{
    if (minValue < maxValue)
    {
        _min = minValue;
        _max = maxValue;
        SetValue (_setting);
    }
}

/**
    @brief  Sets current value for wxKnob.
*/   
int wxKnob::SetValue (int value)
{
    if (value < _min)
	{
        value = _min;
	}
    else if (value > _max)
	{
        value = _max;
	}
   
    if (value != _setting)
    {
        _setting = value;
        Refresh ();
        Update ();
    }

    return( 0 );
}

/**
     @brief     Drawing routine for wxKnob.
     OnPaint will calculate the angle of rotation of the knob based on its value and
     draw either a circle with a hash mark if no bitmap has been assigned to the knob,
     or will rotate and draw the bitmap associated with the knob if one has been
     attached.
     @return
     void
*/
void wxKnob::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    //int sizeX, sizeY;
    double theta = 0.0;
    double dx = 0.0;
    double dy = 0.0;
    int cx = 0;
    int cy = 0;
    int r = 0;
    int r2 = 0;
    wxSize s = GetSize ();
   
    theta = (PI / 180.) * (_maxAngle +
                           (((double) _max - _setting) / (_max - _min))
                           * _range);
    dx = cos (theta);
    dy = -sin (theta);      // - because of upside down coordinates
   
    wxPaintDC dc(this);

    GetCenter (cx, cy);
    r = floor (((s.x < s.y) ? s.x : s.y) * .48);
    r2 = floor (r * .6);
   
    if( !_Image.Ok() )
    {
		if( IsEnabled() )
		{
			dc.SetPen (*wxBLACK_PEN);
			dc.SetBrush( *wxWHITE_BRUSH );
		}
		else
		{
			dc.SetPen (*wxBLACK_PEN);
			dc.SetBrush( *wxGREY_BRUSH );
		}
		dc.DrawCircle (cx, cy, r);
		dc.DrawLine (cx + (int)floor (r * dx), cy + (int)floor (r * dy),
					cx + (int)floor (r2 * dx), cy + (int)floor (r2 * dy));
    }
    else
    {
		// Rotate the image and convert to a bitmap before drawing.  We don't start with a bitmap because
		// it has no rotate() method.
		wxPoint centerPoint( (_Image.GetWidth() / 2  ), (_Image.GetHeight() / 2 ) );
		// Rotation offset required to keep the knob from jumping as it rotates.
		wxPoint rotationOffset;
		// Non-destructive rotation returns an image, we contstruct the bitmap from the image.
		wxBitmap knobBitmap( _Image.Rotate( theta, centerPoint, true, &rotationOffset ) );
		dc.DrawBitmap( knobBitmap, rotationOffset.x, rotationOffset.y, true );
    }
}

/**
     @brief     Mouse handler for wxKnob.
     Handles mouse input and calculates angle of rotation and value based on the
     clicking and dragging of the mouse.  Windows containing a knob control can
     then handle EVT_SLIDER for any postprocessing.
     @return
     void
*/
void wxKnob::OnMouse (wxMouseEvent &event)
{
    int cx, cy;
    double dx, dy, theta, dt;
    int newval;
   
    if (event.Moving ())
    {
        event.Skip ();
        return;
    }
   
    GetCenter (cx, cy);
    dx = event.m_x - cx;
    dy = cy - event.m_y;
    if (dx == 0. && dy == 0.)
	{
        return;
	}
   
    theta = atan2 (dy, dx) * 180. / PI;
    if (theta < 0.)
	{
        theta += 360.;
	}
   
    dt = theta - _maxAngle;
    if (dt < 0.)
	{
        dt += 360;
	}
    if (dt > _range)
	{
        return;
	}
    newval = int (_max - (dt / _range) * (_max - _min));

    SetValue (newval);
    if (event.Dragging () || event.ButtonUp ())
    {
        wxEventType scrollEvent = wxEVT_NULL ;
        if (event.ButtonUp ())
		{
            scrollEvent = wxEVT_SCROLL_THUMBRELEASE;
		}
        else
		{
            scrollEvent = wxEVT_SCROLL_THUMBTRACK;
		}
           
        wxScrollEvent event (scrollEvent, m_windowId);
        event.SetPosition (newval);
        event.SetEventObject (this);
        GetEventHandler()->ProcessEvent (event);

        wxCommandEvent cevent (wxEVT_COMMAND_SLIDER_UPDATED, m_windowId);
        cevent.SetInt (newval);
        cevent.SetEventObject (this);
        GetEventHandler()->ProcessEvent (cevent);
    }
}

void wxKnob::GetCenter (int &x, int &y)
{
    wxSize s = GetSize ();
    x = s.x / 2;
    y = s.y / 2;
}

/**
    @brief  Set bitmap for drawing button.
*/
void wxKnob::SetBitmap( wxImage * image)
{
    if( !image )
    {
        return;
    }
	_Image = *image;
}


/**
* This is required to prevent the control from defaulting to size 80,100.
*/
wxSize wxKnob::DoGetBestSize() const
{
	return wxSize(_xSize, _ySize);
}

/**
    @brief  Set bitmap for drawing button.
*/
void wxKnob::SetBitmap( wxBitmap * image)
{
    if( !image )
    {
        return;
    }
	_Image = image->ConvertToImage();
}

/**
    @brief  Set bitmap for drawing button when control is disabled.
*/
void wxKnob::SetDisabledBitmap( wxImage * image)
{
	_Image = *image;
}

/**
    @brief  Set bitmap for drawing button when control is disabled.
*/
void wxKnob::SetDisabledBitmap( wxBitmap * image)
{
	_Image = image->ConvertToImage();
}

