#ifndef PALETTE_PNG_H
#define PALETTE_PNG_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char palette_png[] =
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
	0x1A, 0x00, 0x00, 0x01, 0x5E, 0x49, 0x44, 0x41, 0x54, 0x38, 
	0x8D, 0x85, 0xD3, 0xBF, 0x4B, 0x57, 0x51, 0x18, 0x06, 0xF0, 
	0x8F, 0x7E, 0xA5, 0x28, 0xB4, 0xF1, 0x4B, 0x0D, 0x1A, 0x62, 
	0xA3, 0x06, 0x0D, 0x46, 0x41, 0x53, 0xA2, 0xA3, 0xE0, 0x6A, 
	0x7F, 0x82, 0xFF, 0x44, 0x4A, 0x41, 0x06, 0x41, 0x41, 0xA8, 
	0x65, 0x43, 0x84, 0x50, 0x4B, 0xD0, 0x20, 0x08, 0xA5, 0x63, 
	0x0E, 0x8E, 0xD1, 0xE0, 0x26, 0x46, 0x43, 0x2D, 0xE5, 0xA4, 
	0xE5, 0x57, 0xFB, 0x36, 0xDC, 0xE7, 0xC6, 0xE5, 0xE6, 0x8F, 
	0x07, 0x0E, 0xE7, 0x3C, 0xEF, 0x7D, 0xDE, 0xE7, 0x9C, 0xF7, 
	0x3D, 0xE7, 0xF2, 0x3F, 0xAE, 0xE0, 0x11, 0x3E, 0x61, 0x07, 
	0x7B, 0xF8, 0x8C, 0xC7, 0x18, 0x3A, 0x42, 0xFF, 0x0F, 0x5D, 
	0x98, 0x45, 0x0B, 0xED, 0x63, 0xC6, 0x01, 0x9E, 0xE2, 0x4C, 
	0x3D, 0xB9, 0x81, 0x77, 0x11, 0xFD, 0xC6, 0x1C, 0x6E, 0xA2, 
	0x1B, 0xE7, 0x30, 0x8C, 0x27, 0xF8, 0x15, 0xCD, 0x1A, 0xCE, 
	0x56, 0x0D, 0xEE, 0xE7, 0xC3, 0xB7, 0x88, 0x8F, 0xC3, 0x10, 
	0xB6, 0xA3, 0x9D, 0x2F, 0x83, 0xFD, 0x71, 0x6E, 0xE1, 0x3A, 
	0x9A, 0xD8, 0xCC, 0x68, 0x46, 0x33, 0x91, 0x7E, 0x2C, 0x62, 
	0x10, 0xBB, 0x38, 0xC4, 0x35, 0xB8, 0x1B, 0xC7, 0x17, 0x11, 
	0x8F, 0x56, 0x6A, 0x1E, 0x4D, 0x6C, 0x31, 0xFC, 0x67, 0xF8, 
	0xC3, 0xF0, 0x05, 0xF8, 0x18, 0x72, 0xBB, 0xD2, 0x8F, 0x19, 
	0x4C, 0x67, 0x5D, 0x9E, 0xF2, 0x39, 0xC6, 0xC3, 0x07, 0x93, 
	0xB3, 0x05, 0x5F, 0x43, 0x2E, 0x9E, 0x50, 0x7B, 0x1D, 0x0D, 
	0xEC, 0xE3, 0xA0, 0x13, 0x7F, 0x6A, 0x1F, 0x9B, 0x18, 0xAB, 
	0xEC, 0x5E, 0xE2, 0x12, 0x6E, 0x64, 0xEE, 0xCA, 0xE8, 0x80, 
	0xF5, 0x9C, 0x60, 0x24, 0xC2, 0xCD, 0xF0, 0x99, 0xF0, 0x0B, 
	0x58, 0x52, 0x34, 0xAD, 0x9D, 0x0D, 0xDF, 0x67, 0xFD, 0xA5, 
	0x13, 0x1F, 0x22, 0x9C, 0xCC, 0xDC, 0xAE, 0xCD, 0x4B, 0xB8, 
	0xA3, 0x78, 0x1F, 0x1B, 0x8A, 0x1B, 0x28, 0x9B, 0xBB, 0x06, 
	0x7D, 0x8A, 0x6B, 0xDC, 0xCF, 0x11, 0x9B, 0x11, 0x34, 0x70, 
	0x35, 0x46, 0x3F, 0x30, 0x90, 0xA4, 0x5E, 0xBC, 0xC5, 0x0A, 
	0x2E, 0x97, 0xF5, 0xDD, 0x8B, 0xF0, 0xBB, 0xE2, 0x2D, 0x94, 
	0x98, 0x4C, 0xFC, 0xB5, 0x53, 0x50, 0x7D, 0xCA, 0x2D, 0x3C, 
	0xC3, 0x2D, 0x4C, 0x25, 0xF6, 0xF2, 0x34, 0x83, 0xD2, 0xE4, 
	0x41, 0x4A, 0xA9, 0xFF, 0x44, 0xAF, 0x4E, 0x4A, 0x2A, 0xD1, 
	0xC6, 0x2A, 0xDE, 0x28, 0x7A, 0xD2, 0x83, 0xF3, 0xD1, 0x6C, 
	0x60, 0xF9, 0x28, 0x83, 0xBF, 0x72, 0x9A, 0x66, 0x32, 0x3D, 
	0x34, 0xCD, 0x90, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 
	0x44, 0xAE, 0x42, 0x60, 0x82, 
};

wxBitmap& palette_png_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( palette_png, sizeof( palette_png ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_PNG );
	static wxBitmap bmp( image );
	return bmp;
}


#endif //PALETTE_PNG_H
