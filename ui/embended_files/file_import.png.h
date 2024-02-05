#ifndef FILE_IMPORT_PNG_H
#define FILE_IMPORT_PNG_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char file_import_png[] =
{
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 
	0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 
	0x00, 0x00, 0x00, 0x10, 0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 
	0xF3, 0xFF, 0x61, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 
	0x73, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x76, 0x01, 
	0x4E, 0x7B, 0x26, 0x08, 0x00, 0x00, 0x00, 0x19, 0x74, 0x45, 
	0x58, 0x74, 0x53, 0x6F, 0x66, 0x74, 0x77, 0x61, 0x72, 0x65, 
	0x00, 0x77, 0x77, 0x77, 0x2E, 0x69, 0x6E, 0x6B, 0x73, 0x63, 
	0x61, 0x70, 0x65, 0x2E, 0x6F, 0x72, 0x67, 0x9B, 0xEE, 0x3C, 
	0x1A, 0x00, 0x00, 0x00, 0xCA, 0x49, 0x44, 0x41, 0x54, 0x38, 
	0x8D, 0x9D, 0xD2, 0x31, 0x6E, 0x02, 0x31, 0x10, 0x85, 0xE1, 
	0x0F, 0x44, 0x89, 0xA8, 0x39, 0x4A, 0xA2, 0x5C, 0x60, 0x05, 
	0xF5, 0xD2, 0xA6, 0x26, 0xE9, 0x38, 0x46, 0x8A, 0x6C, 0x93, 
	0x2B, 0xA4, 0x59, 0x5A, 0xC4, 0x05, 0x52, 0x04, 0x89, 0x2A, 
	0x17, 0x41, 0x51, 0x0A, 0x2A, 0x04, 0x14, 0x59, 0x4B, 0xB0, 
	0xAC, 0xBD, 0x2B, 0x9E, 0x64, 0x69, 0xE4, 0x99, 0xF7, 0x7B, 
	0xC6, 0x36, 0xFF, 0x1A, 0xE3, 0x0B, 0x07, 0x9C, 0x22, 0xEB, 
	0x88, 0x57, 0x11, 0xBD, 0x27, 0x8C, 0x75, 0xC8, 0xBC, 0x09, 
	0x50, 0x56, 0x05, 0x79, 0xE4, 0x80, 0x90, 0x0F, 0x90, 0x97, 
	0x90, 0xE8, 0xC7, 0x5A, 0x4A, 0xA8, 0x87, 0x0F, 0x3C, 0xDF, 
	0x0B, 0x08, 0x90, 0x29, 0x0C, 0x3A, 0x1A, 0x0A, 0x2C, 0xAB, 
	0xF8, 0x01, 0x8B, 0x90, 0x48, 0x01, 0x46, 0xF8, 0xAB, 0xE2, 
	0xEF, 0x58, 0x51, 0x18, 0xA1, 0xC0, 0xAC, 0x56, 0xB8, 0xC6, 
	0xB0, 0xAD, 0xB5, 0x81, 0xEB, 0x9B, 0x7F, 0xBC, 0x88, 0x9F, 
	0xB0, 0xC2, 0x04, 0xFB, 0x14, 0xA4, 0xED, 0xED, 0xDF, 0x6A, 
	0xF5, 0x79, 0xB5, 0x5F, 0x86, 0x0E, 0x96, 0x9A, 0x95, 0x63, 
	0x87, 0xCF, 0xB6, 0x11, 0x66, 0x91, 0xDC, 0x2F, 0x32, 0xFC, 
	0xA4, 0x00, 0xE1, 0x12, 0x9B, 0x7E, 0x62, 0x86, 0x6D, 0xCA, 
	0x7C, 0x09, 0x68, 0xD2, 0xA6, 0xCD, 0xCC, 0xED, 0x3F, 0x28, 
	0xBB, 0x98, 0xBA, 0x76, 0xD0, 0x49, 0x67, 0x0C, 0x18, 0x38, 
	0x64, 0xC1, 0xDF, 0xEF, 0x22, 0x00, 0x00, 0x00, 0x00, 0x49, 
	0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82, 
};

wxBitmap& file_import_png_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( file_import_png, sizeof( file_import_png ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_PNG );
	static wxBitmap bmp( image );
	return bmp;
}


#endif //FILE_IMPORT_PNG_H
