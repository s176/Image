#include "Main.h"
#include "wx/dir.h"   

/// Returns the image type, or -1, determined from the extension.   
static int DetermineImageType(const wxString& filename);

IMPLEMENT_CLASS(MyFrame, wxFrame)

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_TREE_SEL_CHANGED(wxID_TREECTRL, MyFrame::OnImageBrowserDirctrlSelChanged)
EVT_THUMBNAIL_LEFT_DCLICK(ID_IMAGE_BROWSER_BROWSER, MyFrame::OnLeftDClick)
EVT_TREE_SEL_CHANGED(ID_IMAGE_BROWSER_DIRCTRL, MyFrame::OnImageBrowserDirctrlSelChanged)
EVT_MENU(ID_RELOAD, MyFrame::OnReload)
EVT_MENU(ID_SORT, MyFrame::OnSortNameASC)
EVT_MENU(ID_SORTNAMEASC, MyFrame::OnSortNameASC)
EVT_MENU(ID_SORTNAMEDSC, MyFrame::OnSortNameDSC)
EVT_MENU(ID_SORTTIMEASC, MyFrame::OnSortTimeASC)
EVT_MENU(ID_SORTTIMEDSC, MyFrame::OnSortTimeDSC)
EVT_MENU(ID_SORTTYPEASC, MyFrame::OnSortTypeASC)
EVT_MENU(ID_SORTTYPEDSC, MyFrame::OnSortTypeDSC)
EVT_MENU(ID_SELECTALL, MyFrame::OnSelectAll)
EVT_MENU(ID_UNSELECTALL, MyFrame::OnUnselectAll)
EVT_MENU(ID_DELETE, MyFrame::OnDelete)
EVT_MENU(ID_INFO, MyFrame::OnInfo)
EVT_MENU(ID_FACES, MyFrame::OnFaces)
EVT_MENU(ID_PROCESS, MyFrame::OnProcess)
EVT_MENU(ID_IMAGE, MyFrame::OnImage)
END_EVENT_TABLE()

bool MyApp::OnInit()
{

	if (!wxApp::OnInit())
		return false;

	wxInitAllImageHandlers();

	wxFrame* frame = new MyFrame(NULL, wxID_ANY, wxT("Process raw photos"), wxDefaultPosition, wxSize(800, 600));
	frame->Maximize();
	frame->Show();

	return true;
}


MyFrame::MyFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style)
{
	m_selectionCount = -1;

	m_dirCtrl = NULL;
	m_imageBrowser = NULL;

	SetExtraStyle(wxWS_EX_BLOCK_EVENTS);

	wxPanel* itemPanel1 = new wxPanel(this, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL);

	wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	itemPanel1->SetSizer(itemBoxSizer1);
	itemPanel1->SetAutoLayout(TRUE);

	wxToolBar* itemToolBar = new wxToolBar(itemPanel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT | wxTB_HORIZONTAL | wxTB_TEXT | wxNO_BORDER);

	wxBitmap itemtool1Bitmap = wxArtProvider::GetBitmap(wxART_REDO, wxART_OTHER, wxSize(16, 16));
	itemToolBar->AddTool(ID_RELOAD, wxT("Reload"), itemtool1Bitmap, wxNullBitmap, wxITEM_NORMAL, wxT("Reopen folder"), wxT("Reloads current folder"));

	wxBitmap itemtool2Bitmap = wxArtProvider::GetBitmap(wxART_HELP_SIDE_PANEL, wxART_OTHER, wxSize(16, 16));
	itemToolBar->AddTool(ID_SORT, wxT("Sort"), itemtool2Bitmap, wxNullBitmap, wxITEM_DROPDOWN, wxT("Sort images"));
	wxMenu* menu1 = new wxMenu;
	menu1->Append(ID_SORTNAMEASC, wxT("by name ascending"));
	menu1->Append(ID_SORTNAMEDSC, wxT("by name descending"));
	menu1->AppendSeparator();
	menu1->Append(ID_SORTTIMEASC, wxT("by time ascending"));
	menu1->Append(ID_SORTTIMEDSC, wxT("by time descending"));
	menu1->AppendSeparator();
	menu1->Append(ID_SORTTYPEASC, wxT("by type ascending"));
	menu1->Append(ID_SORTTYPEDSC, wxT("by type descending"));
	itemToolBar->SetDropdownMenu(ID_SORT, menu1);

	wxBitmap itemtool3Bitmap = wxArtProvider::GetBitmap(wxART_LIST_VIEW, wxART_OTHER, wxSize(16, 16));
	itemToolBar->AddTool(ID_SELECTALL, wxT("Select all"), itemtool3Bitmap, wxNullBitmap, wxITEM_NORMAL, wxT("Select all images in folder"));
	
	wxBitmap itemtool4Bitmap = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
	itemToolBar->AddTool(ID_UNSELECTALL, wxT("Unselect"), itemtool4Bitmap, wxNullBitmap, wxITEM_NORMAL, wxT("Unselect all images in folder"));
	
	wxBitmap itemtool5Bitmap = wxArtProvider::GetBitmap(wxART_DELETE, wxART_OTHER, wxSize(16, 16));
	itemToolBar->AddTool(ID_DELETE, wxT("Delete"), itemtool5Bitmap, wxNullBitmap, wxITEM_NORMAL, wxT("Delete selected images"));
	
	wxBitmap itemtool6Bitmap = wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_OTHER, wxSize(16, 16));
	itemToolBar->AddTool(ID_INFO, wxT("Foto info"), itemtool6Bitmap, wxNullBitmap, wxITEM_NORMAL, wxT("EXIF Info of selected photo"));
	
	wxBitmap itemtool7Bitmap = wxArtProvider::GetBitmap(wxART_FIND_AND_REPLACE, wxART_OTHER, wxSize(16, 16));
	itemToolBar->AddTool(ID_FACES, wxT("Faces"), itemtool7Bitmap, wxNullBitmap, wxITEM_NORMAL, wxT("Detect faces on selected image"));

	wxBitmap itemtool8Bitmap = wxArtProvider::GetBitmap(wxART_FULL_SCREEN, wxART_OTHER, wxSize(16, 16));
	itemToolBar->AddTool(ID_IMAGE, wxT("Image"), itemtool8Bitmap, wxNullBitmap, wxITEM_NORMAL, wxT("Edit selected image"));
	
	wxBitmap itemtool9Bitmap = wxArtProvider::GetBitmap(wxART_EXECUTABLE_FILE, wxART_OTHER, wxSize(16, 16));
	itemToolBar->AddTool(ID_PROCESS, wxT("Process"), itemtool9Bitmap, wxNullBitmap, wxITEM_NORMAL, wxT("Process selected raw photos (in batch)"));
	
	itemToolBar->Realize();
	
	wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer1->Add(itemBoxSizer2, 1, wxGROW | wxALL, 0);
	
	wxSplitterWindow* itemSplitterWindow1 = new wxSplitterWindow(itemPanel1, ID_SPLITTERWINDOW, wxDefaultPosition, wxSize(500, 400), wxSP_3DBORDER | wxSP_3DSASH | wxNO_BORDER | wxCLIP_CHILDREN | wxSP_LIVE_UPDATE);
	wxGenericDirCtrl* wxGenericDirCtrl1 = new wxGenericDirCtrl(itemSplitterWindow1, ID_IMAGE_BROWSER_DIRCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxDIRCTRL_DIR_ONLY, _T("All files (*.*)|*.*"), 0);
	m_dirCtrl = wxGenericDirCtrl1;
	wxThumbnailCtrl* wxThumbnailCtrl1 = new wxThumbnailCtrl(itemSplitterWindow1, ID_IMAGE_BROWSER_BROWSER, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxHSCROLL | wxVSCROLL | wxTH_TEXT_LABEL | wxTH_IMAGE_LABEL | wxTH_EXTENSION_LABEL | wxTH_MULTIPLE_SELECT);
	m_imageBrowser = wxThumbnailCtrl1;
	m_imageBrowser->SetThumbnailImageSize(wxSize(160, 130));
	itemSplitterWindow1->SplitVertically(wxGenericDirCtrl1, wxThumbnailCtrl1, 250);
	itemBoxSizer2->Add(itemToolBar, 0, wxGROW | wxALL, 0);
	itemBoxSizer2->Add(itemSplitterWindow1, 1, wxGROW | wxALL | wxFIXED_MINSIZE, 5);
	
	wxString initialPath = wxGetCwd();
	if (wxDirExists(initialPath))
	{
		SetSelection(initialPath);
	}

	if (!m_initialSelection.IsEmpty())
		SetSelection(m_initialSelection);


	
}

bool MyFrame::ShowToolTips()
{
	return TRUE;
}

void MyFrame::OnImageBrowserDirctrlSelChanged(wxTreeEvent& event)
{
	if (!m_dirCtrl || !m_imageBrowser)
		return;

	m_selectionCount++;

	if (m_selectionCount > 1)
	{
		m_selectionCount--;
		return;
	}

	wxTreeItemId id = event.GetItem();
	if (id)
	{
		wxDirItemData* data = (wxDirItemData*)m_dirCtrl->GetTreeCtrl()->GetItemData(id);
		if (data && data->m_isDir)
		{
			ShowFolder(data->m_path);
		}
	}
	m_selectionCount--;
}

void MyFrame::ShowFolder(const wxString& path)
{
	wxBusyCursor busy;
	m_imageBrowser->Clear();

	m_imageBrowser->Freeze();
	wxDir dir;
	if (dir.Open(path))
	{
		wxString filename;
		bool cont = dir.GetFirst(&filename, wxT("*.*"), wxDIR_FILES);

		sqlite3 *db;
		wxString dbname = "empirika.db";
		int rc = sqlite3_open(dbname, &db);
		if (rc)
		{
			wxMessageBox("Data base SQLite problems");
			return;
		}
		else
		{
			const char* sql = "CREATE TABLE IF NOT EXISTS thumbs(hash text primary_key, value BLOB)";

			sqlite3_stmt *stmt;
			rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
			rc = sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			
			sql = "CREATE TABLE IF NOT EXISTS faces(id INTEGER PRIMARY KEY AUTOINCREMENT, hash text, fleft int, fright int, ftop int, fbottom int, fname text)";
			
			rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
			rc = sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		}

		while (cont)
		{
			wxString file = path + wxFILE_SEP_PATH + filename;
			int ImageType = DetermineImageType(file);
			if (wxFileExists(file) && ImageType != -1)
			{
				wxImageThumbnailItem* item = new wxImageThumbnailItem(file);
				item->m_db = db;
				if (ImageType == 100)
					item->isRaw = true;
				else
					item->isRaw = false;
				m_imageBrowser->Append(item);
			}

			cont = dir.GetNext(&filename);
		}
		sqlite3_close(db);
	}
	m_imageBrowser->Thaw();
}

void MyFrame::OnReload(wxCommandEvent& event)
{
	wxTreeItemId id = (wxTreeItemId)m_dirCtrl->GetTreeCtrl()->GetSelection(); //event.GetItem();
	if (id)
	{
		wxDirItemData* data = (wxDirItemData*)m_dirCtrl->GetTreeCtrl()->GetItemData(id);
		if (data && data->m_isDir)
		{
			ShowFolder(data->m_path);
		}
	}
}

void MyFrame::OnSortNameASC(wxCommandEvent& event)
{
	m_imageBrowser->Sort(wxTHUMBNAIL_SORT_NAME_UP);
}

void MyFrame::OnSortNameDSC(wxCommandEvent& event)
{
	m_imageBrowser->Sort(wxTHUMBNAIL_SORT_NAME_DOWN);
}

void MyFrame::OnSortTimeASC(wxCommandEvent& event)
{
	m_imageBrowser->Sort(wxTHUMBNAIL_SORT_TIMESTAMP_UP);
}

void MyFrame::OnSortTimeDSC(wxCommandEvent& event)
{
	m_imageBrowser->Sort(wxTHUMBNAIL_SORT_TIMESTAMP_DOWN);
}

void MyFrame::OnSortTypeASC(wxCommandEvent& event)
{
	m_imageBrowser->Sort(wxTHUMBNAIL_SORT_TYPE_UP);
}

void MyFrame::OnSortTypeDSC(wxCommandEvent& event)
{
	m_imageBrowser->Sort(wxTHUMBNAIL_SORT_TYPE_DOWN);
}

void MyFrame::OnSelectAll (wxCommandEvent& event)
{
	m_imageBrowser->SelectAll();
}

void MyFrame::OnUnselectAll(wxCommandEvent& event)
{
	m_imageBrowser->SelectNone();
}

void MyFrame::OnDelete(wxCommandEvent& event)
{
	size_t i;
	size_t count = m_imageBrowser->GetSelections().GetCount();
	if (count > 0)
	{
		if (wxMessageBox("Are you sure you want to remove " + wxString::Format(wxT("%i"), count) + " file(s)?", wxT("Confirm file deletion"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
		{
			for (i = 0; i < count; i++)
			{
				wxThumbnailItem* item = m_imageBrowser->GetItem(m_imageBrowser->GetSelections()[i]);
				if (item)
				{
					if (remove(item->GetFilename().c_str()) != 0)
					{
						wxMessageBox("Error deleting file: " + item->GetFilename());
					}
					else
					{
						//wxMessageBox( wxString::Format(wxT("%i"), m_imageBrowser->GetSelections()[i]));
					}
				}
			}
			wxTreeItemId id = (wxTreeItemId)m_dirCtrl->GetTreeCtrl()->GetSelection(); //event.GetItem();
			if (id)
			{
				wxDirItemData* data = (wxDirItemData*)m_dirCtrl->GetTreeCtrl()->GetItemData(id);
				if (data && data->m_isDir)
				{
					ShowFolder(data->m_path);
				}
			}
		}
	}
}

void MyFrame::OnInfo(wxCommandEvent& event)
{
	size_t i;
	size_t count = m_imageBrowser->GetSelections().GetCount();
	if (count > 1)
	{
		long size = 0;
		FILE *pFile;
		int filescount = 0;
		for (i = 0; i < count; i++)
		{
			wxThumbnailItem* item = m_imageBrowser->GetItem(m_imageBrowser->GetSelections()[i]);
			if (item)
			{
				pFile = fopen(item->GetFilename().c_str(), "rb");
				if (pFile != NULL)
				{
					filescount++;
					fseek(pFile, 0, SEEK_END);
					size += ftell(pFile);
					fclose(pFile);
				}
			}
		}

		long double kilobyte;
		long double megabyte;
		kilobyte = (double) size / 1024;
		megabyte = kilobyte / 1024;
		if (megabyte > 1)
		{
			wxMessageBox(wxString::Format(wxT("%i"),filescount) + " files selected \n" + wxString::Format(wxT("%3.3f"), megabyte) + " MB");
		}
		else if (megabyte <=1 && kilobyte > 1)
		{
			wxMessageBox(wxString::Format(wxT("%i"), filescount) + " files selected \n" + wxString::Format(wxT("%3.3f"), kilobyte) + " KB");
		}
		else 
		{
			wxMessageBox(wxString::Format(wxT("%i"), filescount) + " files selected \n" + wxString::Format(wxT("%i"), size) + " B");
		}
			
	}
	else if (count == 1)
	{
		wxThumbnailItem* item = m_imageBrowser->GetItem(m_imageBrowser->GetSelection());
		if (item->isRaw)
		{
			LibRaw iProcessor;
			iProcessor.open_file(item->GetFilename().char_str());
			wxString textInfo = "File name: " + item->GetFilename().c_str() + "\n";

			textInfo += "Camera: ";
			textInfo += iProcessor.imgdata.idata.make;
			textInfo += "\nModel: ";
			textInfo += iProcessor.imgdata.idata.model;
			textInfo += "\nLens: ";
			textInfo += iProcessor.imgdata.lens.Lens;
			textInfo += "\nWidth x Height: ";
			textInfo += wxString::Format(wxT("%i"), iProcessor.imgdata.sizes.width);
			textInfo += " x ";
			textInfo += wxString::Format(wxT("%i"), iProcessor.imgdata.sizes.height);
			textInfo += "\nFocal length: ";
			textInfo += wxString::Format(wxT("%3.1f"), iProcessor.imgdata.other.focal_len);
			textInfo += "mm\nExposure time: 1/";
			textInfo += wxString::Format(wxT("%3.0f"), 1 / iProcessor.imgdata.other.shutter);
			textInfo += "\nAperture: f/";
			textInfo += wxString::Format(wxT("%3.1f"), iProcessor.imgdata.other.aperture);
			textInfo += "\nISO equivalent: ";
			textInfo += wxString::Format(wxT("%3.0f"), iProcessor.imgdata.other.iso_speed);
			
			wxMessageBox(textInfo, wxT("Image information"));
		}
		else
		{

			FILE* pFile = fopen(item->GetFilename().c_str(), "rb");
			if (pFile)
			{
				Cexif exif;
				exif.DecodeExif(pFile);
				wxString textInfo = "File name: " + item->GetFilename().c_str() + "\n";
				fseek(pFile, 0, SEEK_END);
				long size = ftell(pFile);
				long double megabyte = (double)size / 1024 / 1024;
				textInfo += "File size: " + wxString::Format(wxT("%3.3f"), megabyte) + "MB \n";
				if (exif.m_exifinfo->IsExif)
				{
					textInfo += "Camera Make: ";
					textInfo += exif.m_exifinfo->CameraMake;
					textInfo += "\nCamera Model: ";
					textInfo += exif.m_exifinfo->CameraModel;
					textInfo += "\nDate/Time: ";
					textInfo += exif.m_exifinfo->DateTime;
					textInfo += "\nWidth x Height: ";
					textInfo += wxString::Format(wxT("%i"), exif.m_exifinfo->Width);
					textInfo += " x ";
					textInfo += wxString::Format(wxT("%i"), exif.m_exifinfo->Height);
					textInfo += "\nFocal length: ";
					textInfo += wxString::Format(wxT("%3.1f"), exif.m_exifinfo->FocalLength);
					textInfo += "mm\nExposure time: 1/";
					textInfo += wxString::Format(wxT("%3.0f"), 1 / exif.m_exifinfo->ExposureTime);
					textInfo += "\nAperture: f/";
					textInfo += wxString::Format(wxT("%3.1f"), exif.m_exifinfo->ApertureFNumber);
					textInfo += "\nISO equivalent: ";
					textInfo += wxString::Format(wxT("%i"), exif.m_exifinfo->ISOequivalent);
				}

				fclose(pFile);
				wxMessageBox(textInfo, wxT("Image information"));
			}
		}
	}
}

void MyFrame::OnFaces(wxCommandEvent& event)
{
	size_t i;
	size_t count = m_imageBrowser->GetSelections().GetCount();
	if (count == 1)
	{
		wxThumbnailItem* item = m_imageBrowser->GetItem(m_imageBrowser->GetSelection());
		wxFileName fname(item->GetFilename());
		wxString  ext = fname.GetExt();
		ext.MakeLower();
		if (ext == "jpg" || ext == "jpeg")
		{
			FaceDlg* frame = new FaceDlg(NULL, wxID_ANY, item->GetFilename(), wxDefaultPosition, wxSize(800, 600));

			frame->filename = item->GetFilename();
			frame->hash = item->hash;
			frame->SetImage();
			frame->Show();
		}
		else
		{
			wxMessageBox("To detect faces on foto jpg image needed");
		}
	}
	else if (count > 1)
	{
		wxString names;
		int person_count = 0;
		for (i = 0; i < count; i++)
		{
			wxThumbnailItem* item = m_imageBrowser->GetItem(m_imageBrowser->GetSelections()[i]);
			wxFileName fname(item->GetFilename());
			wxString  ext = fname.GetExt();
			ext.MakeLower();
			if (ext == "jpg" || ext == "jpeg")
			{
				sqlite3 *db;
				wxString dbname = "empirika.db";
				int rc = sqlite3_open(dbname, &db);
				int rcread;
				std::string zSqlstring = "SELECT * FROM faces WHERE hash = '" + item->hash.c_str() + "'";
				const char *zSql = zSqlstring.c_str();
				sqlite3_stmt *pStmt;
				rcread = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
				rcread = sqlite3_step(pStmt);
				int facescount = 0;
				while (rcread == SQLITE_ROW)
				{
					std::string name;
					if (sqlite3_column_type(pStmt, 6) == SQLITE_NULL)
					{
						name = "";
					}
					else
					{
						name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(pStmt, 6)));
						names += name;
						names += "\n";
						person_count++;
					}
					rcread = sqlite3_step(pStmt);
				}
				rcread = sqlite3_finalize(pStmt);
			}		
		}
		if (person_count > 0)
			wxMessageBox(names, "Persons on images:");
	}
}

void MyFrame::OnImage(wxCommandEvent& event)
{

	size_t i;
	size_t count = m_imageBrowser->GetSelections().GetCount();
	if (count == 1)
	{
		wxThumbnailItem* item = m_imageBrowser->GetItem(m_imageBrowser->GetSelection());
		ImageDlg* frame = new ImageDlg(NULL, wxID_ANY, item->GetFilename(), wxDefaultPosition, wxSize(800, 600));
		frame->filename = item->GetFilename();
		frame->isRaw = item->isRaw;
		frame->SetImage();
		frame->Show();
	}
}

void MyFrame::OnProcess(wxCommandEvent& event)
{
	size_t i;
	size_t count = m_imageBrowser->GetSelections().GetCount();
	if (count > 0) 
	{
		ProcessDialog dlg(this);
		if (dlg.ShowModal() == wxID_OK)
		{
			for (i = 0; i < count; i++)
			{
				wxThumbnailItem* item = m_imageBrowser->GetItem(m_imageBrowser->GetSelections()[i]);
				wxImage image;
				if (item->isRaw)
				{
					LibRaw iProcessor;
					iProcessor.open_file(item->GetFilename().char_str());
					if (dlg.m_checkBox24->IsChecked())
					{

						iProcessor.unpack_thumb();
						iProcessor.dcraw_thumb_writer(item->GetFilename() + ".jpg");
						iProcessor.recycle();
					}
					else
					{
						iProcessor.unpack();
						#define OUT iProcessor.imgdata.params
						OUT.output_tiff = 1;
						if (dlg.m_checkBox1->IsChecked())
						{
							OUT.use_camera_wb = 1;
						}
						if (dlg.m_checkBox2->IsChecked())
						{
							OUT.use_auto_wb = 1;
						}
						else
						{
							OUT.use_auto_wb = 0;
						}
						if (dlg.m_checkBox7->IsChecked())
						{
							OUT.threshold = dlg.spinctrl3->GetValue();
						}
						if (dlg.m_checkBox11->IsChecked())
						{
							OUT.bright = dlg.spinctrldbl6->GetValue();
						}
						if (dlg.m_checkBox13->IsChecked())
						{
							OUT.half_size = 1;
						}
						if (dlg.m_checkBox14->IsChecked())
						{
							OUT.gamm[0] = dlg.spinctrldbl7->GetValue();
							OUT.gamm[1] = dlg.spinctrldbl8->GetValue();
						}
						int check = iProcessor.dcraw_process();
						libraw_processed_image_t *img_ptr = iProcessor.dcraw_make_mem_image(&check);
						wxImage tempimage;
						tempimage.SetData(img_ptr->data, img_ptr->width, img_ptr->height, true);
						image = tempimage.Copy();
						iProcessor.recycle();
						LibRaw::dcraw_clear_mem(img_ptr);
					}
				}
				else 
				{
					image.LoadFile(item->GetFilename(), wxBITMAP_TYPE_ANY);
				}
				if (image.IsOk())
				{
					if (dlg.m_checkBox15->IsChecked() || dlg.m_checkBox16->IsChecked())
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

								if (dlg.m_checkBox15->IsChecked())
								{
									double min = 1 / (1 + exp(-dlg.spinctrldbl10->GetValue() * (0.0 - dlg.spinctrldbl9->GetValue())));
									double max = 1 / (1 + exp(-dlg.spinctrldbl10->GetValue() * (1.0 - dlg.spinctrldbl9->GetValue())));
									double minmax = max - min;
									double value = 1 / (1 + exp(-dlg.spinctrldbl10->GetValue() * (hsv.value - dlg.spinctrldbl9->GetValue())));
									hsv.value = (value - min) / minmax;
								}

								if (dlg.m_checkBox16->IsChecked())
								{
									double min = 1 / (1 + exp(-dlg.spinctrldbl12->GetValue() * (0.0 - dlg.spinctrldbl11->GetValue())));
									double max = 1 / (1 + exp(-dlg.spinctrldbl12->GetValue() * (1.0 - dlg.spinctrldbl11->GetValue())));
									double minmax = max - min;
									double sat = 1 / (1 + exp(-dlg.spinctrldbl12->GetValue() * (hsv.saturation - dlg.spinctrldbl11->GetValue())));
									hsv.saturation = (sat - min) / minmax;
								}

								rgb = wxImage::HSVtoRGB(hsv);

								*dstBytePtr++ = rgb.red;
								*dstBytePtr++ = rgb.green;
								*dstBytePtr++ = rgb.blue;

							} while (--count != 0);
						}
					}

					if (dlg.m_checkBox20->IsChecked())
					{
						wxBusyCursor busy;

						wxImage image2 = image.Copy();
						int nHeight = image.GetHeight();
						int nWidth = image.GetWidth();
						int rgb[9][3];
						double ave[3];
						int sum[3];
						double deviation[9];
						double devave = 0;
						int count = 0;
						int rgbcount = 0;
						for (int row = 1; row < nHeight - 1; row++)
						{
							for (int col = 1; col < nWidth - 1; col++)
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
								if (sqrt(deviation[4]) > sqrt(devave) * dlg.spinctrldbl19->GetValue())
								{
									image.SetRGB(col, row, (int)ave[0], (int)ave[1], (int)ave[2]);
									count++;
								}
							}
						}
					}

					if (dlg.m_checkBox21->IsChecked())
					{
						wxBusyCursor busy;
						int blur_k = (int)sqrt(image.GetHeight() * image.GetHeight() + image.GetWidth() * image.GetWidth()) / 800;
						dlg.spinctrldbl20->GetValue();
						wxImage image2 = image.Blur(blur_k);
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

								double calc = 20 * dlg.spinctrldbl20->GetValue() * sqrt(devave) + 0.2 * dlg.spinctrldbl20->GetValue() * delta;

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
								if (dlg.m_checkBox22->IsChecked())
								{
									image.SetRGB(col, row, rgbmask.red, rgbmask.green, rgbmask.blue);
								}
								else
								{
									image.SetRGB(col, row, (float)rgborig.red * calc + (float)rgb.red * (1 - calc), (float)rgborig.green * calc + (float)rgb.green * (1 - calc), (float)rgborig.blue * calc + (float)rgb.blue * (1 - calc));
								}
								count++;
							}
						}

					}

				}


				if (dlg.m_checkBox23->IsChecked())
				{
					image.SaveFile(item->GetFilename() + ".tif", wxBITMAP_TYPE_TIF);
				}
				else
				{
					image.SaveFile(item->GetFilename() + ".jpg", wxBITMAP_TYPE_JPEG);
				}
			}
			
			wxTreeItemId id = (wxTreeItemId)m_dirCtrl->GetTreeCtrl()->GetSelection(); //event.GetItem();
			if (id)
			{
				wxDirItemData* data = (wxDirItemData*)m_dirCtrl->GetTreeCtrl()->GetItemData(id);
				if (data && data->m_isDir)
				{
					ShowFolder(data->m_path);
				}
			}
		}
		else
		{
			//wxMessageBox("Cancel");
		}
	}
}

void MyFrame::SetSelection(const wxString& filename)
{
	if (!m_imageBrowser)
	{
		m_initialSelection = filename;
		return;
	}

	m_selectionCount = 0;

	if (wxDirExists(filename))
	{
		m_dirCtrl->SetPath(filename);
		return;
	}

	wxString path = wxPathOnly(filename);
	wxString file = wxFileNameFromPath(filename);
	m_dirCtrl->SetPath(path);

	m_selectionCount = -1;

	int index = m_imageBrowser->FindItemForFilename(filename);
	if (index > -1)
	{
		m_imageBrowser->Select(index);
		m_imageBrowser->EnsureVisible(index);
	}
}

wxString MyFrame::GetSelection() const
{
	int sel = m_imageBrowser->GetSelection();
	if (sel > -1)
	{
		wxThumbnailItem* item = m_imageBrowser->GetItem(sel);
		if (item)
		{
			return item->GetFilename();
		}
	}
	return wxEmptyString;
}

wxArrayString MyFrame::GetSelections() const
{
	wxArrayString arr;
	wxArrayInt selections = m_imageBrowser->GetSelections();
	size_t i;
	for (i = 0; i < selections.GetCount(); i++)
	{
		wxThumbnailItem* item = m_imageBrowser->GetItem(selections[i]);
		if (item)
			arr.Add(item->GetFilename());
	}
	return arr;
}

static int DetermineImageType(const wxString& filename)
{
	wxString path, name, ext;
	wxFileName fname(filename);
	ext = fname.GetExt();
	ext.MakeLower();
	if (ext == "jpg" || ext == "jpeg")
		return wxBITMAP_TYPE_JPEG;
	else if (ext == "gif")
		return wxBITMAP_TYPE_GIF;
	else if (ext == "bmp")
		return wxBITMAP_TYPE_BMP;
	else if (ext == "png")
		return wxBITMAP_TYPE_PNG;
	else if (ext == "pcx")
		return wxBITMAP_TYPE_PCX;
	else if (ext == "tif" || ext == "tiff")
		return wxBITMAP_TYPE_TIF;
	else if (ext == "3fr" || ext == "arw" || ext == "bay" || ext == "bmq" || ext == "cine" || ext == "cr2" || ext == "crw" || ext == "cs1" || ext == "dc2" || ext == "dcr" || ext == "dng" || ext == "erf" || ext == "fff" || ext == "hdr" || ext == "ia" || ext == "k25" || ext == "kc2" || ext == "kdc" || ext == "mdc" || ext == "mef" || ext == "mos" || ext == "mrw" || ext == "nef" || ext == "nrw" || ext == "orf" || ext == "pef" || ext == "pxn" || ext == "qtk" || ext == "raf" || ext == "raw" || ext == "rdc" || ext == "rw2" || ext == "sr2" || ext == "srf" || ext == "sti" || ext == "x3f")
		return 100;
	else
		return -1;
}

void MyFrame::OnLeftDClick(wxThumbnailEvent& WXUNUSED(event))
{
	wxCommandEvent event2;
	OnImage(event2);
}