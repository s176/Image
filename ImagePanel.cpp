#include <wx/dcbuffer.h>
#include "ImagePanel.h"


BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
EVT_PAINT(wxImagePanel::paintEvent)
EVT_SIZE(wxImagePanel::OnSize)
EVT_MOUSEWHEEL(wxImagePanel::MouseWheel)
EVT_LEFT_DOWN(wxImagePanel::mouseDown)
END_EVENT_TABLE()

wxImagePanel::wxImagePanel(wxWindow* parent) :
	wxPanel(parent)
{
	w = -1;
	h = -1;
}

void wxImagePanel::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	render(dc);
}

void wxImagePanel::paintNow()
{
	wxClientDC dc(this); 
	render(dc);
}

void wxImagePanel::SetImage(wxImage origimage)
{
	image = origimage;
	Refresh();
}

void wxImagePanel::render(wxDC&  dc)
{
	int newWidth, newHeight, oldWidth, oldHeight;
	dc.GetSize(&newWidth, &newHeight);
	oldWidth = newWidth;
	oldHeight = newHeight;
	if (newWidth != w || newHeight != h)
	{
		float scaleX = ((float)newWidth) / ((float)image.GetWidth());
		double scaleY = ((float)newHeight) / ((float)image.GetHeight());
		if (scaleX < 1.0 || scaleY < 1.0)
		{
			double scale = wxMin(scaleX, scaleY);
			newWidth = (int)(scale * image.GetWidth());
			newHeight = (int)(scale * image.GetHeight());
			resized = wxBitmap(image.Scale(newWidth, newHeight, wxIMAGE_QUALITY_HIGH));
			w = newWidth;
			h = newHeight;
		}
		else
		{
			newWidth = image.GetWidth();
			newHeight = image.GetHeight();
			resized = wxBitmap(image, wxIMAGE_QUALITY_NORMAL);
		}
		dc.DrawBitmap(resized, (oldWidth - newWidth) / 2, (oldHeight - newHeight) / 2, false);
	}
}

void wxImagePanel::OnSize(wxSizeEvent& event) {
	Refresh();
	event.Skip();
}

void wxImagePanel::MouseWheel(wxMouseEvent& event) {
	event.Skip();
}

void wxImagePanel::mouseDown(wxMouseEvent& event) {
	event.Skip();
}
