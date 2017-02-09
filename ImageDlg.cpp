#include "libraw/libraw.h"
#include <wx/mstream.h>
#include "wx/filename.h"
#include "ImageDlg.h"

BEGIN_EVENT_TABLE(ImageDlg, wxFrame)
EVT_MENU(ID_RELOAD, ImageDlg::OnReload)
EVT_MENU(ID_THUMBNAIL, ImageDlg::OnThumbnail)
EVT_MENU(ID_SAVE, ImageDlg::OnSave)
EVT_CHECKBOX(ID_CUSTOMWB, ImageDlg::OnCustomWB)
EVT_CHECKBOX(ID_ABER, ImageDlg::OnAber)
EVT_CHECKBOX(ID_BLACK, ImageDlg::OnBlack)
EVT_CHECKBOX(ID_SATURATION, ImageDlg::OnSaturation)
EVT_CHECKBOX(ID_NOISE, ImageDlg::OnNoise)
EVT_CHECKBOX(ID_HIGHLIGHT, ImageDlg::OnHighlight)
EVT_CHECKBOX(ID_FLIP, ImageDlg::OnFlip)
EVT_CHECKBOX(ID_BRIGHT, ImageDlg::OnBright)
EVT_CHECKBOX(ID_GAMMA, ImageDlg::OnGamma)
EVT_CHECKBOX(ID_CONTRAST, ImageDlg::OnContrast)
EVT_CHECKBOX(ID_SAT, ImageDlg::OnSat)
EVT_CHECKBOX(ID_RED, ImageDlg::OnRed)
EVT_CHECKBOX(ID_GREEN, ImageDlg::OnGreen)
EVT_CHECKBOX(ID_BLUE, ImageDlg::OnBlue)
EVT_CHECKBOX(ID_PIXEL, ImageDlg::OnPixel)
EVT_CHECKBOX(ID_MEDIAN, ImageDlg::OnMedian)

EVT_MOUSEWHEEL(ImageDlg::mouseWheelMoved)
EVT_BUTTON(ID_HIDEBUTTON, ImageDlg::OnHideButton)
EVT_LEFT_DOWN(ImageDlg::OnMouse)
END_EVENT_TABLE()

ImageDlg::ImageDlg(wxWindow * parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style)
{

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	m_panel2 = new wxPanel(this, ID_IMAGE, wxDefaultPosition, wxSize(800, 600), wxTAB_TRAVERSAL);

	bSizer3 = new wxBoxSizer(wxHORIZONTAL);

	drawPane = new wxImagePanel(this);
	drawPane->SetBackgroundColour(*wxBLACK);

	bSizer3->Add(drawPane, 1, wxEXPAND | wxALL);

	m_panel31 = new wxPanel(m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer(wxVERTICAL);
	bSizer56->Add(m_panel31, 1, wxEXPAND | wxALL);


	m_panel3 = new wxScrolledWindow(m_panel2, wxID_ANY, wxDefaultPosition, wxSize(220, -1), wxVSCROLL);
	m_panel3->SetScrollRate(5, 5);
	
	wxBoxSizer* bSizer4 = new wxBoxSizer(wxVERTICAL);

	m_panel4 = new wxPanel(m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer(wxVERTICAL);
	button = new wxButton(m_panel4, ID_HIDEBUTTON, ">", wxDefaultPosition, wxSize(20, 20), 0);
	bSizer55->Add(button, 1, wxEXPAND | wxALL);


	itemToolBar = new wxToolBar(m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT | wxTB_HORIZONTAL | wxTB_TEXT | wxNO_BORDER);
	wxBitmap itemtool1Bitmap1 = wxArtProvider::GetBitmap(wxART_REDO, wxART_OTHER, wxSize(16, 16));
	itemToolBar->AddTool(ID_RELOAD, "Process", itemtool1Bitmap1, wxNullBitmap, wxITEM_NORMAL, wxT("Process image using options"), wxT("Process image using options"));
	wxBitmap itemtool1Bitmap2 = wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_OTHER, wxSize(16, 16));
	itemToolBar->AddTool(ID_THUMBNAIL, "Thumbnail", itemtool1Bitmap2, wxNullBitmap, wxITEM_CHECK, wxT("Extract the camera-generated thumbnail"), wxT("Extract the camera-generated thumbnail"));
	wxBitmap itemtool1Bitmap4 = wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_OTHER, wxSize(16, 16));
	itemToolBar->AddTool(ID_SAVE, "Save as", itemtool1Bitmap4, wxNullBitmap, wxITEM_NORMAL, wxT("Save image to file as..."), wxT("Save image to file as..."));

	itemToolBar->Realize();
	bSizer4->Add(itemToolBar, 0, wxGROW | wxALL, 0);
	
	wxStaticLine * m_staticline1 = new wxStaticLine(m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer4->Add(m_staticline1, 0, wxEXPAND | wxALL, 5);

	m_checkBox13 = new wxCheckBox(m_panel3, ID_HALF, wxT("Half-size color image"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox13->SetToolTip("-h Twice as fast as -q 0");
	bSizer4->Add(m_checkBox13, 0, wxALL, 5);
	m_checkBox13->SetValue(true);

	m_checkBox1 = new wxCheckBox(m_panel3, ID_CAMWB, wxT("Camera white balance"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox1->SetToolTip("-w Use the white balance specified by the camera");
	bSizer4->Add(m_checkBox1, 0, wxALL, 5);
	m_checkBox1->SetValue(true);

	m_checkBox2 = new wxCheckBox(m_panel3, ID_AUTOWB, wxT("Auto white balance"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox2->SetToolTip("-a Calculate the white balance by averaging the entire image");
	bSizer4->Add(m_checkBox2, 0, wxALL, 5);

	m_checkBox3 = new wxCheckBox(m_panel3, ID_CUSTOMWB, wxT("Custom white balance"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox3->SetToolTip("-r Specify your own raw white balance");
	bSizer4->Add(m_checkBox3, 0, wxALL, 5);

	spinctrldbl1 = new wxSpinCtrlDouble(m_panel3, ID_CUSTOMWB1, "1.4", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 3.0, 1.4, 0.01);
	spinctrldbl2 = new wxSpinCtrlDouble(m_panel3, ID_CUSTOMWB2, "1.0", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 3.0, 1.0, 0.01);
	spinctrldbl3 = new wxSpinCtrlDouble(m_panel3, ID_CUSTOMWB3, "2.0", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 3.0, 2.0, 0.01);

	spinctrldbl1->SetToolTip("multiplier0 Red");
	spinctrldbl2->SetToolTip("multiplier1 Green");
	spinctrldbl3->SetToolTip("multiplier2 Blue");

	spinctrldbl1->Enable(false);
	spinctrldbl2->Enable(false);
	spinctrldbl3->Enable(false);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxHORIZONTAL);

	bSizer5->Add(spinctrldbl1, 0, wxALL, 5);
	bSizer5->Add(spinctrldbl2, 0, wxALL, 5);
	bSizer5->Add(spinctrldbl3, 0, wxALL, 5);

	bSizer4->Add(bSizer5, 0, wxALL, 0);

	m_checkBox4 = new wxCheckBox(m_panel3, ID_ABER, wxT("Correct chromatic aberration"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox4->SetToolTip("-C Enlarge the raw red and blue layers by the given factors, \ntypically 0.999 to 1.001, to correct chromatic aberration");
	bSizer4->Add(m_checkBox4, 0, wxALL, 5);

	spinctrldbl4 = new wxSpinCtrlDouble(m_panel3, ID_ABER1, "0.999", wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 0, 2.0, 0.999, 0.001);
	spinctrldbl5 = new wxSpinCtrlDouble(m_panel3, ID_ABER2, "1.001", wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 0, 2.0, 1.001, 0.001);

	spinctrldbl4->SetToolTip("red_mag");
	spinctrldbl5->SetToolTip("blue_mag");

	spinctrldbl4->Enable(false);
	spinctrldbl5->Enable(false);

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxHORIZONTAL);

	bSizer6->Add(spinctrldbl4, 0, wxALL, 5);
	bSizer6->Add(spinctrldbl5, 0, wxALL, 5);

	bSizer4->Add(bSizer6, 0, wxALL, 0);

	m_checkBox5 = new wxCheckBox(m_panel3, ID_BLACK, wxT("Darkness   "), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox5->SetToolTip("-k When shadows appear foggy, you need to raise the darkness level.\nThe default darkness is usually correct");

	spinctrl1 = new wxSpinCtrl(m_panel3, ID_BLACK1, "0", wxDefaultPosition, wxSize(65, -1), wxSP_ARROW_KEYS, 0, 5000, 0);
	spinctrl1->SetToolTip("darkness 0...5000");
	spinctrl1->Enable(false);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxHORIZONTAL);
	bSizer7->Add(m_checkBox5, 0, wxALL, 5);
	bSizer7->Add(spinctrl1, 0, wxALL, 5);

	bSizer4->Add(bSizer7, 0, wxALL, 0);

	m_checkBox6 = new wxCheckBox(m_panel3, ID_SATURATION, wxT("Saturation "), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox6->SetToolTip("-S When highlights appear pink, you need to lower the saturation level.\nThe default saturation is usually correct");
	spinctrl2 = new wxSpinCtrl(m_panel3, ID_SATURATION1, "0", wxDefaultPosition, wxSize(65, -1), wxSP_ARROW_KEYS, 0, 20000, 0);
	spinctrl2->SetToolTip("saturation 0...20000");

	spinctrl2->Enable(false);

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer(wxHORIZONTAL);
	bSizer8->Add(m_checkBox6, 0, wxALL, 5);
	bSizer8->Add(spinctrl2, 0, wxALL, 5);

	bSizer4->Add(bSizer8, 0, wxALL, 0);

	m_checkBox7 = new wxCheckBox(m_panel3, ID_NOISE, wxT("Denoising "), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox7->SetToolTip("-n Use wavelets to erase noise while preserving real detail");
	spinctrl3 = new wxSpinCtrl(m_panel3, ID_NOISE1, "200", wxDefaultPosition, wxSize(65, -1), wxSP_ARROW_KEYS, 0, 10000, 200);
	spinctrl3->SetToolTip("noise_threshold 100...1000");

	spinctrl3->Enable(false);

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxHORIZONTAL);
	bSizer9->Add(m_checkBox7, 0, wxALL, 5);
	bSizer9->Add(spinctrl3, 0, wxALL, 5);

	bSizer4->Add(bSizer9, 0, wxALL, 0);

	m_checkBox8 = new wxCheckBox(m_panel3, ID_HIGHLIGHT, wxT("Highlight  "), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox8->SetToolTip("-H highlight");
	spinctrl4 = new wxSpinCtrl(m_panel3, ID_HIGHLIGHT1, "5", wxDefaultPosition, wxSize(65, -1), wxSP_ARROW_KEYS, 0, 10, 5);
	spinctrl4->SetToolTip("-H 0 Clip all highlights to solid white(default)\n-H 1 Leave highlights unclipped in various shades of pink\n-H 2 Blend clipped and unclipped values together for a gradual fade to white\n-H 3+ Reconstruct highlights. Low numbers favor whites; high numbers favor colors");
	spinctrl4->Enable(false);

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer(wxHORIZONTAL);
	bSizer10->Add(m_checkBox8, 0, wxALL, 5);
	bSizer10->Add(spinctrl4, 0, wxALL, 5);

	bSizer4->Add(bSizer10, 0, wxALL, 0);

	m_checkBox9 = new wxCheckBox(m_panel3, ID_FLIP, wxT("Flip            "), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox9->SetToolTip("-t Flip the output image. By default, dcraw applies the flip specified by the camera");

	spinctrl5 = new wxSpinCtrl(m_panel3, ID_FLIP1, "0", wxDefaultPosition, wxSize(65, -1), wxSP_ARROW_KEYS, 0, 360, 0);
	spinctrl5->SetToolTip("0-7, 90, 180, 270\n0 disables all flipping");

	spinctrl5->Enable(false);

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer(wxHORIZONTAL);
	bSizer11->Add(m_checkBox9, 0, wxALL, 5);
	bSizer11->Add(spinctrl5, 0, wxALL, 5);

	bSizer4->Add(bSizer11, 0, wxALL, 0);

	m_checkBox11 = new wxCheckBox(m_panel3, ID_BRIGHT, wxT("Brightness"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox11->SetToolTip("-b Divide the white level by this number");
	spinctrldbl6 = new wxSpinCtrlDouble(m_panel3, ID_BRIGHT1, "1.2", wxDefaultPosition, wxSize(65, -1), wxSP_ARROW_KEYS, 0, 50.0, 1.2, 0.1);
	spinctrldbl6->SetToolTip("brightness 1.0 by default");

	spinctrldbl6->Enable(false);

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer(wxHORIZONTAL);
	bSizer12->Add(m_checkBox11, 0, wxALL, 5);
	bSizer12->Add(spinctrldbl6, 0, wxALL, 5);

	bSizer4->Add(bSizer12, 0, wxALL, 0);
	
	m_checkBox14 = new wxCheckBox(m_panel3, ID_GAMMA, wxT("Gamma"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox14->SetToolTip("-g Set the gamma curve");

	spinctrldbl7 = new wxSpinCtrlDouble(m_panel3, ID_GAMMA1, "0.3", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 10.0, 0.45, 0.1);
	spinctrldbl8 = new wxSpinCtrlDouble(m_panel3, ID_GAMMA2, "3.0", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 15.0, 4.5, 0.1);

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

	wxStaticLine * m_staticline2 = new wxStaticLine(m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer4->Add(m_staticline2, 0, wxEXPAND | wxALL, 5);

	m_checkBox15 = new wxCheckBox(m_panel3, ID_CONTRAST, wxT("Contrast"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox15->SetToolTip("HSV-value curve");

	spinctrldbl9 = new wxSpinCtrlDouble(m_panel3, ID_CONTRAST1, "0.45", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 1.0, 0.45, 0.01);
	spinctrldbl10 = new wxSpinCtrlDouble(m_panel3, ID_CONTRAST2, "2.5", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0.1, 10.0, 2.5, 0.1);

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

	m_checkBox16 = new wxCheckBox(m_panel3, ID_SAT, wxT("Saturate "), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox16->SetToolTip("HSV-saturation curve");

	spinctrldbl11 = new wxSpinCtrlDouble(m_panel3, ID_SAT1, "0.3", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 1.0, 0.3, 0.01);
	spinctrldbl12 = new wxSpinCtrlDouble(m_panel3, ID_SAT2, "2.0", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0.1, 10.0, 2, 0.1);

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

	m_checkBox17 = new wxCheckBox(m_panel3, ID_RED, wxT("Red         "), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox17->SetToolTip("Colorize by red-value curve");

	spinctrldbl13 = new wxSpinCtrlDouble(m_panel3, ID_RED1, "0.3", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 1.0, 0.3, 0.01);
	spinctrldbl14 = new wxSpinCtrlDouble(m_panel3, ID_RED2, "2.0", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0.1, 10.0, 2, 0.1);

	spinctrldbl13->SetToolTip("Curve point 0...1 \n 0 - increase \n 1 - decrease");
	spinctrldbl14->SetToolTip("Curve intensity (slope) 0.1...10");

	spinctrldbl13->Enable(false);
	spinctrldbl14->Enable(false);

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer(wxHORIZONTAL);
	bSizer17->Add(m_checkBox17, 0, wxALL, 5);
	bSizer17->Add(spinctrldbl13, 0, wxALL, 5);
	bSizer17->Add(spinctrldbl14, 0, wxALL, 5);

	bSizer4->Add(bSizer17, 0, wxALL, 0);

	m_checkBox18 = new wxCheckBox(m_panel3, ID_GREEN, wxT("Green     "), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox18->SetToolTip("Colorize by green-value curve");

	spinctrldbl15 = new wxSpinCtrlDouble(m_panel3, ID_GREEN1, "0.3", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 1.0, 0.3, 0.01);
	spinctrldbl16 = new wxSpinCtrlDouble(m_panel3, ID_GREEN2, "2.0", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0.1, 10.0, 2, 0.1);

	spinctrldbl15->SetToolTip("Curve point 0...1 \n 0 - increase \n 1 - decrease");
	spinctrldbl16->SetToolTip("Curve intensity (slope) 0.1...10");

	spinctrldbl15->Enable(false);
	spinctrldbl16->Enable(false);

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer(wxHORIZONTAL);
	bSizer18->Add(m_checkBox18, 0, wxALL, 5);
	bSizer18->Add(spinctrldbl15, 0, wxALL, 5);
	bSizer18->Add(spinctrldbl16, 0, wxALL, 5);

	bSizer4->Add(bSizer18, 0, wxALL, 0);

	m_checkBox19 = new wxCheckBox(m_panel3, ID_BLUE, wxT("Blue        "), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox19->SetToolTip("Colorize by blue-value curve");

	spinctrldbl17 = new wxSpinCtrlDouble(m_panel3, ID_BLUE1, "0.3", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 1.0, 0.3, 0.01);
	spinctrldbl18 = new wxSpinCtrlDouble(m_panel3, ID_BLUE2, "2.0", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0.1, 10.0, 2, 0.1);

	spinctrldbl17->SetToolTip("Curve point 0...1 \n 0 - increase \n 1 - decrease");
	spinctrldbl18->SetToolTip("Curve intensity (slope) 0.1...10");

	spinctrldbl17->Enable(false);
	spinctrldbl18->Enable(false);

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer(wxHORIZONTAL);
	bSizer19->Add(m_checkBox19, 0, wxALL, 5);
	bSizer19->Add(spinctrldbl17, 0, wxALL, 5);
	bSizer19->Add(spinctrldbl18, 0, wxALL, 5);

	bSizer4->Add(bSizer19, 0, wxALL, 0);

	m_checkBox20 = new wxCheckBox(m_panel3, ID_PIXEL, wxT("Pixels      "), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox20->SetToolTip("RGB 3X3 average filter.\nReduce bad pixels of RGB-noise");

	spinctrldbl19 = new wxSpinCtrlDouble(m_panel3, ID_PIXEL1, "1.5", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 3.0, 1.5, 0.1);
	spinctrldbl19->SetToolTip("Standard deviation threshold 0...3 \n0 - all pixels are averaged\n3 - some abnormal pixels are averaged");

	spinctrldbl19->Enable(false);

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer(wxHORIZONTAL);
	bSizer20->Add(m_checkBox20, 0, wxALL, 5);
	bSizer20->Add(spinctrldbl19, 0, wxALL, 5);

	bSizer4->Add(bSizer20, 0, wxALL, 0);

	m_checkBox21 = new wxCheckBox(m_panel3, ID_MEDIAN, wxT("Smooth  "), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox21->SetToolTip("Denoise 5X5 filter by local contrast");

	spinctrldbl20 = new wxSpinCtrlDouble(m_panel3, ID_MEDIAN1, "4.0", wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 10.0, 4.0, 0.1);
	spinctrldbl20->SetToolTip("Standard deviation threshold 0...10 \n0 - all pixels are smoothed\n10 - some contrast pixels are smoothed");

	m_checkBox22 = new wxCheckBox(m_panel3, ID_MASK, wxT("Mask"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBox22->SetToolTip("Show low contrast mask");

	spinctrldbl20->Enable(false);
	m_checkBox22->Enable(false);

	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer(wxHORIZONTAL);
	bSizer21->Add(m_checkBox21, 0, wxALL, 5);
	bSizer21->Add(spinctrldbl20, 0, wxALL, 5);
	bSizer21->Add(m_checkBox22, 0, wxALL, 5);

	bSizer4->Add(bSizer21, 0, wxALL, 0);
	m_panel4->SetSizer(bSizer55);
	m_panel4->Layout();
	bSizer55->Fit(m_panel4);
	
	bSizer3->Add(m_panel4, 0, wxEXPAND, 0);
	
	m_panel3->SetSizer(bSizer4);
	
	bSizer4->Fit(m_panel3);
	
	bSizer3->Add(m_panel3, 0, wxEXPAND | wxALL, 0);
	m_panel3->Layout();
	
	m_panel2->SetSizer(bSizer3);
	m_panel2->Layout();
	
	bSizer3->Fit(m_panel2);
	bSizer2->Add(m_panel2, 1, wxEXPAND | wxALL, 0);

	SetSizer(bSizer2);
	
	Centre(wxBOTH);
}


void ImageDlg::OnHideButton(wxCommandEvent& event)
{
	if (bSizer3->IsShown(m_panel3))
	{
		button->SetLabelText("<");
		bSizer3->Hide(m_panel3);
		bSizer3->Layout();
		
	}
	else
	{
		button->SetLabelText(">");
		bSizer3->Show(m_panel3);
		bSizer3->Layout();
	}
	
}

void ImageDlg::SetImage()
{
	wxImage image2;
	if (isRaw)
	{
		wxBusyCursor busy;
		LibRaw iProcessor;
		iProcessor.open_file(filename.char_str());
		iProcessor.unpack();

#define P1  iProcessor.imgdata.idata
#define C   iProcessor.imgdata.color
#define OUT iProcessor.imgdata.params

		OUT.output_tiff = 1;

		if (m_checkBox1->IsChecked())
		{
			OUT.use_camera_wb = 1;
		}
		if (m_checkBox2->IsChecked())
		{
			OUT.use_auto_wb = 1;
		}
		else
		{
			OUT.use_auto_wb = 0;
		}
		if (m_checkBox3->IsChecked())
		{
			OUT.user_mul[0] = spinctrldbl1->GetValue();
			OUT.user_mul[1] = spinctrldbl2->GetValue();
			OUT.user_mul[2] = spinctrldbl3->GetValue();
		}
		if (m_checkBox4->IsChecked())
		{
			OUT.aber[0] = spinctrldbl4->GetValue();
			OUT.aber[2] = spinctrldbl5->GetValue();
		}
		if (m_checkBox5->IsChecked())
		{
			OUT.user_black = spinctrl1->GetValue();
		}
		if (m_checkBox6->IsChecked())
		{
			OUT.user_sat = spinctrl2->GetValue();
		}
		if (m_checkBox7->IsChecked())
		{
			OUT.threshold = spinctrl3->GetValue();
		}
		if (m_checkBox8->IsChecked())
		{
			OUT.highlight = spinctrl4->GetValue();
		}
		if (m_checkBox9->IsChecked())
		{
			OUT.user_flip = spinctrl5->GetValue();
		}
		if (m_checkBox11->IsChecked())
		{
			OUT.bright = spinctrldbl6->GetValue();
		}
		if (m_checkBox13->IsChecked())
		{
			OUT.half_size = 1;
		}
		if (m_checkBox14->IsChecked())
		{
			OUT.gamm[0] = spinctrldbl7->GetValue();
			OUT.gamm[1] = spinctrldbl8->GetValue();
		}
		int check = iProcessor.dcraw_process();
		libraw_processed_image_t *img_ptr = iProcessor.dcraw_make_mem_image(&check);
		wxImage tempimage;
		tempimage.SetData(img_ptr->data, img_ptr->width, img_ptr->height, true);
		image = tempimage.Copy();
		iProcessor.recycle();
		LibRaw::dcraw_clear_mem(img_ptr);
	}
	else
	{
		itemToolBar->EnableTool(ID_THUMBNAIL, false);
		m_checkBox13->Enable(false);
		m_checkBox1->Enable(false);
		m_checkBox2->Enable(false);
		m_checkBox3->Enable(false);
		m_checkBox4->Enable(false);
		m_checkBox5->Enable(false);
		m_checkBox6->Enable(false);
		m_checkBox7->Enable(false);
		m_checkBox8->Enable(false);
		m_checkBox9->Enable(false);
		m_checkBox11->Enable(false);
		m_checkBox14->Enable(false);
		image.LoadFile(filename);
	}
	if (image.IsOk())
	{
		if (m_checkBox15->IsChecked() || m_checkBox16->IsChecked() || m_checkBox17->IsChecked() || m_checkBox18->IsChecked() || m_checkBox19->IsChecked())
		{
			unsigned char *srcBytePtr;
			unsigned char *dstBytePtr;
			unsigned long count;
			wxImage::HSVValue hsv;
			wxImage::RGBValue rgb;

			count = image.GetWidth() * image.GetHeight();
			if (count > 0 && !wxIsNullDouble(0.3))
			{
				srcBytePtr = image.GetData();
				dstBytePtr = srcBytePtr;
				do
				{
					rgb.red = *srcBytePtr++;
					rgb.green = *srcBytePtr++;
					rgb.blue = *srcBytePtr++;
					hsv = wxImage::RGBtoHSV(rgb);

					if (m_checkBox15->IsChecked())
					{
						double min = 1 / (1 + exp(-spinctrldbl10->GetValue() * (0.0 - spinctrldbl9->GetValue())));
						double max = 1 / (1 + exp(-spinctrldbl10->GetValue() * (1.0 - spinctrldbl9->GetValue())));
						double minmax = max - min;
						double value = 1 / (1 + exp(-spinctrldbl10->GetValue() * (hsv.value - spinctrldbl9->GetValue())));
						hsv.value = (value - min) / minmax; 
					}
					
					if (m_checkBox16->IsChecked())
					{
						double min = 1 / (1 + exp(-spinctrldbl12->GetValue() * (0.0 - spinctrldbl11->GetValue())));
						double max = 1 / (1 + exp(-spinctrldbl12->GetValue() * (1.0 - spinctrldbl11->GetValue())));
						double minmax = max - min;
						double sat = 1 / (1 + exp(-spinctrldbl12->GetValue() * (hsv.saturation - spinctrldbl11->GetValue())));
						hsv.saturation = (sat - min) / minmax;
					}
				
					rgb = wxImage::HSVtoRGB(hsv);
				
					if (m_checkBox17->IsChecked())
					{
						double min = 1 / (1 + exp(-spinctrldbl14->GetValue() * (0.0 - spinctrldbl13->GetValue())));
						double max = 1 / (1 + exp(-spinctrldbl14->GetValue() * (1.0 - spinctrldbl13->GetValue())));
						double minmax = max - min;
						double x = (double) rgb.red / 255;
						double sat = 1 / (1 + exp(-spinctrldbl14->GetValue() * (x - spinctrldbl13->GetValue())));
						rgb.red = 255 * (sat - min) / minmax;
					}
				
					if (m_checkBox18->IsChecked())
					{
						double min = 1 / (1 + exp(-spinctrldbl16->GetValue() * (0.0 - spinctrldbl15->GetValue())));
						double max = 1 / (1 + exp(-spinctrldbl16->GetValue() * (1.0 - spinctrldbl15->GetValue())));
						double minmax = max - min;
						double x = (double)rgb.green / 255;
						double sat = 1 / (1 + exp(-spinctrldbl16->GetValue() * (x - spinctrldbl15->GetValue())));
						rgb.green = 255 * (sat - min) / minmax;
					}

					if (m_checkBox19->IsChecked())
					{
						double min = 1 / (1 + exp(-spinctrldbl18->GetValue() * (0.0 - spinctrldbl17->GetValue())));
						double max = 1 / (1 + exp(-spinctrldbl18->GetValue() * (1.0 - spinctrldbl17->GetValue())));
						double minmax = max - min;
						double x = (double)rgb.blue / 255;
						double sat = 1 / (1 + exp(-spinctrldbl18->GetValue() * (x - spinctrldbl17->GetValue())));
						rgb.blue = 255 * (sat - min) / minmax;
					}
					
					*dstBytePtr++ = rgb.red;
					*dstBytePtr++ = rgb.green;
					*dstBytePtr++ = rgb.blue;
				
				} while (--count != 0);
			}
		}

		if (m_checkBox20->IsChecked())
		{
			wxBusyCursor busy;
			image2 = image.Copy();		
			int nHeight = image.GetHeight();
			int nWidth = image.GetWidth();
			int rgb[9][3];
			double ave[3];
			int sum[3];
			double deviation[9];
			double devave = 0;
			int count = 0;
			int rgbcount = 0;
			for (int row = 1; row < nHeight-1; row++)
			{
				for (int col = 1; col < nWidth-1; col++)
				{
					for (int t = 0; t < 3; t++)
					{
						sum[t] = 0;
						ave[t] = 0;
					}
					devave = 0;
					rgbcount = 0;
					
					for (int rowt = -1; rowt < 2; rowt++)
					{
						for (int colt = -1; colt < 2; colt++)
						{
							rgb[rgbcount][0] = image2.GetRed(col + colt, row + rowt);
							rgb[rgbcount][1] = image2.GetGreen(col + colt, row + rowt);
							rgb[rgbcount][2] = image2.GetBlue(col + colt, row + rowt);
							rgbcount++;
						}
					}
					for (int i = 0; i < 9; i++)
					{
						for (int p = 0; p < 3; p++)
						{
							sum[p] += rgb[i][p];
						}
					}
					for (int i = 0; i < 3; i++)
					{
						ave[i] = (double)sum[i] / 9;
					}
					for (int i = 0; i < 9; i++)
					{
						deviation[i] = ((double)rgb[i][0] - ave[0])*((double)rgb[i][0] - ave[0]) + ((double)rgb[i][1] - ave[1])*((double)rgb[i][1] - ave[1]) + ((double)rgb[i][2] - ave[2])*((double)rgb[i][2] - ave[2]);
						devave += deviation[i];
					}
					devave /= 9;
					if (sqrt(deviation[4]) > sqrt(devave) * spinctrldbl19->GetValue())
					{
						image.SetRGB(col, row, (int)ave[0], (int)ave[1], (int)ave[2]);
						count++;
					}
				}
			}
		}
		
		if (m_checkBox21->IsChecked())
		{
			wxBusyCursor busy;
			int blur_k = (int)sqrt(image.GetHeight() * image.GetHeight() + image.GetWidth() * image.GetWidth()) / 800;
			spinctrldbl20->GetValue();
			image2 = image.Blur(blur_k);
			
			int nHeight = image.GetHeight();
			int nWidth = image.GetWidth();

			double ave;
			double sum;
			double deviation[25];
			double devave;
			int hsvcount;
			int count = 0;
			double sat = 0;
			double value = 0;
			wxImage::RGBValue rgb;
			wxImage::HSVValue hsv[25];
			for (int row = 2; row < nHeight - 2; row++)
			{
				for (int col = 2; col < nWidth - 2; col++)
				{
					sum = 0;
					devave = 0;
					ave = 0;				
					hsvcount = 0;
					sat = 0;
					value = 0;
					for (int rowt = -2; rowt < 3; rowt++)
					{
						for (int colt = -2; colt < 3; colt++)
						{
							rgb.red = image2.GetRed(col + colt, row + rowt);
							rgb.green = image2.GetGreen(col + colt, row + rowt);
							rgb.blue = image2.GetBlue(col + colt, row + rowt);
							hsv[hsvcount++] = wxImage::RGBtoHSV(rgb);
						}
					}
					
					rgb.red = image2.GetRed(col, row);
					rgb.green = image2.GetGreen(col, row);
					rgb.blue = image2.GetBlue(col, row);
					wxImage::HSVValue hsvreal;

					hsvreal = wxImage::RGBtoHSV(rgb);

					for (int i = 0; i < 25; i++)
					{
						sum += hsv[i].value;
					}

					ave = sum / 25;
					
					for (int i = 0; i < 25; i++)
					{
						deviation[i] = (hsv[i].value - ave)*(hsv[i].value - ave);
						devave += deviation[i];
					}
					devave /= 25;
					double delta = abs(hsvreal.value - hsv[13].value);
				
					double calc = 20 * spinctrldbl20->GetValue() * sqrt(devave) + 0.2 * spinctrldbl20->GetValue() * delta;
						
					if (calc > 1.0)
						calc = 1.0;
						
					hsv[13].saturation = 1;
					hsv[13].hue = calc;
					hsv[13].value = calc;
				
					wxImage::RGBValue rgbmask = wxImage::HSVtoRGB(hsv[13]);
					wxImage::RGBValue rgborig;
					rgborig.red = image.GetRed(col, row);
					rgborig.green = image.GetGreen(col, row);
					rgborig.blue = image.GetBlue(col, row);
					if (m_checkBox22->IsChecked())
					{
						image.SetRGB(col, row, rgbmask.red, rgbmask.green, rgbmask.blue);
					}
					else
					{
						image.SetRGB(col, row, (float) rgborig.red * calc + (float) rgb.red * (1-calc), (float)rgborig.green * calc + (float)rgb.green * (1 - calc), (float)rgborig.blue * calc + (float)rgb.blue * (1 - calc));
					}
					count++;
				}
			}
		}
		drawPane->SetImage(image.Copy());
	}
};

void ImageDlg::OnSave(wxCommandEvent& event)
{
	wxFileName name(filename);
	wxString savepath = name.GetName();
	wxFileDialog
		saveFileDialog(this, _("Save image file"), "", savepath + ".jpg",
			"JPEG files (*.jpg; *.jpeg) | *.jpg;*.jpeg | BMP files (*.bmp) | *.bmp | PNG files (*.png) | *.png | PCX files (*.pcx) | *.pcx | TIFF files (*.tif; *.tiff) | *.tif;*.tiff", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	saveFileDialog.Center();
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;     

	wxString ext;
	wxBitmapType imageext = wxBITMAP_TYPE_JPEG;
	wxFileName fname(saveFileDialog.GetPath());
	ext = fname.GetExt();
	ext.MakeLower();
	if (ext == "jpg" || ext == "jpeg")
		imageext = wxBITMAP_TYPE_JPEG;
	else if (ext == "bmp")
		imageext = wxBITMAP_TYPE_BMP;
	else if (ext == "png")
		imageext = wxBITMAP_TYPE_PNG;
	else if (ext == "pcx")
		imageext = wxBITMAP_TYPE_PCX;
	else if (ext == "tif" || ext == "tiff")
		imageext = wxBITMAP_TYPE_TIF;
	if (drawPane->image.SaveFile(saveFileDialog.GetPath(), imageext))
	{
		//wxMessageBox("File was successfully saved");
	}
	else
	{
		wxMessageBox("Failed to save file");
	}
}

void ImageDlg::OnReload(wxCommandEvent& event)
{
	itemToolBar->ToggleTool(ID_THUMBNAIL, false);
	SetImage();
}

void ImageDlg::OnThumbnail(wxCommandEvent& event)
{
	if (isRaw)
	{
		if (itemToolBar->GetToolState(ID_THUMBNAIL))
		{
			if (!image_thumbnail.IsOk())
			{
				wxBusyCursor busy;
				LibRaw iProcessor;
				iProcessor.open_file(filename.char_str());
				iProcessor.unpack_thumb();
				libraw_processed_image_t *img_ptr = iProcessor.dcraw_make_mem_thumb();
				wxMemoryInputStream inputstream(img_ptr->data, img_ptr->data_size);
				image_thumbnail.LoadFile(inputstream, wxBITMAP_TYPE_JPEG);
				iProcessor.recycle();
				LibRaw::dcraw_clear_mem(img_ptr);
			}
			drawPane->SetImage(image_thumbnail.Copy());
		}
		else
		{
			drawPane->SetImage(image.Copy());
		}
	}
}

void ImageDlg::OnCustomWB(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		m_panel3->SetScrollbars(0, 20, 0, 20, 0, 0);
		spinctrldbl1->Enable(true);
		spinctrldbl2->Enable(true);
		spinctrldbl3->Enable(true);
	}
	else
	{
		m_panel3->SetScrollbars(0, 20, 0, 20, 0, 0);
		spinctrldbl1->Enable(false);
		spinctrldbl2->Enable(false);
		spinctrldbl3->Enable(false);
	}
}

void ImageDlg::OnAber(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		spinctrldbl4->Enable(true);
		spinctrldbl5->Enable(true);
	}
	else
	{
		spinctrldbl4->Enable(false);
		spinctrldbl5->Enable(false);
	}
}

void ImageDlg::OnBlack(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		spinctrl1->Enable(true);
	}
	else
	{
		spinctrl1->Enable(false);
	}
}

void ImageDlg::OnSaturation(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		spinctrl2->Enable(true);
	}
	else
	{
		spinctrl2->Enable(false);
	}
}

void ImageDlg::OnNoise(wxCommandEvent& event)
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

void ImageDlg::OnHighlight(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		spinctrl4->Enable(true);
	}
	else
	{
		spinctrl4->Enable(false);
	}
}

void ImageDlg::OnFlip(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		spinctrl5->Enable(true);
	}
	else
	{
		spinctrl5->Enable(false);
	}
}

void ImageDlg::OnBright(wxCommandEvent& event)
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

void ImageDlg::OnGamma(wxCommandEvent& event)
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

void ImageDlg::OnContrast(wxCommandEvent& event)
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

void ImageDlg::OnSat(wxCommandEvent& event)
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

void ImageDlg::OnRed(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		spinctrldbl13->Enable(true);
		spinctrldbl14->Enable(true);
	}
	else
	{
		spinctrldbl13->Enable(false);
		spinctrldbl14->Enable(false);
	}
}

void ImageDlg::OnGreen(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		spinctrldbl15->Enable(true);
		spinctrldbl16->Enable(true);
	}
	else
	{
		spinctrldbl15->Enable(false);
		spinctrldbl16->Enable(false);
	}
}

void ImageDlg::OnBlue(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		spinctrldbl17->Enable(true);
		spinctrldbl18->Enable(true);
	}
	else
	{
		spinctrldbl17->Enable(false);
		spinctrldbl18->Enable(false);
	}
}

void ImageDlg::OnPixel(wxCommandEvent& event)
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

void ImageDlg::OnMedian(wxCommandEvent& event)
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

void ImageDlg::mouseWheelMoved(wxMouseEvent& event) {
	event.Skip();
}

void ImageDlg::OnMouse(wxMouseEvent& event) {
	event.Skip();
}
