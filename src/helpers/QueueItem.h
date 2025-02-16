#ifndef __HELPERS_QUEUE_ITEM_
#define __HELPERS_QUEUE_ITEM_

inline const std::unordered_map<SDMode, std::string> GenerationMode_str = {
    {SDMode::TXT2IMG, "txt2img"},
    {SDMode::IMG2IMG, "img2img"},
    {SDMode::CONVERT, "convert"},
    {SDMode::UPSCALE, "upscale"},
    {SDMode::IMG2VID, "img2vid"}};

inline const std::unordered_map<std::string, SDMode> GenerationMode_str_inv = {
    {"txt2img", SDMode::TXT2IMG},
    {"img2img", SDMode::IMG2IMG},
    {"convert", SDMode::CONVERT},
    {"upscale", SDMode::UPSCALE},
    {"img2vid", SDMode::IMG2VID}};

/// @brief Store the images from the queue jobs
struct QueueItemImage : public sd_gui_utils::networks::ItemImage {
    std::string pathname;
    long id = -1;

    QueueItemImage() = default;

    QueueItemImage(const std::string& pathname_, sd_gui_utils::ImageType type_ = sd_gui_utils::ImageType::GENERATED, long id_ = -1)
        : ItemImage{type_}, pathname(pathname_), id(id_) {}
    QueueItemImage(const wxString& pathname_, sd_gui_utils::ImageType type_ = sd_gui_utils::ImageType::GENERATED, long id_ = -1)
        : ItemImage{type_}, pathname(pathname_.utf8_string()), id(id_) {}

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
};  // struct QueueItemImage
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(QueueItemImage, pathname, type, id)
inline void to_json(nlohmann::json& j, const QueueItemImage* item) {
    if (item) {
        j = nlohmann::json{{"pathname", wxString(item->pathname).utf8_string()}, {"type", item->type}};
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

struct QueueItem : public sd_gui_utils::networks::RemoteQueueItem {
    std::vector<QueueItemImage> images = {};
    std::vector<std::string> rawImages = {};
    std::string initial_image          = "";
    std::string mask_image             = "";
    inline wxString GetActualSpeed() {
        wxString speed = "";
        if (this->status == QueueStatus::MODEL_LOADING || this->mode == SDMode::CONVERT) {
            // int progress = (this->step / this->steps) * 100;
            speed = wxString::Format(this->time > 1.0f ? "%.2fs/it" : "%.2fit/s", this->time > 1.0f || this->time == 0 ? this->time : (1.0f / this->time));
        } else {
            speed = wxString::Format(this->time > 1.0f ? "%.2fs/it %d/%d" : "%.2fit/s %d/%d", this->time > 1.0f || this->time == 0 ? this->time : (1.0f / this->time), this->step, this->steps);
        }
        return speed;
    }
    inline int GetActualProgress() {
        float current_progress = 0.f;

        if (this->step > 0 && this->steps > 0) {
            current_progress = 100.f * (static_cast<float>(this->step) /
                                        static_cast<float>(this->steps));
        }
        if (this->step == this->steps) {
            current_progress = 100.f;
        }
        return static_cast<int>(current_progress);
    }

    inline sd_gui_utils::RemoteQueueItem convertToNetwork() {
        sd_gui_utils::RemoteQueueItem newItem(*this);
        for (const auto img : this->images) {
            std::string encoded;
            if (sd_gui_utils::EncodeFileToBase64(img.pathname, encoded) == false) {
                continue;
            }

            sd_gui_utils::networks::ItemImage itemImage;
            itemImage.rawData = std::vector<unsigned char>(encoded.begin(), encoded.end());
            itemImage.type    = img.type;
            newItem.image_data.push_back(itemImage);
        }
        this->images.clear();
        for (const auto img : this->rawImages) {
            std::string encoded;
            if (sd_gui_utils::EncodeFileToBase64(img, encoded) == false) {
                continue;
            }

            sd_gui_utils::networks::ItemImage itemImage;
            itemImage.rawData = std::vector<unsigned char>(encoded.begin(), encoded.end());
            itemImage.type    = sd_gui_utils::ImageType::GENERATED;
            newItem.image_data.push_back(itemImage);
        }
        return newItem;
    };
    inline static QueueItem convertFromNetwork(const sd_gui_utils::RemoteQueueItem& item) {
        QueueItem newItem(item);
        int counter = 0;
        for (const auto img : item.image_data) {
            std::cout << "[CONVERT] " << img.rawData.size() << " type: " << (int)img.type << std::endl;
            QueueItemImage image;
            wxFileName fn;
            fn.AssignTempFileName("sd_gui_");
            image.pathname   = fn.GetFullPath();
            std::string data = std::string(img.rawData.begin(), img.rawData.end());
            if (sd_gui_utils::DecodeBase64ToFile(data, image.pathname) == false) {
                continue;
            }
            image.type = img.type;
            image.id   = counter;
            // newItem.images.push_back(image);
            if (sd_gui_utils::hasImageType(image.type, sd_gui_utils::ImageType::INITIAL)) {
                newItem.initial_image = image.pathname;
            } else if (sd_gui_utils::hasImageType(image.type, sd_gui_utils::ImageType::MASK_USED)) {
                newItem.mask_image = image.pathname;
            } else if (sd_gui_utils::hasImageType(image.type, sd_gui_utils::ImageType::CONTROLNET)) {
                newItem.params.control_image_path = image.pathname;
            } else if (sd_gui_utils::hasImageType(image.type, sd_gui_utils::ImageType::GENERATED)) {
                newItem.rawImages.push_back(image.pathname);
            } else {
                newItem.images.push_back(image);
            }

            counter++;
        }
        return newItem;
    };
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(QueueItem,
                                                id,
                                                created_at,
                                                updated_at,
                                                finished_at,
                                                started_at,
                                                params,
                                                status,
                                                //  event,
                                                stats,
                                                step,
                                                steps,
                                                hash_fullsize,
                                                hash_progress_size,
                                                time,
                                                model,
                                                mode,
                                                status_message,
                                                upscale_factor,
                                                sha256,
                                                app_version,
                                                git_version,
                                                original_prompt,
                                                original_negative_prompt,
                                                keep_checkpoint_in_memory,
                                                keep_upscaler_in_memory,
                                                need_sha256,
                                                generated_sha256,
                                                update_index,
                                                server,
                                                images,
                                                rawImages,
                                                initial_image,
                                                mask_image,
                                                image_data)

#endif  // __HELPERS_QUEUE_ITEM