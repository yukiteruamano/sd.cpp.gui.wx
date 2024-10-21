#ifndef __SD_GUI_QUEUE_MANAGER
#define __SD_GUI_QUEUE_MANAGER

#include <chrono>
#include <fstream>
#include <map>
#include "utils.hpp"

#include <wx/event.h>
#include <wx/window.h>

namespace QM {
    enum QueueStatus {
        PENDING,
        RUNNING,
        PAUSED,
        FAILED,
        MODEL_LOADING,
        DONE,
        HASHING
    };

    enum GenerationMode {
        TXT2IMG,
        IMG2IMG,
        CONVERT,
        UPSCALE
    };

    inline const char* QueueStatus_str[] = {
        "pending",
        "running",
        "paused",
        "failed",
        "model loading...",
        "finished",
        "model hashing..."};

    /// @brief Event commands to inter thread communication
    enum class QueueEvents : unsigned int {
        ITEM_DELETED            = 1 << 0,
        ITEM_ADDED              = 1 << 1,
        ITEM_STATUS_CHANGED     = 1 << 2,
        ITEM_UPDATED            = 1 << 3,
        ITEM_START              = 1 << 4,
        ITEM_FINISHED           = 1 << 5,
        ITEM_MODEL_LOAD_START   = 1 << 6,
        ITEM_MODEL_LOADED       = 1 << 7,
        ITEM_MODEL_FAILED       = 1 << 8,
        ITEM_GENERATION_STARTED = 1 << 9,
        ITEM_FAILED             = 1 << 10,
        SD_MESSAGE              = 1 << 11
    };

    enum class QueueItemImageType : unsigned int {
        /// @brief The image is generated by diffusion
        GENERATED = 1 << 0,
        /// @brief The image is added by user into the controlnet
        CONTROLNET = 1 << 1,
        /// @brief This is an itial image (eg. img2img original image, or upscaler original image)
        INITIAL = 1 << 2,
        UNKNOWN = 1 << 3
    };

    inline const std::unordered_map<QM::QueueEvents, std::string> QueueEvents_str = {
        {QM::QueueEvents::ITEM_DELETED, "ITEM_DELETED"},
        {QM::QueueEvents::ITEM_ADDED, "ITEM_ADDED"},
        {QM::QueueEvents::ITEM_STATUS_CHANGED, "ITEM_STATUS_CHANGED"},
        {QM::QueueEvents::ITEM_UPDATED, "ITEM_UPDATED"},
        {QM::QueueEvents::ITEM_START, "ITEM_START"},
        {QM::QueueEvents::ITEM_FINISHED, "ITEM_FINISHED"},
        {QM::QueueEvents::ITEM_MODEL_LOAD_START, "ITEM_MODEL_LOAD_START"},
        {QM::QueueEvents::ITEM_MODEL_LOADED, "ITEM_MODEL_LOADED"},
        {QM::QueueEvents::ITEM_MODEL_FAILED, "ITEM_MODEL_FAILED"},
        {QM::QueueEvents::ITEM_GENERATION_STARTED, "ITEM_GENERATION_STARTED"},
        {QM::QueueEvents::ITEM_FAILED, "ITEM_FAILED"},
        {QM::QueueEvents::SD_MESSAGE, "SD_MESSAGE"}};

    inline std::unordered_map<QM::QueueItemImageType, std::string> QueueItemImageType_str = {
        {QM::QueueItemImageType::GENERATED, "Generated"},
        {QM::QueueItemImageType::CONTROLNET, "Controlnet"},
        {QM::QueueItemImageType::INITIAL, "Initial"},
        {QM::QueueItemImageType::INITIAL, "Unknown"}};

    /// @brief Store the images from the queue jobs
    struct QueueItemImage {
        std::string pathname;
        QueueItemImageType type = QM::QueueItemImageType::GENERATED;
        long id                 = -1;

        QueueItemImage() = default;

        QueueItemImage(const QueueItemImage& other)
            : pathname(other.pathname), type(other.type), id(other.id) {}
        QueueItemImage(std::string pathname_, QM::QueueItemImageType type_ = QM::QueueItemImageType::GENERATED, long id_ = -1)
            : pathname(pathname_), type(type_), id(id_) {}
        QueueItemImage& operator=(const QueueItemImage& other) {
            if (this == &other) {
                return *this;
            }

            pathname = other.pathname;
            type     = other.type;
            id       = other.id;
            return *this;
        }

        bool operator==(const QueueItemImage& other) const {
            return (pathname == other.pathname);
        }
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(QueueItemImage, pathname, type)
    inline void to_json(nlohmann::json& j, const QueueItemImage* item) {
        if (item) {
            j = nlohmann::json{{"pathname", sd_gui_utils::UnicodeToUTF8(item->pathname)}, {"type", item->type}};
        } else {
            j = nullptr;
        }
    }

    inline void from_json(const nlohmann::json& j, QueueItemImage*& item) {
        if (!j.is_null()) {
            item = new QueueItemImage();
            j.at("pathname").get_to(item->pathname);
            j.at("type").get_to(item->type);
        } else {
            item = nullptr;
        }
    }

    struct QueueItem {
        int id = 0, created_at = 0, updated_at = 0, finished_at = 0, started_at = 0;
        sd_gui_utils::SDParams params;
        QM::QueueStatus status = QM::QueueStatus::PENDING;
        std::vector<QM::QueueItemImage*> images;
        int step = 0, steps = 0;
        size_t hash_fullsize = 0, hash_progress_size = 0;
        float time = 0;
        std::string model;
        QM::GenerationMode mode = QM::GenerationMode::TXT2IMG;
        std::string initial_image;
        std::string status_message = "";
        uint32_t upscale_factor    = 4;
        std::string sha256;

        QueueItem() = default;
        QueueItem(const QueueItem& other)
            : id(other.id), created_at(other.created_at), updated_at(other.updated_at), finished_at(other.finished_at), started_at(other.started_at), params(other.params), status(other.status), images(other.images), step(other.step), steps(other.steps), hash_fullsize(other.hash_fullsize), hash_progress_size(other.hash_progress_size), time(other.time), model(other.model), mode(other.mode), initial_image(other.initial_image), status_message(other.status_message), upscale_factor(other.upscale_factor), sha256(other.sha256) {}

        ~QueueItem() {}

        QueueItem& operator=(const QueueItem& other) {
            if (this != &other) {
                id                 = other.id;
                created_at         = other.created_at;
                updated_at         = other.updated_at;
                finished_at        = other.finished_at;
                started_at         = other.started_at;
                images             = other.images;
                params             = other.params;
                status             = other.status;
                step               = other.step;
                steps              = other.steps;
                time               = other.time;
                model              = other.model;
                mode               = other.mode;
                initial_image      = other.initial_image;
                hash_fullsize      = other.hash_fullsize;
                hash_progress_size = other.hash_progress_size;
                status_message     = other.status_message;
                upscale_factor     = other.upscale_factor;
            }
            return *this;
        }
    };

    inline void to_json(nlohmann::json& j, const QueueItem& p) {
        nlohmann::json imageArray = nlohmann::json::array();
        for (const auto& imagePtr : p.images) {
            nlohmann::json imageJson = nullptr;
            to_json(imageJson, imagePtr);
            imageArray.push_back(imageJson);
        }
        j = nlohmann::json{
            {"id", p.id},
            {"created_at", p.created_at},
            {"updated_at", p.updated_at},
            {"finished_at", p.finished_at},
            {"started_at", p.started_at},
            {"status", (int)p.status},
            {"model", sd_gui_utils::UnicodeToUTF8(p.model)},
            {"mode", (int)p.mode},
            {"params", p.params},
            {"images", imageArray},
            {"upscale_factor", p.upscale_factor},
            {"initial_image", sd_gui_utils::UnicodeToUTF8(p.initial_image)},

        };
    }

    inline void from_json(const nlohmann::json& j, QueueItem& p) {
        j.at("id").get_to(p.id);
        j.at("created_at").get_to(p.created_at);
        j.at("updated_at").get_to(p.updated_at);
        if (j.contains("started_at")) {
            j.at("started_at").get_to(p.started_at);
        }
        if (j.contains("upscale_factor")) {
            j.at("upscale_factor").get_to(p.upscale_factor);
        }

        if (j.contains("images") && j["images"].is_array()) {
            auto& images_json = j["images"];

            for (auto& image_json : images_json) {
                if (image_json.is_string()) {
                    p.images.push_back(new QueueItemImage({image_json.get<std::string>()}));
                } else {
                    QueueItemImage* image = new QueueItemImage();
                    from_json(image_json, *image);
                    p.images.push_back(image);
                }
            }
        }

        j.at("finished_at").get_to(p.finished_at);
        j.at("model").get_to(p.model);
        j.at("params").get_to(p.params);
        j.at("initial_image").get_to(p.initial_image);
        p.status        = j.at("status").get<QM::QueueStatus>();
        p.mode          = j.at("mode").get<QM::GenerationMode>();
        p.initial_image = sd_gui_utils::UTF8ToUnicode(p.initial_image);
        p.model         = sd_gui_utils::UTF8ToUnicode(p.model);
    }

    class QueueManager {
    public:
        QueueManager(wxEvtHandler* eventHandler, std::string jobsdir);
        ~QueueManager();
        int AddItem(QM::QueueItem* item, bool fromFile = false);
        QM::QueueItem* GetItemPtr(int id);
        QM::QueueItem* GetItemPtr(QM::QueueItem item);
        const std::map<int, const QM::QueueItem*> getList();
        QM::QueueItem* Duplicate(const QM::QueueItem* item);
        QM::QueueItem* Duplicate(int id);
        // @brief Update the item too then update the status. This will store the list of the generated images too
        void SetStatus(QM::QueueStatus status, QM::QueueItem* item);
        void PauseAll();
        void RestartQueue();
        void UnPauseItem(QM::QueueItem* item);
        void PauseItem(QM::QueueItem* item);
        void SendEventToMainWindow(QM::QueueEvents eventType, QM::QueueItem* item = nullptr);
        void OnThreadMessage(wxThreadEvent& e);
        void SaveJobToFile(int id);
        void SaveJobToFile(const QM::QueueItem& item);
        bool DeleteJob(QM::QueueItem item);
        bool DeleteJob(int id);
        bool IsRunning();

    private:
        int GetCurrentUnixTimestamp();
        void LoadJobListFromDir();
        std::string jobsDir;
        int lastId = 0;
        int GetAnId();
        // thread events handler, toupdate main window data table
        void onItemAdded(QM::QueueItem item);

        // @brief check if something is running or not
        bool isRunning = false;

        wxEvtHandler* eventHandler;
        wxWindow* parent;
        std::map<int, QM::QueueItem*> QueueList;
    };

};

#endif