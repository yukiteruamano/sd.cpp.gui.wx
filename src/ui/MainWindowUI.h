#ifndef __MainWindowUI__
#define __MainWindowUI__

/**
@file
Subclass of UI, which is generated by wxFormBuilder.
*/

#include "MainWindow.h"

//// end generated include
/// generated by chalet from ./ver.hpp.in
#include "../helpers/wildcards.hpp"
#include "../helpers/simplecurl.h"
#include "../libs/cores.h"
#include "MainWindowSettings.h"
#include "ModelInfo.h"
#include "QueueManager.h"
#include "ver.hpp"

#include <bitset>
#include <cctype>
#include <cinttypes>
#include <filesystem>
#include <fstream>
#include <map>
#include <mutex>
#include <thread>
#include <vector>

#include "../helpers/sd.hpp"
#include "utils.hpp"

#include "MainWindowAboutDialog.h"
#include "MainWindowCivitAiWindow.h"
#include "MainWindowImageDialog.h"

#include <wx/display.h>
#include <wx/dynlib.h>
#include <wx/event.h>
#include <wx/fileconf.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/notifmsg.h>
#include <wx/splash.h>
#include <wx/sstream.h>
#include <wx/stdpaths.h>
#include <wx/taskbar.h>
#include <wx/textdlg.h>
#include <wx/tokenzr.h>
#include <wx/webrequest.h>
#include <exiv2/exiv2.hpp>

#include <wx/persist/toplevel.h>

#include "embedded_files/app_icon.h"
#include "embedded_files/splash_image.h"

/** Implementing UI */
class MainWindowUI : public mainUI {
protected:
    // Handlers for UI events.
    void onSettings(wxCommandEvent& event);
    void onModelsRefresh(wxCommandEvent& event);
    void OnAboutButton(wxCommandEvent& event);
    void OnCivitAitButton(wxCommandEvent& event);
    void onModelSelect(wxCommandEvent& event);
    void onTypeSelect(wxCommandEvent& event);
    void onVaeSelect(wxCommandEvent& event);
    void onSamplerSelect(wxCommandEvent& event);
    void onRandomGenerateButton(wxCommandEvent& event);
    void OnWHChange(wxSpinEvent& event);
    void onResolutionSwap(wxCommandEvent& event);
    void onSavePreset(wxCommandEvent& event);
    void onLoadPreset(wxCommandEvent& event);
    void onSelectPreset(wxCommandEvent& event);
    void onDeletePreset(wxCommandEvent& event);
    void m_notebook1302OnNotebookPageChanged(wxNotebookEvent& event);
    void onJobsStart(wxCommandEvent& event);
    void onJobsPause(wxCommandEvent& event);
    void onJobsDelete(wxCommandEvent& event);
    void OnJobListItemActivated(wxDataViewEvent& event);
    void onContextMenu(wxDataViewEvent& event);
    void OnJobListItemSelection(wxDataViewEvent& event);
    void onTxt2ImgFileDrop(wxDropFilesEvent& event);
    void OnPromptText(wxCommandEvent& event);
    void OnNegPromptText(wxCommandEvent& event);
    void onGenerate(wxCommandEvent& event);
    void OnControlnetImageOpen(wxFileDirPickerEvent& event);
    void OnControlnetImagePreviewButton(wxCommandEvent& event);
    void OnControlnetImageDelete(wxCommandEvent& event);
    void Onimg2imgDropFile(wxDropFilesEvent& event);
    void OnImageOpenFileChanged(wxFileDirPickerEvent& event);
    void OnImg2ImgPreviewButton(wxCommandEvent& event);
    void OnDeleteInitialImage(wxCommandEvent& event);
    void OnUpscalerDropFile(wxDropFilesEvent& event);
    void OnImageOpenFilePickerChanged(wxFileDirPickerEvent& event);
    void OnDeleteUpscaleImage(wxCommandEvent& event);
    void OnUpscalerModelSelection(wxCommandEvent& event);
    void OnUpscalerFactorChange(wxSpinEvent& event);
    void OnCheckboxLoraFilter(wxCommandEvent& event);
    void OnCheckboxCheckpointFilter(wxCommandEvent& event);
    void OnModellistFilterKeyUp(wxKeyEvent& event);
    void OnDataModelActivated(wxDataViewEvent& event);
    void OnDataModelSelected(wxDataViewEvent& event);

public:
    /** Constructor */
    MainWindowUI(wxWindow* parent);
    //// end generated class members
    ~MainWindowUI();
    void OnThreadMessage(wxThreadEvent& e);
    void OnCivitAiThreadMessage(wxThreadEvent& e);
    void loadDll(wxDynamicLibrary* dll);

private:
    wxFileConfig* fileConfig = nullptr;
    sd_gui_utils::config* cfg;
    wxString ini_path;
    MainWindowSettings* settingsWindow;
    sd_gui_utils::SDParams* sd_params;
    std::vector<wxStaticBitmap*> modelImagePreviews;
    std::vector<wxStaticBitmap*> jobImagePreviews;
    wxDynamicLibrary* sd_dll;

    wxTaskBarIcon* TaskBar;
    wxMenu* TaskBarMenu;
    wxBitmap TaskBarIcon;

    MainWindowCivitAiWindow* civitwindow = nullptr;

    /// @brief first: model display name
    /// @brief second: model full path
    std::map<std::string, std::string> ModelFiles;
    /// @brief first: model display name
    /// @brief second: index in the selectbox
    std::map<std::string, int> ModelFilesIndex;
    std::map<std::string, std::string> VaeFiles;
    std::map<std::string, std::string> TaesdFiles;
    std::map<std::string, std::string> EsrganFiles;
    std::map<std::string, std::string> ControlnetModels;
    std::map<std::string, std::string> LoraFiles;
    std::map<std::string, std::string> EmbeddingFiles;
    std::map<std::string, sd_gui_utils::generator_preset> Presets;

    ModelInfo::Manager* ModelManager;
    wxString previousText;
    // the queue manager
    QM::QueueManager* qmanager;
    std::mutex mutex;
    std::mutex logMutex;
    bool modelLoaded        = false;
    bool upscaleModelLoaded = false;
    bool firstCfgInit       = true;
    int init_width          = 512;
    int init_height         = 512;
    std::string currentModel;
    std::string currentVaeModel;
    std::string currentTaesdModel;
    std::string currentControlnetModel;
    std::string currentUpscalerModel;
    QM::GenerationMode lastGenerationMode;
    bool currentVaeDecodeOnly;
    sd_type_t currentwType = sd_type_t::SD_TYPE_COUNT;
    wxImage* currentInitialImage;
    wxImage* currentInitialImagePreview;
    wxImage* currentControlnetImage;
    wxImage* currentControlnetImagePreview;
    wxImage* currentUpscalerSourceImage;
    std::string currentInitialImagePath;
    wxImageList* previewImageList;
    wxImageList* modelPreviewImageList;
    sd_ctx_t* txt2img_sd_ctx;
    upscaler_ctx_t* upscaler_sd_ctx;
    std::streambuf* buffer;
    std::vector<std::thread*> threads;
    wxTextAttr defaultTextCtrlStyle;
    wxBitmap ControlnetOrigPreviewBitmap;
    wxBitmap AppOrigPlaceHolderBitmap;

    // row,QueueItem
    std::map<int, QM::QueueItem*> JobTableItems;
    std::vector<sd_gui_utils::VoidHolder*> voids;

    std::atomic_bool stop_thread = false;

    void initConfig();
    void loadModelList();
    void loadLoraList();
    void loadVaeList();
    void loadTaesdList();
    void loadControlnetList();
    void loadEmbeddingList();
    void loadSamplerList();
    void loadEsrganList();
    void loadTypeList();
    void loadShcedulerList();
    void refreshModelTable(std::string filter = "");
    void OnCloseSettings(wxCloseEvent& event);
    void OnCloseCivitWindow(wxCloseEvent& event);
    void OnExit(wxEvent& event);
    void OnPopupClick(wxCommandEvent& evt);
    void LoadFileList(sd_gui_utils::DirTypes type = sd_gui_utils::DirTypes::CHECKPOINT);
    void LoadPresets();
    void ShowNotification(std::string title, std::string message);
    void ChangeModelByName(wxString ModelName);
    void ChangeModelByInfo(const sd_gui_utils::ModelFileInfo info);
    void ChangeGuiFromQueueItem(const QM::QueueItem item);
    void UpdateModelInfoDetailsFromModelList(sd_gui_utils::ModelFileInfo* modelinfo);
    void UpdateJobInfoDetailsFromJobQueueList(QM::QueueItem* item);
    static void ModelHashingCallback(size_t readed_size, std::string sha256, void* custom_pointer);
    static void ModelStandaloneHashingCallback(size_t readed_size, std::string sha256, void* custom_pointer);

    static void HandleSDLog(sd_log_level_t level, const char* text, void* data);
    static void HandleSDProgress(int step, int steps, float time, void* data);

    QM::QueueItem* handleSdImage(sd_image_t result, QM::QueueItem* itemPtr, wxEvtHandler* eventHandler);

    std::string paramsToImageComment(QM::QueueItem myItem, sd_gui_utils::ModelFileInfo modelInfo);
    void imageCommentToGuiParams(std::map<std::string, std::string> params, sd_gui_utils::SDMode mode);
    void onimg2ImgImageOpen(std::string file);
    void onUpscaleImageOpen(std::string file);
    void onControlnetImageOpen(std::string file);

    // load the model in a new thread
    sd_ctx_t* LoadModelv2(wxEvtHandler* eventHandler, QM::QueueItem* myItem);
    upscaler_ctx_t* LoadUpscaleModel(wxEvtHandler* eventHandler, QM::QueueItem* myItem);
    // generate in another thread
    void GenerateTxt2img(wxEvtHandler* eventHandler, QM::QueueItem* myItem);
    void GenerateImg2img(wxEvtHandler* eventHandler, QM::QueueItem* item);
    void GenerateUpscale(wxEvtHandler* eventHandler, QM::QueueItem* item);

    // start a thread to generate image
    void StartGeneration(QM::QueueItem* myJob);

    // handle queue managers events, manipulate data table by events
    void OnQueueItemManagerItemAdded(QM::QueueItem* item);
    void OnQueueItemManagerItemUpdated(QM::QueueItem* item);
    void OnQueueItemManagerItemStatusChanged(QM::QueueItem* item);

    template <typename T>
    static void SendThreadEvent(wxEvtHandler* eventHandler, QM::QueueEvents eventType, const T& payload, std::string text = "");

    template <typename T>
    static void SendThreadEvent(wxEvtHandler* eventHandler, sd_gui_utils::ThreadEvents eventType, const T& payload, std::string text = "");

    // generate the hash for a model, from the model table list
    void threadedModelHashCalc(wxEvtHandler* eventHandler, sd_gui_utils::ModelFileInfo* modelinfo);
    void threadedModelInfoDownload(wxEvtHandler* eventHandler, sd_gui_utils::ModelFileInfo* modelinfo);
    void threadedModelInfoImageDownload(wxEvtHandler* eventHandler, sd_gui_utils::ModelFileInfo* modelinfo);

    SdSetLogCallbackFunction sd_set_log_callback;
    SdSetProgressCallbackFunction sd_set_progress_callback;

    inline static void terminateHandler() {
        std::cout << "Assertion failure caught!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    inline void writeLog(const std::string& message) {
        std::ofstream logfile(this->cfg->datapath + "/app.log", std::ios::app);
        if (!logfile.is_open()) {
            std::cerr << "Err: can not open logfile: " << this->cfg->datapath + "/app.log" << std::endl;
            return;
        }
        std::time_t now   = std::time(nullptr);
        std::tm* timeinfo = std::localtime(&now);
        char timestamp[30];
        std::strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", timeinfo);
        std::lock_guard<std::mutex> lock(this->logMutex);
        wxString logline = wxString::Format("%s: %s", timestamp, message);
        logfile << logline.c_str();
        logfile.close();
        this->logs->AppendText(logline);
    }
    inline void writeLog(const wxString& message) {
        this->writeLog(message.ToStdString());
    }
};

#endif  // __MainWindowUI__
