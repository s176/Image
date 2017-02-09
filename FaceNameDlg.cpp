#include "FacenameDlg.h"

FacenameDialog::FacenameDialog(wxWindow *parent, wxImage &image, std::string &old_name)
	: wxDialog(NULL, -1, "Set person's name", wxDefaultPosition, wxSize(350, 400))
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	m_bitmap = new wxStaticBitmap(m_panel, wxID_ANY, wxBitmap(image.Scale(220, 220, wxIMAGE_QUALITY_NORMAL)), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_bitmap, 1, wxALL | wxEXPAND, 5);

	m_textCtrl = new wxTextCtrl(m_panel, wxID_ANY, old_name, wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_textCtrl, 0, wxALL | wxEXPAND, 20);

	m_sdbSizer = new wxStdDialogButtonSizer();
	m_OK = new wxButton(m_panel, wxID_OK);
	m_OK->SetDefault();
	m_sdbSizer->AddButton(m_OK);
	m_Cancel = new wxButton(m_panel, wxID_CANCEL);
	m_sdbSizer->AddButton(m_Cancel);
	m_sdbSizer->Realize();

	bSizer2->Add(m_sdbSizer, 0, wxALL | wxEXPAND, 5);

	m_panel->SetSizer(bSizer2);
	m_panel->Layout();
	bSizer2->Fit(m_panel);
	bSizer1->Add(m_panel, 1, wxEXPAND | wxALL, 5);


	SetSizer(bSizer1);
	Layout();

	Centre(wxBOTH);

}
