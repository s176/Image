#include "libraw/libraw.h"
#include <wx/mstream.h>
#include "wx/filename.h"
#include "FaceDlg.h"

FaceDlg::FaceDlg(wxWindow * parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style)
{
	wxBoxSizer* bSizer = new wxBoxSizer(wxHORIZONTAL);
	drawPane = new wxFacePanel(this);
	drawPane->SetBackgroundColour(*wxBLACK);
	bSizer->Add(drawPane, 1, wxEXPAND);
	SetSizer(bSizer);
	Centre(wxBOTH);
}

void FaceDlg::SetImage()
{
	wxImage image;
	image.LoadFile(filename);
	faces.clear();
	drawPane->faces.clear();
	drawPane->hash = hash;
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

	if (facescount == 0)
	{
		wxBusyCursor busy;
		dlib::array2d<dlib::rgb_pixel> dlibImage;
		dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
		dlib::load_image(dlibImage, std::string(filename.mb_str()));
		std::vector<dlib::rectangle> dets;
		dets = detector(dlibImage);
		for (int i = 0; i < dets.size(); i++)
		{
			std::string zSqlwritestring = "INSERT INTO faces(hash, fleft, fright, ftop, fbottom) VALUES('"
				+ hash.c_str() + "', "
				+ std::to_string(dets[i].left()) + ", "
				+ std::to_string(dets[i].right()) + ", "
				+ std::to_string(dets[i].top()) + ", "
				+ std::to_string(dets[i].bottom()) + ")";
			const char *zSqlwrite = zSqlwritestring.c_str();
			sqlite3_stmt *pStmtwrite;
			int rcwrite;
			rcwrite = sqlite3_prepare(db, zSqlwrite, -1, &pStmtwrite, 0);
			rcwrite = sqlite3_step(pStmtwrite);
		}
		if (dets.size() > 0)
			SetImage();
	}

	if (faces.size() > 0)
	{
		drawPane->faces = faces;
	}
	else
	{
		wxMessageBox("No faces found");
	}
	drawPane->SetImage(image);
};


