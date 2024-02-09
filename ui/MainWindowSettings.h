#ifndef __MainWindowSettings__
#define __MainWindowSettings__

/**
@file
Subclass of Settings, which is generated by wxFormBuilder.
*/

#include "MainWindow.h"

//// end generated include
#include "ver.hpp"
#include "utils.hpp"
#include "../cores.h"

#include <wx/fileconf.h>
#include <wx/stdpaths.h>

/** Implementing Settings */
class MainWindowSettings : public Settings
{
	protected:
		// Handlers for Settings events.
		void onSave( wxCommandEvent& event );
	public:
		/** Constructor */
		MainWindowSettings( wxWindow* parent );
	//// end generated class members
private:
	void InitConfig();
	wxFileConfig *fileConfig;
	sd_gui_utils::config *cfg;
	std::string ini_path;



};

#endif // __MainWindowSettings__
