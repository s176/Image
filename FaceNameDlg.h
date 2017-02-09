#pragma once
#include "wx/wx.h"
#include <wx/dialog.h>
#include <wx/statline.h>

class FacenameDialog : public wxDialog
{
	
public:
	FacenameDialog(wxWindow *parent, wxImage &image, std::string &old_name);

	wxPanel* m_panel;
	wxStaticBitmap* m_bitmap;
	wxBitmap m_image;
	wxTextCtrl* m_textCtrl;
	wxStdDialogButtonSizer* m_sdbSizer;
	wxButton* m_OK;
	wxButton* m_Cancel;	
};