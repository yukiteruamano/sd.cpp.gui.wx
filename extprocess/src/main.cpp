#include <chrono>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <thread>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#endif

#include "libs/SharedMemoryManager.h"
#include "libs/json.hpp"
#include "ver.hpp"
#include "wx/translation.h"
#include "wx/event.h"
#include "wx/string.h"
#include "../../src/ui/utils.hpp"
#include "ui/QueueManager.h"

#include "ApplicationLogic.h"
#include "config.hpp"
#include "helpers/sd.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <dynamiclib_name>" << std::endl;
        writeCriticalLog("wrong parameters: " + std::string(argv[0]), "stablediffusiongui_diffuser.log");
        return 1;
    }

    std::shared_ptr<SharedMemoryManager> sharedMemory = std::make_shared<SharedMemoryManager>(SHARED_MEMORY_PATH, SHARED_MEMORY_SIZE, false);

    ApplicationLogic appLogic(argv[1], sharedMemory);
    if (!appLogic.loadLibrary()) {
        std::cerr << "[EXTPROCESS] Can not load shared library" << std::endl;
        writeCriticalLog("[EXTPROCESS] Can not load shared library: " + std::string(argv[1]), "stablediffusiongui_diffuser.log");
        return 1;
    }
    bool needToRun = true;
    int lastId     = 0;
    while (needToRun) {
        char buffer[SHARED_MEMORY_SIZE];
        if (sharedMemory->read(buffer, SHARED_MEMORY_SIZE)) {
            if (std::strlen(buffer) > 0) {
                std::string message = std::string(buffer, SHARED_MEMORY_SIZE);
                if (message.find("exit") != std::string::npos) {
                    std::cout << "Got exit command, exiting... " << std::endl;
                    needToRun = false;
                    break;
                }
                try {
                    nlohmann::json j = nlohmann::json::parse(message);
                    auto item        = j.get<QM::QueueItem>();
                    if (item.id != lastId) {
                        sharedMemory->clear();
                        std::cout << "[EXTPROCESS] New message: " << item.id << std::endl;
                        lastId = item.id;
                        appLogic.processMessage(item);
                    }
                } catch (std::exception& e) {
                    std::cerr << "[EXTPROCESS] Can not parse json message: " << e.what() << std::endl;
                }
            }
        } else {
            std::cerr << "[EXTPROCESS] Can not read shared memory" << std::endl;
            needToRun = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(EPROCESS_SLEEP_TIME));
    }

    return 0;
}
