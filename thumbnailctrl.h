#ifndef _WX_THUMBNAILCTRL_H_ 
#define _WX_THUMBNAILCTRL_H_ 

#include "wx/dynarray.h" 
#include <wx/mstream.h>
#include <openssl/md5.h>
#include "sqlite3.h"
#include "EXIF.H"

#define wxTH_MULTIPLE_SELECT    0x0010 
#define wxTH_SINGLE_SELECT      0x0000 
#define wxTH_TEXT_LABEL         0x0020 
#define wxTH_IMAGE_LABEL        0x0040 
#define wxTH_EXTENSION_LABEL    0x0080 

#define wxTHUMBNAIL_SHIFT_DOWN  0x01 
#define wxTHUMBNAIL_CTRL_DOWN   0x02 
#define wxTHUMBNAIL_ALT_DOWN    0x04 

#define wxTHUMBNAIL_SORT_NAME_UP            1 
#define wxTHUMBNAIL_SORT_NAME_DOWN          2 
#define wxTHUMBNAIL_SORT_TIMESTAMP_UP       3 
#define wxTHUMBNAIL_SORT_TIMESTAMP_DOWN     4 
#define wxTHUMBNAIL_SORT_NUMERICALLY_UP     5 
#define wxTHUMBNAIL_SORT_NUMERICALLY_DOWN   6 
#define wxTHUMBNAIL_SORT_TYPE_UP            7 
#define wxTHUMBNAIL_SORT_TYPE_DOWN          8 

#define wxTHUMBNAIL_DEFAULT_OVERALL_SIZE wxSize(-1, -1) 
#define wxTHUMBNAIL_DEFAULT_IMAGE_SIZE wxSize(80, 80) 
#define wxTHUMBNAIL_DEFAULT_SPACING 3 
#define wxTHUMBNAIL_DEFAULT_MARGIN 3 
#define wxTHUMBNAIL_DEFAULT_UNFOCUSSED_BACKGROUND wxColour(175, 175, 175) 
#define wxTHUMBNAIL_DEFAULT_FOCUSSED_BACKGROUND wxColour(140, 140, 140) 
// #define wxTHUMBNAIL_DEFAULT_UNSELECTED_BACKGROUND wxColour(205, 205, 205) 
#define wxTHUMBNAIL_DEFAULT_UNSELECTED_BACKGROUND wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE) 
#define wxTHUMBNAIL_DEFAULT_TYPE_COLOUR wxColour(0, 0, 200) 
#define wxTHUMBNAIL_DEFAULT_TAG_COLOUR wxColour(0, 0, 255) 
#define wxTHUMBNAIL_DEFAULT_FOCUS_RECT_COLOUR wxColour(100, 80, 80) 

class wxThumbnailCtrl;

#define wxTHUMBNAIL_SELECTED    0x01 
#define wxTHUMBNAIL_TAGGED      0x02 
#define wxTHUMBNAIL_FOCUSSED    0x04 
#define wxTHUMBNAIL_IS_FOCUS    0x08 

class wxThumbnailItem : public wxObject
{
	DECLARE_CLASS(wxThumbnailItem)
public:

	wxThumbnailItem(const wxString& filename = wxEmptyString)
	{
		m_filename = filename; m_state = 0;
	}

	void SetFilename(const wxString& filename) { m_filename = filename; }
	const wxString& GetFilename() const { return m_filename; }

	void SetState(int state) { m_state = state; }
	int GetState() const { return m_state; }

	virtual bool Draw(wxDC& dc, wxThumbnailCtrl* ctrl, const wxRect& rect, int style);
	
	virtual bool DrawBackground(wxDC& dc, wxThumbnailCtrl* ctrl, const wxRect& rect, const wxRect& imageRect, int style, int index);

	virtual bool Load(wxThumbnailCtrl* WXUNUSED(ctrl), bool WXUNUSED(forceLoad)) { return false; }

	bool isRaw;
	wxString hash;

protected:
	wxString    m_filename;
	int         m_state; 
};

class wxImageThumbnailItem : public wxThumbnailItem
{
	DECLARE_CLASS(wxImageThumbnailItem)
public:

	wxImageThumbnailItem(const wxString& filename = wxEmptyString) :
		wxThumbnailItem(filename) {}

	virtual bool Draw(wxDC& dc, wxThumbnailCtrl* ctrl, const wxRect& rect, int style);

	virtual bool Load(wxThumbnailCtrl* ctrl, bool forceLoad);

	sqlite3 *m_db;

protected:
	wxBitmap    m_cachedBitmap;
};



WX_DECLARE_OBJARRAY(wxThumbnailItem, wxThumbnailItemArray);

class wxThumbnailCtrl : public wxScrolledWindow
{
	DECLARE_CLASS(wxThumbnailCtrl)
	DECLARE_EVENT_TABLE()

public:

	wxThumbnailCtrl();
	wxThumbnailCtrl(wxWindow* parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
		long style = wxTH_TEXT_LABEL | wxTH_IMAGE_LABEL | wxTH_EXTENSION_LABEL);

	bool Create(wxWindow* parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
		long style = wxTH_TEXT_LABEL | wxTH_IMAGE_LABEL | wxTH_EXTENSION_LABEL);

	void Init();

	void Freeze();

	void Thaw();

	void EnsureVisible(int n);

	void Reload(int n);

	int FindItemForFilename(const wxString& filename);

	void Sort(int sortMode);

	virtual bool DrawItem(int n, wxDC& dc, const wxRect& rect, int style);

	virtual bool DrawItemBackground(int n, wxDC& dc, const wxRect& rect, const wxRect& imageRect, int style);

	virtual int Append(wxThumbnailItem* item);

	virtual int Insert(wxThumbnailItem* item, int pos = 0);

	virtual void Clear();

	virtual void Delete(int n);

	virtual int GetCount() const { return m_items.GetCount(); }

	bool IsEmpty() const { return GetCount() == 0; }

	wxThumbnailItem* GetItem(int n);

	bool GetItemRect(int item, wxRect& rect, bool transform = true);

	bool GetItemRectImage(int item, wxRect& rect, bool transform = true);

	bool GetRowCol(int item, const wxSize& clientSize, int& row, int& col);

	int GetFocusItem() const { return m_focusItem; }

	void SetFocusItem(int item);

	void Select(int n, bool select = true);

	void SelectRange(int from, int to, bool select = true);

	void Tag(int n, bool tag = true);

	void SelectAll();

	void SelectNone();

	int GetSelection() const;

	const wxArrayInt& GetSelections() const { return m_selections; }

	const wxArrayInt& GetTags() const { return m_tags; }

	bool IsSelected(int n) const;

	bool IsTagged(int n) const;

	void ClearSelections();

	void ClearTags();

	void SetThumbnailOverallSize(const wxSize& sz) { m_thumbnailOverallSize = sz; }
	const wxSize& GetThumbnailOverallSize() const { return m_thumbnailOverallSize; }

	void SetThumbnailImageSize(const wxSize& sz);
	const wxSize& GetThumbnailImageSize() const { return m_thumbnailImageSize; }

	void SetSpacing(int spacing) { m_spacing = spacing; }
	int GetSpacing() const { return m_spacing; }

	void SetThumbnailMargin(int margin) { m_thumbnailMargin = margin; }
	int GetThumbnailMargin() const { return m_thumbnailMargin; }

	void SetThumbnailTextHeight(int h) { m_thumbnailTextHeight = h; }
	int GetThumbnailTextHeight() const { return m_thumbnailTextHeight; }

	void SetSelectedThumbnailBackgroundColour(const wxColour& focussedColour, const wxColour& unfocussedColour)
	{
		m_focussedThumbnailBackgroundColour = focussedColour; m_unfocussedThumbnailBackgroundColour = unfocussedColour;
	}
	const wxColour& GetSelectedThumbnailFocussedBackgroundColour() const { return m_focussedThumbnailBackgroundColour; }
	const wxColour& GetSelectedThumbnailUnfocussedBackgroundColour() const { return m_unfocussedThumbnailBackgroundColour; }

	void SetUnselectedThumbnailBackgroundColour(const wxColour& colour) { m_unselectedThumbnailBackgroundColour = colour; }
	const wxColour& GetUnselectedThumbnailBackgroundColour() const { return m_unselectedThumbnailBackgroundColour; }

	void SetTypeColour(const wxColour& colour) { m_typeColour = colour; }
	const wxColour& GetTypeColour() const { return m_typeColour; }

	void SetTagColour(const wxColour& colour) { m_tagColour = colour; }
	const wxColour& GetTagColour() const { return m_tagColour; }

	void SetFocusRectColour(const wxColour& colour) { m_focusRectColour = colour; }
	const wxColour& GetFocusRectColour() const { return m_focusRectColour; }

	void OnSelectAll(wxCommandEvent& event);
	void OnUpdateSelectAll(wxUpdateUIEvent& event);

	void OnPaint(wxPaintEvent& event);
	void OnEraseBackground(wxEraseEvent& event);

	void OnLeftClick(wxMouseEvent& event);

	void OnLeftDClick(wxMouseEvent& event);

	void OnMiddleClick(wxMouseEvent& event);

	void OnRightClick(wxMouseEvent& event);

	void OnChar(wxKeyEvent& event);

	void OnSize(wxSizeEvent& event);

	void OnSetFocus(wxFocusEvent& event);
	void OnKillFocus(wxFocusEvent& event);

	void SetupScrollbars();

	void CalculateOverallThumbnailSize();

	void DoSelection(int n, int flags);

	bool HitTest(const wxPoint& pt, int& n);

	virtual bool Navigate(int keyCode, int flags);

	void ScrollIntoView(int n, int keyCode);

	void PaintBackground(wxDC& dc);

	bool RecreateBuffer(const wxSize& size = wxDefaultSize);

	const wxBitmap& GetTagBitmap() const { return m_tagBitmap; }

	void SetSortMode(int sortMode) { m_sortMode = sortMode; }
	int GetSortMode() const { return m_sortMode; }

	static wxThumbnailCtrl* GetThumbnailCtrl() { return sm_currentThumbnailCtrl; }

	wxSize DoGetBestSize() const;

private:

	wxThumbnailItemArray    m_items;

	wxArrayInt              m_selections;

	wxArrayInt              m_tags;

	wxSize                  m_thumbnailOverallSize;

	wxSize                  m_thumbnailImageSize;

	int                     m_spacing;

	int                     m_thumbnailMargin;

	int                     m_thumbnailTextHeight;

	int                     m_freezeCount;

	int                     m_firstSelection;

	int                     m_lastSelection;

	int                     m_focusItem;

	wxBitmap                m_tagBitmap;

	int                     m_sortMode;

	static wxThumbnailCtrl* sm_currentThumbnailCtrl;

	wxColour                m_focussedThumbnailBackgroundColour;
	wxColour                m_unfocussedThumbnailBackgroundColour;
	wxColour                m_unselectedThumbnailBackgroundColour;
	wxColour                m_focusRectColour;

	wxColour                m_typeColour;

	wxColour                m_tagColour;

	wxBitmap                m_bufferBitmap;
};

class wxThumbnailEvent : public wxNotifyEvent
{
public:
	wxThumbnailEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
		: wxNotifyEvent(commandType, winid),
		m_itemIndex(-1), m_flags(0)
	{ }

	wxThumbnailEvent(const wxThumbnailEvent& event)
		: wxNotifyEvent(event),
		m_itemIndex(event.m_itemIndex), m_flags(event.m_flags)
	{ }

	int GetIndex() const { return m_itemIndex; }
	void SetIndex(int n) { m_itemIndex = n; }

	int GetFlags() const { return m_flags; }
	void SetFlags(int flags) { m_flags = flags; }

	virtual wxEvent *Clone() const { return new wxThumbnailEvent(*this); }

protected:
	int           m_itemIndex;
	int           m_flags;

private:
	DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxThumbnailEvent)
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_COMMAND_THUMBNAIL_ITEM_SELECTED, 2600)
DECLARE_EVENT_TYPE(wxEVT_COMMAND_THUMBNAIL_ITEM_DESELECTED, 2601)
DECLARE_EVENT_TYPE(wxEVT_COMMAND_THUMBNAIL_LEFT_CLICK, 2602)
DECLARE_EVENT_TYPE(wxEVT_COMMAND_THUMBNAIL_RIGHT_CLICK, 2603)
DECLARE_EVENT_TYPE(wxEVT_COMMAND_THUMBNAIL_MIDDLE_CLICK, 2604)
DECLARE_EVENT_TYPE(wxEVT_COMMAND_THUMBNAIL_LEFT_DCLICK, 2605)
DECLARE_EVENT_TYPE(wxEVT_COMMAND_THUMBNAIL_RETURN, 2606)
END_DECLARE_EVENT_TYPES()

typedef void (wxEvtHandler::*wxThumbnailEventFunction)(wxThumbnailEvent&);

#define EVT_THUMBNAIL_ITEM_SELECTED(id, fn) DECLARE_EVENT_TABLE_ENTRY( wxEVT_COMMAND_THUMBNAIL_ITEM_SELECTED, id, -1, (wxObjectEventFunction) (wxEventFunction)  wxStaticCastEvent( wxThumbnailEventFunction, & fn ), NULL ), 
#define EVT_THUMBNAIL_ITEM_DESELECTED(id, fn) DECLARE_EVENT_TABLE_ENTRY( wxEVT_COMMAND_THUMBNAIL_ITEM_DESELECTED, id, -1, (wxObjectEventFunction) (wxEventFunction)  wxStaticCastEvent( wxThumbnailEventFunction, & fn ), NULL ), 
#define EVT_THUMBNAIL_LEFT_CLICK(id, fn) DECLARE_EVENT_TABLE_ENTRY( wxEVT_COMMAND_THUMBNAIL_LEFT_CLICK, id, -1, (wxObjectEventFunction) (wxEventFunction)  wxStaticCastEvent( wxThumbnailEventFunction, & fn ), NULL ), 
#define EVT_THUMBNAIL_RIGHT_CLICK(id, fn) DECLARE_EVENT_TABLE_ENTRY( wxEVT_COMMAND_THUMBNAIL_RIGHT_CLICK, id, -1, (wxObjectEventFunction) (wxEventFunction)  wxStaticCastEvent( wxThumbnailEventFunction, & fn ), NULL ), 
#define EVT_THUMBNAIL_MIDDLE_CLICK(id, fn) DECLARE_EVENT_TABLE_ENTRY( wxEVT_COMMAND_THUMBNAIL_MIDDLE_CLICK, id, -1, (wxObjectEventFunction) (wxEventFunction)  wxStaticCastEvent( wxThumbnailEventFunction, & fn ), NULL ), 
#define EVT_THUMBNAIL_LEFT_DCLICK(id, fn) DECLARE_EVENT_TABLE_ENTRY( wxEVT_COMMAND_THUMBNAIL_LEFT_DCLICK, id, -1, (wxObjectEventFunction) (wxEventFunction)  wxStaticCastEvent( wxThumbnailEventFunction, & fn ), NULL ), 
#define EVT_THUMBNAIL_RETURN(id, fn) DECLARE_EVENT_TABLE_ENTRY( wxEVT_COMMAND_THUMBNAIL_RETURN, id, -1, (wxObjectEventFunction) (wxEventFunction)  wxStaticCastEvent( wxThumbnailEventFunction, & fn ), NULL ), 

#endif 
#pragma once
