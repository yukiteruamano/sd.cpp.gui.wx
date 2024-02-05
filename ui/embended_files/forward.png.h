#ifndef FORWARD_PNG_H
#define FORWARD_PNG_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char forward_png[] =
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
	0x1A, 0x00, 0x00, 0x00, 0xB0, 0x49, 0x44, 0x41, 0x54, 0x38, 
	0x8D, 0xCD, 0xD2, 0x31, 0x8E, 0x41, 0x61, 0x14, 0xC5, 0xF1, 
	0x1F, 0x95, 0x68, 0x2C, 0xC2, 0x24, 0xAC, 0x40, 0xC4, 0x0A, 
	0x2C, 0x43, 0x3B, 0x51, 0xD8, 0x81, 0x8E, 0x44, 0xAD, 0x54, 
	0xA9, 0x45, 0x42, 0xA5, 0x52, 0xD1, 0x8F, 0x0D, 0x4C, 0x63, 
	0x07, 0x93, 0x0C, 0x85, 0xC2, 0xD3, 0x90, 0x7C, 0x5E, 0xDE, 
	0x43, 0xDE, 0x2B, 0x38, 0xC9, 0x6D, 0xCE, 0x77, 0xEE, 0x3F, 
	0x37, 0x5F, 0x0E, 0x9F, 0xA0, 0x32, 0x06, 0x58, 0x63, 0x84, 
	0x4A, 0xF0, 0xD6, 0xC2, 0x1C, 0x4B, 0xB4, 0xD3, 0x00, 0x53, 
	0x44, 0xC1, 0xFC, 0xA2, 0x81, 0x2F, 0x1C, 0x03, 0xFF, 0x8C, 
	0x31, 0x4A, 0x71, 0xC0, 0x21, 0x06, 0x88, 0x70, 0xC2, 0x36, 
	0xC1, 0x8F, 0xB0, 0x43, 0x3D, 0x04, 0x24, 0x85, 0x9E, 0xCD, 
	0x3F, 0x3A, 0x50, 0xB8, 0x1A, 0x59, 0xD5, 0xCD, 0x0B, 0xD8, 
	0x17, 0x73, 0x2C, 0xC3, 0x39, 0xEF, 0x05, 0xDF, 0x64, 0xFB, 
	0xC4, 0x23, 0x7A, 0x37, 0xCA, 0x5F, 0x42, 0xE0, 0x84, 0x4D, 
	0xCA, 0xF2, 0x0F, 0x6A, 0xE1, 0x19, 0x93, 0x58, 0xE0, 0x56, 
	0xA4, 0xAA, 0x17, 0x8B, 0x54, 0x42, 0x1F, 0x2B, 0x0C, 0xDD, 
	0x57, 0xB9, 0x89, 0x19, 0x16, 0x1E, 0x54, 0xF9, 0xBD, 0xBA, 
	0x00, 0xCE, 0x45, 0x55, 0xC1, 0x08, 0x9C, 0xBC, 0x95, 0x00, 
	0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 
	0x82, 
};

wxBitmap& forward_png_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( forward_png, sizeof( forward_png ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_PNG );
	static wxBitmap bmp( image );
	return bmp;
}


#endif //FORWARD_PNG_H
