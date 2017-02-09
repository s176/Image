#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>

class wxImagePanel : public wxPanel
{
	wxBitmap resized;
	int w, h;

public:
	wxImagePanel(wxWindow* parent);
	void SetImage(wxImage origimage);
	void paintEvent(wxPaintEvent & evt);
	void paintNow();
	void OnSize(wxSizeEvent& event);
	void MouseWheel(wxMouseEvent& event);
	void render(wxDC& dc);
	void mouseDown(wxMouseEvent& event);
	wxImage image;

	DECLARE_EVENT_TABLE()
};