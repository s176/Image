#include <wx/dcbuffer.h>
#include "FacePanel.h"

BEGIN_EVENT_TABLE(wxFacePanel, wxPanel)
EVT_PAINT(wxFacePanel::paintEvent)
EVT_SIZE(wxFacePanel::OnSize)
EVT_MOUSEWHEEL(wxFacePanel::MouseWheel)
EVT_LEFT_DOWN(wxFacePanel::mouseDown)
END_EVENT_TABLE()


wxFacePanel::wxFacePanel(wxWindow* parent) :
	wxPanel(parent)
{
	w = -1;
	h = -1;
}

void wxFacePanel::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	render(dc);
}

void wxFacePanel::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void wxFacePanel::SetImage(wxImage origimage)
{
	image = origimage;
	Refresh();
}

void wxFacePanel::render(wxDC&  dc)
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
			scale = wxMin(scaleX, scaleY);
			newWidth = (int)(scale * image.GetWidth());
			newHeight = (int)(scale * image.GetHeight());
			resized = wxBitmap(image.Scale(newWidth, newHeight, wxIMAGE_QUALITY_NORMAL));
			w = newWidth;
			h = newHeight;
		}
		else
		{
			newWidth = image.GetWidth();
			newHeight = image.GetHeight();
			resized = wxBitmap(image, wxIMAGE_QUALITY_NORMAL);
		}

		XCoord = (oldWidth - newWidth) / 2;
		YCoord = (oldHeight - newHeight) / 2;
		dc.DrawBitmap(resized, XCoord, YCoord, false);
		int count = faces.size();
		for (int i = 0; i < count; i++)
		{
			wxPen pen(wxT("RED"), 2, wxSOLID);
			dc.SetPen(pen);
			wxPoint pt1;
			pt1.x = XCoord + (int)(scale * faces[i].face_rect.left());
			pt1.y = YCoord + (int)(scale * faces[i].face_rect.top());
			
			wxPoint pt2;
			pt2.x = XCoord + (int)(scale * faces[i].face_rect.right());
			pt2.y = YCoord + (int)(scale * faces[i].face_rect.top());
			
			wxPoint pt3;
			pt3.x = XCoord + (int)(scale * faces[i].face_rect.right());
			pt3.y = YCoord + (int)(scale * faces[i].face_rect.bottom());

			wxPoint pt4;
			pt4.x = XCoord + (int)(scale * faces[i].face_rect.left());
			pt4.y = YCoord + (int)(scale * faces[i].face_rect.bottom());

			wxPoint pt5;
			pt5.x = XCoord + (int)(scale * faces[i].face_rect.left());
			pt5.y = YCoord + (int)(scale * faces[i].face_rect.bottom());

			dc.SetTextForeground(wxColour(255, 150, 0));
			dc.SetFont(wxFontInfo((int)(scale*(faces[i].face_rect.right() - faces[i].face_rect.left()) / 15) + 10).Family(wxFONTFAMILY_SCRIPT));
			
			if (!faces[i].person_name.empty())
				dc.DrawText(faces[i].person_name, pt5);
			dc.DrawLine(pt1, pt2);
			dc.DrawLine(pt2, pt3);
			dc.DrawLine(pt3, pt4);
			dc.DrawLine(pt1, pt4);
		}
	}
}

void wxFacePanel::OnSize(wxSizeEvent& event) {
	Refresh();
	event.Skip();
}

void wxFacePanel::MouseWheel(wxMouseEvent& event) {
	event.Skip();
}

void wxFacePanel::ResetFaces()
{
	faces.clear();
	sqlite3 *db;
	wxString dbname = "empirika.db";
	int rc = sqlite3_open(dbname, &db);
	int rcread;
	std::string zSqlstring = "SELECT * FROM faces WHERE hash = '" + hash.c_str() + "'";
	const char *zSql = zSqlstring.c_str();
	sqlite3_stmt *pStmt;
	rcread = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
	rcread = sqlite3_step(pStmt);
	int facescount = 0;
	while (rcread == SQLITE_ROW)
	{
		Face tempface;
		int id = sqlite3_column_int(pStmt, 0);
		tempface.db_id = id;
		int left = sqlite3_column_int(pStmt, 2);
		int right = sqlite3_column_int(pStmt, 3);
		int top = sqlite3_column_int(pStmt, 4);
		int bottom = sqlite3_column_int(pStmt, 5);
		dlib::rectangle rect(left, top, right, bottom);
		tempface.face_rect = rect;
		std::string name;
		if (sqlite3_column_type(pStmt, 6) == SQLITE_NULL)
			name = "";
		else
			name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(pStmt, 6)));

		tempface.person_name = name;
		faces.push_back(tempface);
		rcread = sqlite3_step(pStmt);
		facescount++;
	}
	rcread = sqlite3_finalize(pStmt);
}

void wxFacePanel::mouseDown(wxMouseEvent& event) {
	
	for (int i = 0; i < faces.size(); i++)
	{
		if (XCoord + (int)(scale * faces[i].face_rect.left()) < event.GetX() && XCoord + (int)(scale * faces[i].face_rect.right()) > event.GetX() && YCoord + (int)(scale * faces[i].face_rect.top()) < event.GetY() && YCoord + (int)(scale * faces[i].face_rect.bottom()) > event.GetY())
		{
			wxRect m_rect;
			
			m_rect.SetLeft(faces[i].face_rect.left() <= 0 ? 1 : faces[i].face_rect.left());
			m_rect.SetRight(faces[i].face_rect.right() >= image.GetWidth() ? image.GetWidth()-1 : faces[i].face_rect.right());
			m_rect.SetTop(faces[i].face_rect.top() <= 0 ? 1 : faces[i].face_rect.top());
			m_rect.SetBottom(faces[i].face_rect.bottom() >= image.GetHeight() ? image.GetHeight()-1 : faces[i].face_rect.bottom());

			FacenameDialog dlg(this, image.GetSubImage(m_rect), faces[i].person_name);
			if (dlg.ShowModal() == wxID_OK)
			{
				sqlite3 *db;
				wxString dbname = "empirika.db";
				int rc = sqlite3_open(dbname, &db);
				std::string zSqlwritestring = "UPDATE faces SET fname = '" 
					+ dlg.m_textCtrl->GetValue().ToStdString() + "' "
					+ "WHERE id = '"	+ std::to_string(faces[i].db_id) + "'";
				const char *zSqlwrite = zSqlwritestring.c_str();
				sqlite3_stmt *pStmtwrite;
				int rcwrite;
				rcwrite = sqlite3_prepare(db, zSqlwrite, -1, &pStmtwrite, 0);
				rcwrite = sqlite3_step(pStmtwrite);
				sqlite3_finalize(pStmtwrite);
				sqlite3_close(db);
				ResetFaces();
				paintNow();
			}
			else
			{
				//wxMessageBox("Cancel");
			}		
		}
	}
	event.Skip();
}
