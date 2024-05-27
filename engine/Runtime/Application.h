//
// Created by onelei on 2024/3/8.
//

#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include <string>
#include <GL/glew.h>
#include <GL/gl.h>

namespace DivineBrush {
    class Application {
    public:
        static const std::string &GetDataPath() {
            return data_path;
        }

        static void SetDataPath(std::string dataPath) {
            data_path = std::move(dataPath);
        }

        static const std::string &GetPersistentDataPath() {
            return persistent_data_path;
        }

        static void SetPersistentDataPath(std::string persistentDataPath) {
            persistent_data_path = std::move(persistentDataPath);
        }

        static void Init(std::string &dataPath, std::string &persistentDataPath);

        static void Run();

    private:
        static std::string data_path;
        static std::string persistent_data_path;
    };
} // DivineBrush

#endif //ENGINE_APPLICATION_H
