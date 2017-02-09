#ifndef _WX_MAIN_H_ 
#define _WX_MAIN_H_ 

#include "libraw/libraw.h"
#include "wx/wxprec.h"
#include "wx/wx.h"
#include "wx/app.h"
#include "wx/grid.h"
#include "wx/splitter.h"
#include "wx/file.h"
#include <cstdio>
#include <iostream> 
#include "wx/artprov.h"
#include "wx/menu.h"
#include "wx/treectrl.h"
#include "wx/toolbar.h"
#include "wx/msgdlg.h"
#include "wx/busyinfo.h"
#include "wx/aui/aui.h"
#include "wx/dirctrl.h" 
#include "wx/filename.h"
#include "wx/toolbar.h"

#include "wx/dynarray.h" 
#include <wx/mstream.h>
#include <openssl/md5.h>

#include "thumbnailctrl.h" 
#include "ProcessDlg.h"
#include "ImageDlg.h"
#include "FaceDlg.h"
#include "sqlite3.h"
#include "EXIF.H"

class wxGenericDirCtrl;
class wxThumbnailCtrl;

class MyApp : public wxApp
{
public:
	virtual bool OnInit() wxOVERRIDE;
};

DECLARE_APP(MyApp)
IMPLEMENT_APP(MyApp)

class MyFrame : public wxFrame
{
	DECLARE_CLASS(MyFrame)
	DECLARE_EVENT_TABLE()
	
	enum
	{
		ID_PANEL,// = wxID_HIGHEST+1,
		ID_PANEL1,
		ID_PANEL2,
		ID_MENUITEM,
		ID_SPLITTERWINDOW,
		ID_TREECTRL,
		ID_NOTEBOOK,
		ID_TOOLBAR,
		ID_TOOL,
		ID_TOOL1,
		ID_TOOL2,
		ID_IMAGE_BROWSER_DIRCTRL,
		ID_IMAGE_BROWSER_BROWSER,
		ID_GRID,
		ID_RELOAD,
		ID_SORT,
		ID_SORTNAMEASC,
		ID_SORTNAMEDSC,
		ID_SORTTIMEASC,
		ID_SORTTIMEDSC,
		ID_SORTTYPEASC,
		ID_SORTTYPEDSC,
		ID_SELECTALL,
		ID_UNSELECTALL,
		ID_DELETE,
		ID_INFO,
		ID_FACES,
		ID_IMAGE,
		ID_PROCESS,
	};

public:
	//MyFrame();
	MyFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);
	
	void ShowFolder(const wxString& path);

	void SetSelection(const wxString& filename);
	wxString GetSelection() const;
	wxArrayString GetSelections() const;

	void OnImageBrowserDirctrlSelChanged(wxTreeEvent& event);
	static bool ShowToolTips();
	
	wxToolBar          *m_tbar;
	wxGenericDirCtrl* m_dirCtrl;
	wxThumbnailCtrl* m_imageBrowser;

	int m_selectionCount;

	wxString m_initialSelection;

	void OnReload(wxCommandEvent& event);
	void OnSortNameASC(wxCommandEvent& event);
	void OnSortNameDSC(wxCommandEvent& event);
	void OnSortTimeASC(wxCommandEvent& event);
	void OnSortTimeDSC(wxCommandEvent& event);
	void OnSortTypeASC(wxCommandEvent& event);
	void OnSortTypeDSC(wxCommandEvent& event);
	void OnSelectAll(wxCommandEvent& event);
	void OnUnselectAll(wxCommandEvent& event);
	void OnDelete(wxCommandEvent& event);
	void OnInfo(wxCommandEvent& event);
	void OnFaces(wxCommandEvent& event);
	void OnImage(wxCommandEvent& event);
	void OnProcess(wxCommandEvent& event);
	void OnLeftDClick(wxThumbnailEvent& WXUNUSED(event));
	//~MyFrame();
};

#endif 
#pragma once