#ifndef __MainWindowUI__
#define __MainWindowUI__

/**
@file
Subclass of UI, which is generated by wxFormBuilder.
*/

#include "../helpers/simplecurl.h"
#include "../helpers/sslUtils.hpp"
#include "MainWindowAboutDialog.h"
#include "MainWindowDesktopWidget.h"
#include "MainWindowImageDialog.h"

class MainApp;

/** Implementing UI */
class MainWindowUI : public mainUI {
protected:
    // Handlers for UI events.
    void onSettings(wxCommandEvent& event) override;
    void onModelsRefresh(wxCommandEvent& event) override;
    void OnAboutButton(wxCommandEvent& event) override;
    void OnCivitAitButton(wxCommandEvent& event) override;
    void OnStopBackgroundProcess(wxCommandEvent& event) override;
    void onModelSelect(wxCommandEvent& event) override;
    void onTypeSelect(wxCommandEvent& event) override;
    void onVaeSelect(wxCommandEvent& event) override;
    void onSamplerSelect(wxCommandEvent& event) override;
    void onRandomGenerateButton(wxCommandEvent& event) override;
    void onSd15ResSelect(wxCommandEvent& event) override;
    void onSdXLResSelect(wxCommandEvent& event) override;
    void OnWHChange(wxSpinEvent& event) override;
    void onResolutionSwap(wxCommandEvent& event) override;
    void onSavePreset(wxCommandEvent& event) override;
    void onLoadPreset(wxCommandEvent& event) override;
    void onSelectPreset(wxCommandEvent& event) override;
    void onDeletePreset(wxCommandEvent& event) override;
    void m_notebook1302OnNotebookPageChanged(wxNotebookEvent& event) override;
    void onJobsStart(wxCommandEvent& event) override;
    void onJobsPause(wxCommandEvent& event) override;
    void onJobsDelete(wxCommandEvent& event) override;
    void OnJobListItemActivated(wxDataViewEvent& event) override;
    void onContextMenu(wxDataViewEvent& event) override;
    void OnJobListItemSelection(wxDataViewEvent& event) override;
    void onTxt2ImgFileDrop(wxDropFilesEvent& event) override;
    void OnPromptText(wxCommandEvent& event) override;
    void OnNegPromptText(wxCommandEvent& event) override;
    void onGenerate(wxCommandEvent& event) override;
    void OnControlnetImageOpen(wxFileDirPickerEvent& event) override;
    void OnControlnetImagePreviewButton(wxCommandEvent& event) override;
    void OnControlnetImageDelete(wxCommandEvent& event) override;
    void onFilePickerDiffusionModel(wxFileDirPickerEvent& event) override;
    void onFilePickerClipL(wxFileDirPickerEvent& event) override;
    void onFilePickerT5XXL(wxFileDirPickerEvent& event) override;
    void onCleanDiffusionModel(wxCommandEvent& event) override;
    void Onimg2imgDropFile(wxDropFilesEvent& event) override;
    void OnImageOpenFileChanged(wxFileDirPickerEvent& event) override;
    void OnImg2ImgPreviewButton(wxCommandEvent& event) override;
    void OnDeleteInitialImage(wxCommandEvent& event) override;
    void OnUpscalerDropFile(wxDropFilesEvent& event) override;
    void OnImageOpenFilePickerChanged(wxFileDirPickerEvent& event) override;
    void OnDeleteUpscaleImage(wxCommandEvent& event) override;
    void OnUpscalerModelSelection(wxCommandEvent& event) override;
    void OnUpscalerFactorChange(wxSpinEvent& event) override;
    void OnCheckboxLoraFilter(wxCommandEvent& event) override;
    void OnCheckboxCheckpointFilter(wxCommandEvent& event) override;
    void OnModellistFilterKeyUp(wxKeyEvent& event) override;
    void OnDataModelActivated(wxDataViewEvent& event) override;
    void OnDataModelSelected(wxDataViewEvent& event) override;
    void onCnOnCpu(wxCommandEvent& event) override;
    void onClipOnCpu(wxCommandEvent& event) override;
    void onVAEOnCpu(wxCommandEvent& event) override;
    void onDiffusionFlashAttn(wxCommandEvent& event) override;
    void OnImageInfoOpen(wxFileDirPickerEvent& event) override;
    void OnCleanImageInfo(wxCommandEvent& event) override;
    void OnImageInfoLoadTxt2img(wxCommandEvent& event) override;
    void OnImageInfoLoadImg2img(wxCommandEvent& event) override;
    void OnShowWidget(wxCommandEvent& event) override;
    // painting on img2img
    void OnImg2ImgMouseDown(wxMouseEvent& event) override;
    void OnImg2ImgMouseUp(wxMouseEvent& event) override;
    void OnImg2ImgMouseMotion(wxMouseEvent& event) override;
    void OnImg2ImgPaint(wxPaintEvent& event) override;
    //void OnImg2ImgMouseEnter(wxMouseEvent& event) override;
    void OnImg2ImgMouseLeave(wxMouseEvent& event) override;
    void OnImg2ImgMouseWheel(wxMouseEvent& event) override;
    void OnInpaintSaveMask(wxCommandEvent& event) override;
    void OnInpaintResizeImage(wxCommandEvent& event) override;

public:
    /** Constructor */
    MainWindowUI(wxWindow* parent, const std::string dllName, const std::string& usingBackend, bool disableExternalProcessHandling, MainApp* mapp);
    //// end generated class members
    ~MainWindowUI();
    void OnThreadMessage(wxThreadEvent& e);
    void OnCivitAiThreadMessage(wxThreadEvent& e);

private:
    MainApp* mapp = nullptr;

    bool disableExternalProcessHandling               = false;
    std::atomic<unsigned int> jobsCountSinceSegfault  = {0};
    std::atomic<unsigned int> stepsCountSinceSegfault = {0};
    std::string usingBackend;

    std::vector<wxStaticBitmap*> modelImagePreviews;
    std::vector<wxStaticBitmap*> jobImagePreviews;

    wxTaskBarIcon* TaskBar;
    wxMenu* TaskBarMenu;
    wxBitmap TaskBarIcon;

    MainWindowDesktopWidget* widget      = nullptr;
    MainWindowCivitAiWindow* civitwindow = nullptr;
    MainWindowAboutDialog* aboutDialog   = nullptr;
    MainWindowSettings* settingsWindow   = nullptr;

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

    std::shared_ptr<ModelInfo::Manager> ModelManager;
    std::shared_ptr<QM::QueueManager> qmanager;
    std::mutex mutex;
    std::mutex logMutex;
    std::mutex taskBarMutex;

    int init_width  = 512;
    int init_height = 512;

    std::shared_ptr<wxImageList> previewImageList;
    std::vector<std::thread*> threads;
    wxBitmap ControlnetOrigPreviewBitmap;
    wxBitmap AppOrigPlaceHolderBitmap;

    std::vector<sd_gui_utils::VoidHolder*> voids;
    struct subprocess_s* subprocess = nullptr;

    std::atomic<bool> extProcessNeedToRun = true;
    wxString extprocessCommand;
    wxString extProcessParam;
    wxString extprocessLastError;

    wxPoint onImg2ImgPaintLastPos; 
    bool onImg2ImgPaintIsDrawing; 
    wxBitmap inpaintBitMap;
    wxImage inpaintOrigImage;
    wxImage inpaintZoomedImage;
    double inpaintZoomFactor = 1.0;
    const double inpaintZoomFactorStep = 0.1;
    int inpaintBrushSize = 10;

    // std::ofstream logfile;
    wxFile logfile;
    std::unordered_map<wxString, wxString> lastImageInfoParams;

    void loadModelList();
    void loadLoraList();
    void loadVaeList();
    void loadTaesdList();
    void loadControlnetList();
    void loadEmbeddingList();
    void loadSamplerList();
    void loadEsrganList();
    void loadTypeList();
    void loadSchedulerList();
    void refreshModelTable(const wxString& filter = wxEmptyString);
    void OnCloseSettings(wxCloseEvent& event);
    void OnCloseCivitWindow(wxCloseEvent& event);
    void OnHtmlLinkClicked(wxHtmlLinkEvent& event) override;
    void onWhatIsThis(wxCommandEvent& event) override;
    void OnExit(wxEvent& event);
    void OnPopupClick(wxCommandEvent& evt);
    void LoadFileList(sd_gui_utils::DirTypes type = sd_gui_utils::DirTypes::CHECKPOINT);
    void LoadPresets();
    void ShowNotification(const wxString& title, const wxString& message);
    void ChangeModelByName(wxString ModelName);
    void ChangeModelByInfo(const sd_gui_utils::ModelFileInfo info);
    void ChangeGuiFromQueueItem(const QM::QueueItem item);
    void UpdateModelInfoDetailsFromModelList(sd_gui_utils::ModelFileInfo* modelinfo);
    void UpdateJobInfoDetailsFromJobQueueList(std::shared_ptr<QM::QueueItem> item);
    bool ProcessEventHandler(std::string msg);
    void ProcessCheckThread();
    void ProcessOutputThread();
    void ProcessStdOutEvent(const char* bytes, size_t n);
    void ProcessStdErrEvent(const char* bytes, size_t n);
    void UpdateCurrentProgress(std::shared_ptr<QM::QueueItem> item, const QM::QueueEvents& event);
    void SetSchedulerByType(schedule_t schedule);
    void SetSamplerByType(sample_method_t sampler);
    void SetTypeByType(sd_type_t type);
    inline void DisableControlNet() {
        this->m_controlnetModels->Disable();
        this->m_controlnetModels->Select(0);
        this->m_controlnetImageDelete->Disable();
        this->m_controlnetImageOpen->Disable();
        this->m_controlnetStrength->Disable();
        this->m_controlnetImageOpen->SetPath("");
        auto origSize = this->m_controlnetImagePreview->GetSize();
        this->m_controlnetImagePreview->SetBitmap(this->ControlnetOrigPreviewBitmap);
        this->m_controlnetImagePreview->SetSize(origSize);
        this->m_controlnetImagePreviewButton->Disable();
    };

    inline void EnableControlNet() {
        this->m_controlnetModels->Enable();
        this->m_controlnetImageDelete->Enable();
        this->m_controlnetImageOpen->Enable();
        this->m_controlnetStrength->Enable();
    };

    inline void DisableModelSelect() {
        this->m_model->Select(0);
        this->m_model->Disable();
    }
    inline void EnableModelSelect() { this->m_model->Enable(); }

    std::shared_ptr<std::thread> processCheckThread   = nullptr;
    std::shared_ptr<std::thread> processHandleOutput  = nullptr;
    std::atomic_bool extProcessRunning                = false;
    std::shared_ptr<SharedMemoryManager> sharedMemory = nullptr;

    static void ModelHashingCallback(size_t readed_size, std::string sha256, void* custom_pointer);
    static void ModelStandaloneHashingCallback(size_t readed_size, std::string sha256, void* custom_pointer);

    // std::shared_ptr<QM::QueueItem> handleSdImage(std::string result, std::shared_ptr<QM::QueueItem> itemPtr, wxEvtHandler* eventHandler);
    std::shared_ptr<QM::QueueItem> handleSdImage(const std::string& tmpImagePath, std::shared_ptr<QM::QueueItem> itemPtr, wxEvtHandler* eventHandler);

    wxString paramsToImageComment(const QM::QueueItem& myItem);
    std::string paramsToImageCommentJson(QM::QueueItem myItem, sd_gui_utils::ModelFileInfo modelInfo);
    void imageCommentToGuiParams(std::unordered_map<wxString, wxString> params, SDMode mode);
    void onimg2ImgImageOpen(const wxString& file);
    void onUpscaleImageOpen(const wxString& file);
    void onControlnetImageOpen(const wxString& file);

    void readMetaDataFromImage(const wxFileName& file, const SDMode mode, bool askForLoadParameters = false);
    std::unordered_map<wxString, wxString> getMetaDataFromImage(const wxFileName& file);

    // clean up image informations
    void cleanUpImageInformations();

    void PrepareModelConvert(sd_gui_utils::ModelFileInfo* modelInfo);

    // start a thread to generate image
    void StartGeneration(std::shared_ptr<QM::QueueItem> myJob);

    // handle queue managers events, manipulate data table by events
    void OnQueueItemManagerItemAdded(std::shared_ptr<QM::QueueItem> item);
    void OnQueueItemManagerItemUpdated(std::shared_ptr<QM::QueueItem> item);
    void OnQueueItemManagerItemStatusChanged(std::shared_ptr<QM::QueueItem> item);

    template <typename T>
    static void SendThreadEvent(wxEvtHandler* eventHandler, QM::QueueEvents eventType, const T& payload, std::string text = "");

    template <typename T>
    static void SendThreadEvent(wxEvtHandler* eventHandler, sd_gui_utils::ThreadEvents eventType, const T& payload, std::string text = "");

    template <typename T>
    void SendThreadEvent(sd_gui_utils::ThreadEvents eventType, const T& payload, std::string text = "");

    // generate the hash for a model, from the model table list
    void threadedModelHashCalc(wxEvtHandler* eventHandler, sd_gui_utils::ModelFileInfo* modelinfo);
    void threadedModelInfoDownload(wxEvtHandler* eventHandler, sd_gui_utils::ModelFileInfo* modelinfo);
    void threadedModelInfoImageDownload(wxEvtHandler* eventHandler, sd_gui_utils::ModelFileInfo* modelinfo);

    void initLog();
    void deInitLog();
    void writeLog(const wxString& msg, bool writeIntoGui = true);
    void writeLog(const std::string& message);

    SdSetLogCallbackFunction sd_set_log_callback;
    SdSetProgressCallbackFunction sd_set_progress_callback;

    inline static wxString formatFileName(const QM::QueueItem& item, const wxString& format = "[mode]_[jobid]_[seed]_[width]x[height]_[batch]") {
        wxDateTime localTime = wxDateTime::Now();

        auto day = localTime.Format(wxT("%d"));

        std::unordered_map<std::string, std::string> tags = {
            {"[year]", std::to_string(localTime.GetYear())},
            {"[month]", std::to_string(1 + localTime.GetMonth())},
            {"[day]", day.utf8_string()},
            {"[hours]", std::to_string(localTime.GetHour())},
            {"[minutes]", std::to_string(localTime.GetMinute())},
            {"[seconds]", std::to_string(localTime.GetSecond())},
            {"[finished_at]", std::to_string(item.finished_at)},
            {"[created_at]", std::to_string(item.created_at)},
            {"[updated_at]", std::to_string(item.updated_at)},
            {"[jobid]", std::to_string(item.id)},
            {"[seed]", std::to_string(item.params.seed)},
            {"[batch]", std::to_string(item.params.batch_count)},
            {"[width]", std::to_string(item.params.width)},
            {"[height]", std::to_string(item.params.height)},
            {"[mode]", modes_str[item.mode]},
            {"[model]", item.model},
            {"[model_sha256]", item.sha256},
            {"[steps]", std::to_string(item.step)},
            {"[steps_total]", std::to_string(item.steps)},
            {"[cfg_scale]", std::to_string(item.params.cfg_scale)},
            {"[denoising_strength]", std::to_string(item.params.strength)},
        };

        wxString result = format;

        for (const auto& [tag, value] : tags) {
            size_t pos = 0;
            while ((pos = result.find(tag, pos)) != std::string::npos) {
                result.replace(pos, tag.length(), value);
                pos += value.length();
            }
        }

        return result;
    }
};

#endif  // __MainWindowUI__
