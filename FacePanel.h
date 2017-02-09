#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_io.h>

#include "Face.h"
#include "FaceNameDlg.h"
#include "sqlite3.h"

class wxFacePanel : public wxPanel
{
	wxBitmap resized;
	int w, h;
	int XCoord = 0;
	int YCoord = 0;
	double scale = 1.0;
public:
	wxFacePanel(wxWindow* parent);
	void SetImage(wxImage origimage);
	void paintEvent(wxPaintEvent & evt);
	void paintNow();
	void OnSize(wxSizeEvent& event);
	void MouseWheel(wxMouseEvent& event);
	void render(wxDC& dc);
	void mouseDown(wxMouseEvent& event);
	wxImage image;
	wxString hash;
	std::vector<Face> faces;

	void ResetFaces();
		
	DECLARE_EVENT_TABLE()
};