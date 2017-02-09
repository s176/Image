#include "ProcessDlg.h"

BEGIN_EVENT_TABLE(ProcessDialog, wxDialog)
EVT_CHECKBOX(ID_THUMB, ProcessDialog::OnThumb)
EVT_CHECKBOX(ID_NOISE, ProcessDialog::OnNoise)
EVT_CHECKBOX(ID_BRIGHT, ProcessDialog::OnBright)
EVT_CHECKBOX(ID_GAMMA, ProcessDialog::OnGamma)
EVT_CHECKBOX(ID_CONTRAST, ProcessDialog::OnContrast)
EVT_CHECKBOX(ID_SAT, ProcessDialog::OnSat)
EVT_CHECKBOX(ID_PIXEL, ProcessDialog::OnPixel)
EVT_CHECKBOX(ID_MEDIAN, ProcessDialog::OnMedian)
END_EVENT_TABLE()


ProcessDialog::ProcessDialog(wxWindow *parent)
	: wxDialog(NULL, -1, "Process images", wxDefaultPosition, wxSize(240, 500))
{
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	m_panel2 = new wxScrolledWindow(this, ID_IMAGE, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
	m_panel2->SetAutoLayout(true);
	m_panel2->SetScrollRate(5, 5);

	wxBoxSizer* bSizer4 = new wxBoxSizer(wxVERTICAL);

	
	m_checkBox24 = new wxCheckBox(m_panel2, ID_THUMB, wxT("Just extract JPEG"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox24->SetToolTip("if checked camera JPEG images are extracted");
	bSizer4->Add(m_checkBox24, 0, wxALL, 5);

	wxStaticLine * m_staticline1 = new wxStaticLine(m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer4->Add(m_staticline1, 0, wxEXPAND | wxALL, 5);

	m_checkBox13 = new wxCheckBox(m_panel2, ID_HALF, wxT("Half-size color image"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox13->SetToolTip("-h Twice as fast as -q 0");
	bSizer4->Add(m_checkBox13, 0, wxALL, 5);
	m_checkBox13->SetValue(true);

	m_checkBox1 = new wxCheckBox(m_panel2, ID_CAMWB, wxT("Camera white balance"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox1->SetToolTip("-w Use the white balance specified by the camera");
	bSizer4->Add(m_checkBox1, 0, wxALL, 5);
	m_checkBox1->SetValue(true);

	m_checkBox2 = new wxCheckBox(m_panel2, ID_AUTOWB, wxT("Auto white balance"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox2->SetToolTip("-a Calculate the white balance by averaging the entire image");
	bSizer4->Add(m_checkBox2, 0, wxALL, 5);

	m_checkBox7 = new wxCheckBox(m_panel2, ID_NOISE, wxT("Denoising "), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox7->SetToolTip("-n Use wavelets to erase noise while preserving real detail");
	spinctrl3 = new wxSpinCtrl(m_panel2, ID_NOISE1, "200", wxDefaultPosition, wxSize(65, -1), wxSP_ARROW_KEYS, 0, 10000, 200);
	spinctrl3->SetToolTip("noise_threshold 100...1000");

	spinctrl3->Enable(false);

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxHORIZONTAL);
	bSizer9->Add(m_checkBox7, 0, wxALL, 5);
	bSizer9->Add(spinctrl3, 0, wxALL, 5);

	bSizer4->Add(bSizer9, 0, wxALL, 0);

	m_checkBox11 = new wxCheckBox(m_panel2, ID_BRIGHT, wxT("Brightness"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox11->SetToolTip("-b Divide the white level by this number");
	spinctrldbl6 = new wxSpinCtrlDouble(m_panel2, ID_BRIGHT1, "1.2", wxDefaultPosition, wxSize(65, -1), wxSP_ARROW_KEYS, 0, 50.0, 1.2, 0.1);
	spinctrldbl6->SetToolTip("brightness 1.0 by default");

	spinctrldbl6->Enable(false);

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer(wxHORIZONTAL);
	bSizer12->Add(m_checkBox11, 0, wxALL, 5);
	bSizer12->Add(spinctrldbl6, 0, wxALL, 5);

	bSizer4->Add(bSizer12, 0, wxALL, 0);

	m_checkBox14 = new wxCheckBox(m_panel2, ID_GAMMA, wxT("Gamma"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox14->SetToolTip("-g Set the gamma curve");

	spinctrldbl7 = new wxSpinCtrlDouble(m_panel2, ID_GAMMA1, "0.3", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 10.0, 0.45, 0.1);
	spinctrldbl8 = new wxSpinCtrlDouble(m_panel2, ID_GAMMA2, "3.0", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 15.0, 4.5, 0.1);

	spinctrldbl7->SetToolTip("Pow 0.45 by default");
	spinctrldbl8->SetToolTip("Toe slope 4.5 by default");

	spinctrldbl7->Enable(false);
	spinctrldbl8->Enable(false);

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer(wxHORIZONTAL);
	bSizer14->Add(m_checkBox14, 0, wxALL, 5);
	bSizer14->Add(spinctrldbl7, 0, wxALL, 5);
	bSizer14->Add(spinctrldbl8, 0, wxALL, 5);

	bSizer4->Add(bSizer14, 0, wxALL, 0);

	wxStaticLine * m_staticline2 = new wxStaticLine(m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer4->Add(m_staticline2, 0, wxEXPAND | wxALL, 5);

	m_checkBox15 = new wxCheckBox(m_panel2, ID_CONTRAST, wxT("Contrast"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox15->SetToolTip("HSV-value curve");

	spinctrldbl9 = new wxSpinCtrlDouble(m_panel2, ID_CONTRAST1, "0.45", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 1.0, 0.45, 0.01);
	spinctrldbl10 = new wxSpinCtrlDouble(m_panel2, ID_CONTRAST2, "2.5", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0.1, 10.0, 2.5, 0.1);

	spinctrldbl9->SetToolTip("Curve point 0...1");
	spinctrldbl10->SetToolTip("Curve intensity (slope) 0.1...10");

	spinctrldbl9->Enable(false);
	spinctrldbl10->Enable(false);

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer(wxHORIZONTAL);
	bSizer15->Add(m_checkBox15, 0, wxALL, 5);
	bSizer15->Add(spinctrldbl9, 0, wxALL, 5);
	bSizer15->Add(spinctrldbl10, 0, wxALL, 5);

	bSizer4->Add(bSizer15, 0, wxALL, 0);

	m_checkBox16 = new wxCheckBox(m_panel2, ID_SAT, wxT("Saturate "), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox16->SetToolTip("HSV-saturation curve");

	spinctrldbl11 = new wxSpinCtrlDouble(m_panel2, ID_SAT1, "0.3", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 1.0, 0.3, 0.01);
	spinctrldbl12 = new wxSpinCtrlDouble(m_panel2, ID_SAT2, "2.0", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0.1, 10.0, 2, 0.1);

	spinctrldbl11->SetToolTip("Curve point 0...1");
	spinctrldbl12->SetToolTip("Curve intensity (slope) 0.1...10");

	spinctrldbl11->Enable(false);
	spinctrldbl12->Enable(false);

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer(wxHORIZONTAL);
	bSizer16->Add(m_checkBox16, 0, wxALL, 5);
	bSizer16->Add(spinctrldbl11, 0, wxALL, 5);
	bSizer16->Add(spinctrldbl12, 0, wxALL, 5);

	bSizer4->Add(bSizer16, 0, wxALL, 0);
	
	m_checkBox20 = new wxCheckBox(m_panel2, ID_PIXEL, wxT("Pixels      "), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox20->SetToolTip("RGB 3X3 average filter.\nReduce bad pixels of RGB-noise");

	spinctrldbl19 = new wxSpinCtrlDouble(m_panel2, ID_PIXEL1, "1.5", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 3.0, 1.5, 0.1);
	spinctrldbl19->SetToolTip("Standard deviation threshold 0...3 \n0 - all pixels are averaged\n3 - some abnormal pixels are averaged");

	spinctrldbl19->Enable(false);

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer(wxHORIZONTAL);
	bSizer20->Add(m_checkBox20, 0, wxALL, 5);
	bSizer20->Add(spinctrldbl19, 0, wxALL, 5);

	bSizer4->Add(bSizer20, 0, wxALL, 0);

	m_checkBox21 = new wxCheckBox(m_panel2, ID_MEDIAN, wxT("Smooth  "), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox21->SetToolTip("Denoise 5X5 filter by local contrast");

	spinctrldbl20 = new wxSpinCtrlDouble(m_panel2, ID_MEDIAN1, "4.0", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 10.0, 4.0, 0.1);
	spinctrldbl20->SetToolTip("Standard deviation threshold 0...10 \n0 - all pixels are smoothed\n10 - some contrast pixels are smoothed");

	m_checkBox22 = new wxCheckBox(m_panel2, ID_MASK, wxT("Mask"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox22->SetToolTip("Show low contrast mask");

	spinctrldbl20->Enable(false);
	m_checkBox22->Enable(false);

	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer(wxHORIZONTAL);
	bSizer21->Add(m_checkBox21, 0, wxALL, 5);
	bSizer21->Add(spinctrldbl20, 0, wxALL, 5);
	bSizer21->Add(m_checkBox22, 0, wxALL, 5);

	bSizer4->Add(bSizer21, 0, wxALL, 0);
	
	wxStaticLine * m_staticline3 = new wxStaticLine(m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer4->Add(m_staticline3, 0, wxEXPAND | wxALL, 5);

	m_checkBox23 = new wxCheckBox(m_panel2, ID_TIFF, wxT("Save as TIFF"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox23->SetToolTip("if checked images are saved in TIFF, else in JPEG");
	bSizer4->Add(m_checkBox23, 0, wxALL, 5);
	
	wxStaticLine * m_staticline4 = new wxStaticLine(m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer4->Add(m_staticline4, 0, wxEXPAND | wxALL, 5);

	wxStdDialogButtonSizer* m_sdbSizer = new wxStdDialogButtonSizer();
	m_OK = new wxButton(m_panel2, wxID_OK);
	m_OK->SetDefault();
	m_sdbSizer->AddButton(m_OK);
	m_Cancel = new wxButton(m_panel2, wxID_CANCEL);
	m_sdbSizer->AddButton(m_Cancel);
	m_sdbSizer->Realize();

	bSizer4->Add(m_sdbSizer, 0, wxALL | wxEXPAND, 5);

	m_panel2->SetSizer(bSizer4);
	m_panel2->Layout();
	bSizer4->Fit(m_panel2);
	bSizer2->Add(m_panel2, 1, wxEXPAND | wxALL, 5);
	
	SetSizer(bSizer2);
	Layout();

	Centre(wxBOTH);
}

void ProcessDialog::OnThumb(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		m_checkBox13->Enable(false);
		m_checkBox1->Enable(false);
		m_checkBox2->Enable(false);
		m_checkBox7->Enable(false);
		m_checkBox11->Enable(false);
		m_checkBox14->Enable(false);
		m_checkBox15->Enable(false);
		m_checkBox16->Enable(false);
		m_checkBox20->Enable(false);
		m_checkBox21->Enable(false);
		m_checkBox22->Enable(false);
		m_checkBox23->Enable(false);
	}
	else
	{
		m_checkBox13->Enable(true);
		m_checkBox1->Enable(true);
		m_checkBox2->Enable(true);
		m_checkBox7->Enable(true);
		m_checkBox11->Enable(true);
		m_checkBox14->Enable(true);
		m_checkBox15->Enable(true);
		m_checkBox16->Enable(true);
		m_checkBox20->Enable(true);
		m_checkBox21->Enable(true);
		m_checkBox22->Enable(true);
		m_checkBox23->Enable(true);
	}
}

void ProcessDialog::OnNoise(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		spinctrl3->Enable(true);
	}
	else
	{
		spinctrl3->Enable(false);
	}
}

void ProcessDialog::OnBright(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		spinctrldbl6->Enable(true);
	}
	else
	{
		spinctrldbl6->Enable(false);
	}
}


void ProcessDialog::OnGamma(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		spinctrldbl7->Enable(true);
		spinctrldbl8->Enable(true);
	}
	else
	{
		spinctrldbl7->Enable(false);
		spinctrldbl8->Enable(false);
	}
}

void ProcessDialog::OnContrast(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		spinctrldbl9->Enable(true);
		spinctrldbl10->Enable(true);
	}
	else
	{
		spinctrldbl9->Enable(false);
		spinctrldbl10->Enable(false);
	}
}

void ProcessDialog::OnSat(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		spinctrldbl11->Enable(true);
		spinctrldbl12->Enable(true);
	}
	else
	{
		spinctrldbl11->Enable(false);
		spinctrldbl12->Enable(false);
	}
}
void ProcessDialog::OnPixel(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		spinctrldbl19->Enable(true);
	}
	else
	{
		spinctrldbl19->Enable(false);
	}
}

void ProcessDialog::OnMedian(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		spinctrldbl20->Enable(true);
		m_checkBox22->Enable(true);
	}
	else
	{
		spinctrldbl20->Enable(false);
		m_checkBox22->Enable(false);
	}
}