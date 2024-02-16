#ifndef __MainWindowUI__
#define __MainWindowUI__

/**
@file
Subclass of UI, which is generated by wxFormBuilder.
*/

#include "MainWindow.h"

//// end generated include
#include "ver.hpp"
#include "../cores.h"
#include "MainWindowSettings.h"
#include "MainWindowImageViewer.h"
#include "QueueManager.h"

#include <filesystem>
#include <map>
#include <thread>
#include <vector>
#include <fstream>
#include <mutex>

#include <fmt/format.h>
#include "utils.hpp"
#include <stable-diffusion.h>

#include "MainWindowImageDialog.h"

#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <wx/event.h>
#include <wx/notifmsg.h>
#include <wx/textdlg.h>
#include <wx/menu.h>
#include <wx/taskbar.h>
#include <wx/msgdlg.h>

#include "embedded_files/app_icon.h"

/** Implementing UI */
class MainWindowUI : public UI
{
protected:
	// Handlers for UI events.
	void onSettings(wxCommandEvent &event);
	void onModelsRefresh(wxCommandEvent &event);
	void onModelSelect(wxCommandEvent &event);
	void onTypeSelect(wxCommandEvent &event);
	void onVaeSelect(wxCommandEvent &event);
	void onRandomGenerateButton(wxCommandEvent &event);
	void onResolutionSwap(wxCommandEvent &event);
	void onJobsStart(wxCommandEvent &event);
	void onJobsPause(wxCommandEvent &event);
	void onJobsDelete(wxCommandEvent &event);
	void onJoblistItemActivated(wxDataViewEvent &event);
	void onContextMenu(wxDataViewEvent &event);
	void onJoblistSelectionChanged(wxDataViewEvent &event);
	void onGenerate(wxCommandEvent &event);
	void OnControlnetImageOpen(wxFileDirPickerEvent &event);
	void OnControlnetImagePreviewButton(wxCommandEvent &event);
	void OnControlnetImageDelete(wxCommandEvent &event);
	void Onimg2imgDropFile(wxDropFilesEvent &event);
	void OnImageOpenFileChanged(wxFileDirPickerEvent &event);
	void OnImg2ImgPreviewButton(wxCommandEvent &event);
	void OnDeleteInitialImage(wxCommandEvent &event);
	void onSamplerSelect(wxCommandEvent &event);
	void onSavePreset(wxCommandEvent &event);
	void onLoadPreset(wxCommandEvent &event);
	void onSelectPreset(wxCommandEvent &event);
	void onDeletePreset(wxCommandEvent &event);

public:
	/** Constructor */
	MainWindowUI(wxWindow *parent);
	//// end generated class members
	~MainWindowUI();
	void OnThreadMessage(wxThreadEvent &e);

private:
	std::mutex sdMutex;
	wxFileConfig *fileConfig;
	sd_gui_utils::config *cfg;
	wxString ini_path;
	MainWindowSettings *settingsWindow;
	sd_gui_utils::SDParams *sd_params;

	wxTaskBarIcon *TaskBar;
	wxMenu *TaskBarMenu;

	/// @brief first: model display name 
	/// @brief second: model full path
	std::map<std::string, std::string> ModelFiles;
	/// @brief first: model display name
	/// @brief second: index in the selectbox
	std::map<std::string, int> ModelFilesIndex;
	std::map<std::string, std::string> VaeFiles;
	std::map<std::string, std::string> TaesdFiles;
	std::map<std::string, std::string> ControlnetModels;
	std::map<std::string, std::string> LoraFiles;
	std::map<std::string, sd_gui_utils::generator_preset> Presets;
	std::map<std::string, sd_gui_utils::ModelFileInfo> ModelInfos;

	// the queue manager
	QM::QueueManager *qmanager;
	bool modelLoaded = false;
	bool firstCfgInit = true;
	std::string currentModel;
	std::string currentVaeModel;
	std::string currentTaesdModel;
	std::string currentControlnetModel;
	sd_type_t currentwType = sd_type_t::SD_TYPE_COUNT;
	wxImage *currentInitialImage;
	wxImage *currentInitialImagePreview;
	wxImage *currentControlnetImage;
	wxImage *currentControlnetImagePreview;
	std::string currentInitialImagePath;
	sd_ctx_t *sd_ctx;
	std::streambuf *buffer;
	std::vector<std::thread *> threads;

	// row,QueueItem
	std::map<int, QM::QueueItem *> JobTableItems;
	std::map<int, wxDataViewColumn *> *JobTableColumns;

	std::atomic_bool stop_thread = false;

	void initConfig();
	void loadModelList();
	void loadLoraList();
	void loadVaeList();
	void loadTaesdList();
	void loadControlnetList();
	void loadSamplerList();
	void loadTypeList();
	void refreshModelTable();
	void OnCloseSettings(wxCloseEvent &event);
	void OnExit(wxEvent &event);
	void OnPopupClick(wxCommandEvent &evt);
	void LoadFileList(sd_gui_utils::DirTypes type = sd_gui_utils::DirTypes::CHECKPOINT);
	void LoadPresets();
	void ChangeModelByName(wxString ModelName);
	static void ModelHashingCallback(size_t readed_size, std::string sha256, void *custom_pointer);
	static void ModelStandaloneHashingCallback(size_t readed_size, std::string sha256, void *custom_pointer);

	static void HandleSDLog(sd_log_level_t level, const char *text, void *data);
	static void HandleSDProgress(int step, int steps, float time, void *data);

	// load the model in a new thread
	sd_ctx_t *LoadModelv2(wxEvtHandler *eventHandler, QM::QueueItem myItem);
	// generate in another thread
	void GenerateTxt2img(wxEvtHandler *eventHandler, QM::QueueItem myItem);
	void GenerateImg2img(wxEvtHandler *eventHandler, QM::QueueItem myItem);

	// start a thread to generate image
	void StartGeneration(QM::QueueItem myJob);

	// handle queue managers events, manipulate data table by events
	void OnQueueItemManagerItemAdded(QM::QueueItem item);
	void OnQueueItemManagerItemUpdated(QM::QueueItem item);
	void OnQueueItemManagerItemStatusChanged(QM::QueueItem item);

	// generate the hash for a model, from the model table list
	void threadedModelHashCalc(wxEvtHandler *eventHandler, sd_gui_utils::ModelFileInfo *modelinfo);
};

#endif // __MainWindowUI__
