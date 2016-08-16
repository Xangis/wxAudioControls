#pragma once

#include "wx/wx.h"
#include "wavefile.h"
#include <vector>

class wxWavePanel: public wxPanel
{
    DECLARE_DYNAMIC_CLASS( wxWavePanel )
    DECLARE_EVENT_TABLE()
public:
    /// wxEVT_PAINT event handler for ID_PANEL
    void OnPaint( wxPaintEvent& event );
	void OnSize( wxSizeEvent& event );
	wxWavePanel( );
    wxWavePanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style );
	void SetWaveFile( WaveFile* waveFile );
	//void SetData( void* data, int length, int bytesPerSample, int numChannels );
    void SetForeground( const wxPen* pen ) { _penColor = pen; }
    void SetBackground( const wxBrush* brush ) { _backgroundBrushColor = brush; }
	void EnableHighQuality( bool enabled );
	void SetIndicatorSamplePoints( std::vector<int>* points );
	void ClearIndicators();
private:
	WaveFile* _waveFile;
    const wxPen* _penColor;
    const wxBrush* _backgroundBrushColor;
	std::vector<int> _indicatorLines;
	std::vector<int> _maxPixelPeaksL;
	std::vector<int> _maxPixelPeaksR;
	std::vector<int> _minPixelPeaksL;
	std::vector<int> _minPixelPeaksR;
	bool _highQuality;
	void RefreshPeaks(int width);
};
