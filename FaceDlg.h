#pragma once
#include "wx/wx.h"
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include "wx/artprov.h"
#include "FacePanel.h"
#include "wx/spinctrl.h"
#include <math.h>
#include <algorithm>

#include "Face.h"

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_io.h>
#include "sqlite3.h"


class FaceDlg : public wxFrame
{
	enum
	{
		ID_IMAGE,
	};

public:
	FaceDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);

	wxString filename;
	wxString hash;
	std::vector<Face> faces;
	wxFacePanel* drawPane;
	
	void SetImage();
};
