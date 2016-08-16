#include "wxWavePanel.h"

IMPLEMENT_DYNAMIC_CLASS( wxWavePanel, wxPanel )

BEGIN_EVENT_TABLE( wxWavePanel, wxPanel )
	EVT_PAINT( wxWavePanel::OnPaint )
	EVT_SIZE( wxWavePanel::OnSize )
END_EVENT_TABLE()

wxWavePanel::wxWavePanel()
{
	_highQuality = true;
    _waveFile = NULL;
}

wxWavePanel::wxWavePanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
	_highQuality = true;
    _waveFile = NULL;
    Create(parent, id, pos, size, style);
    _penColor = wxCYAN_PEN;
    _backgroundBrushColor = wxBLACK_BRUSH;
}

void wxWavePanel::SetWaveFile(WaveFile* waveFile)
{
	_waveFile = waveFile;
	Refresh();
}

void wxWavePanel::OnSize( wxSizeEvent& event )
{
	RefreshPeaks(event.GetSize().GetWidth());
	Refresh();
	event.Skip();
}

/**
* Generates the peak (level) data for a window of a particular size so we don't have to 
* recalculate every time OnPaint is called.  This will make resizing and initial file load
* smaller, but make normal use much faster.
*/
void wxWavePanel::RefreshPeaks(int width)
{
	if( width == (int)_minPixelPeaksL.size() )
	{
		return;
	}
	_minPixelPeaksL.clear();
	_minPixelPeaksR.clear();
	_maxPixelPeaksL.clear();
	_maxPixelPeaksR.clear();

	int numSamples;
	int channels;
	short* data;
	if( _waveFile != NULL && _waveFile->GetNumSamples() != 0 )
	{
		numSamples = _waveFile->GetNumSamples();
		channels = _waveFile->GetNumChannels();
		data = _waveFile->GetData();
	}
	else
	{
		return;
	}

    int horizontalSkip = numSamples / width;
    if( horizontalSkip < 1 ) horizontalSkip = 1;

	int count;
    int point = 0;
	// Low-Quality Rendering Mode -- Picks exact peaks.
	if( !_highQuality || horizontalSkip == 1)
	{
		if( channels == 1 )
		{
			for( count = 0; count < width; count++ )
			{
				point = count * horizontalSkip;
				if( point < numSamples )
				{
					_minPixelPeaksL.push_back((int)data[point]);
					_maxPixelPeaksL.push_back((int)data[point]);
				}
				else
				{
					_minPixelPeaksL.push_back(0);
					_maxPixelPeaksL.push_back(0);
				}
			}
		}
		else if( channels == 2 )
		{
			for( count = 0; count < width; count++ )
			{
				point = count * horizontalSkip * 2;
				if( point % 2 == 1 )
				{
					point--;
				}
				if( point < (numSamples * 2) )
				{
					_minPixelPeaksL.push_back( (int)data[point] );
					_maxPixelPeaksL.push_back( (int)data[point] );
					_minPixelPeaksR.push_back( (int)data[point+1] );
					_maxPixelPeaksR.push_back( (int)data[point+1] );
				}
				else
				{
					_minPixelPeaksL.push_back(0);
					_maxPixelPeaksL.push_back(0);
					_minPixelPeaksR.push_back(0);
					_maxPixelPeaksR.push_back(0);
				}
			}
		}
	}
	// High-quality rendering mode -- examines every sample.
	else
	{
		int start = 0;
		int minValueL = 0;
		int minValueR = 0;
		int maxValueL = 0;
		int maxValueR = 0;
		for( count = 0; count < numSamples; count++ )
		{
			if( channels == 1 )
			{
				if( data[count] > maxValueL ) maxValueL = data[count];
				if( data[count] < minValueL ) minValueL = data[count];
				if( count == (start+horizontalSkip-1))
				{
					_minPixelPeaksL.push_back(minValueL);
					_maxPixelPeaksL.push_back(maxValueL);
					minValueL = 0;
					maxValueL = 0;
					start = count+1;
				}
			}
			else if( channels == 2 )
			{
				if( data[count*2] > maxValueL ) maxValueL = data[count*2];
				if( data[count*2] < minValueL ) minValueL = data[count*2];
				if( data[count*2+1] > maxValueR ) maxValueR = data[count*2+1];
				if( data[count*2+1] < minValueR ) minValueR = data[count*2+1];
				if( count == (start+horizontalSkip-1))
				{
					_minPixelPeaksL.push_back(minValueL);
					_minPixelPeaksR.push_back(minValueR);
					_maxPixelPeaksL.push_back(maxValueL);
					_maxPixelPeaksR.push_back(maxValueR);
					minValueL = 0;
					maxValueL = 0;
					minValueR = 0;
					maxValueR = 0;
					start = count+1;
				}
			}
		}
	}

	// Delete the data if we're using a WaveFile since we're responsible for cleanup.
	delete[] data;
}

//void wxWavePanel::SetData( void* data, int length, int bytesPerSample, int numChannels )
//{
//	if( _waveFile != 0 )
//	{
//		delete _waveFile;
//		_waveFile = NULL;
//	}
//	_pixelPeaksL.clear();
//	_pixelPeaksR.clear();
//	_indicatorLines.clear();
//}

/*!
 * wxEVT_PAINT event handler for ID_PANEL
 */
void wxWavePanel::OnPaint( wxPaintEvent& event )
{
    wxPaintDC dc(this);

    dc.SetBackground( *_backgroundBrushColor );
	dc.Clear(); 

	if( _waveFile == NULL )
	{
		event.Skip(false);
		return;
	}

	int width;
	int height;
    GetClientSize(&width, &height);

	if( (int)_minPixelPeaksL.size() != width )
	{
		RefreshPeaks(width);
	}

	dc.SetPen( *_penColor );

	int channels = _waveFile->GetNumChannels();
	int verticalScale;
	if( channels == 2 )
	{
		verticalScale = 32768 / (height / 4);
		dc.DrawLine( wxPoint( 0, height/4), wxPoint( width-1, height/4) );
		dc.DrawLine( wxPoint( 0, height*3/4), wxPoint( width-1, height*3/4) );
	}
	else
	{
	    verticalScale = 32768 / (height / 2);
		dc.DrawLine( wxPoint( 0, height / 2), wxPoint( width-1, height/2) );
	}
	// Draw waveforms.
	for( int count = 0; count < width; count++ )
    {
		if( channels == 1 )
		{
            int maxLocationY = (height / 2) - (_maxPixelPeaksL[count] / verticalScale );
            int minLocationY = (height / 2) - (_minPixelPeaksL[count] / verticalScale );
            dc.DrawLine( wxPoint(count, minLocationY), wxPoint( count, maxLocationY ));
		}
		else
		{
			int maxLocationLY = (height / 4) - (_maxPixelPeaksL[count] / verticalScale );
			int minLocationLY = (height / 4) - (_minPixelPeaksL[count] / verticalScale );
			dc.DrawLine( wxPoint( count, minLocationLY), wxPoint( count, maxLocationLY ));
			int maxLocationRY = ((height * 3) / 4) - (_maxPixelPeaksR[count] / verticalScale );
			int minLocationRY = ((height * 3) / 4) - (_minPixelPeaksR[count] / verticalScale );
			dc.DrawLine( wxPoint(count, minLocationRY), wxPoint( count, maxLocationRY ));
		}
    }
	// Draw indicators, if any.
	if( _indicatorLines.size() > 0 && _waveFile != NULL )
	{
		dc.SetPen(*wxGREEN_PEN);
		for( unsigned int i = 0; i < _indicatorLines.size(); i++ )
		{
			int x = (_indicatorLines[i] * width) / (_waveFile->GetNumSamples() / _waveFile->GetNumChannels());
			dc.DrawLine( wxPoint( x, 0 ), wxPoint( x, height ));
		}
	}

	event.Skip(false);
}

void wxWavePanel::ClearIndicators()
{
	_indicatorLines.clear();
	Refresh();
}

void wxWavePanel::SetIndicatorSamplePoints( std::vector<int>* points )
{
	_indicatorLines.clear();
	for( unsigned int i = 0; i < points->size(); i++ )
	{
		_indicatorLines.push_back((*points)[i]);
	}
	Refresh();
}

void wxWavePanel::EnableHighQuality( bool enabled )
{
	_highQuality = enabled;
	_maxPixelPeaksL.clear();
	_maxPixelPeaksR.clear();
	_minPixelPeaksL.clear();
	_minPixelPeaksR.clear();
	RefreshPeaks(this->GetSize().GetWidth());
}