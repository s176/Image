#pragma once

#include <dlib/image_processing/frontal_face_detector.h>

struct Face
{
	int db_id;
	std::string person_name;
	dlib::rectangle face_rect;
};