//
// Created by onelei on 2024/3/8.
//

#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

//#include "string"
#include <string>
#include <GL/glew.h>

namespace DivineBrush {
    class Application {
    public:
        static GLuint color_texture_id;//FBO 颜色纹理
        static GLuint depth_texture_id;//FBO 深度纹理

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

        void Update();

        void UpdateScreenSize();

        static void Run();

    private:
        static std::string data_path;
        static std::string persistent_data_path;
    };
} // DivineBrush

#endif //ENGINE_APPLICATION_H
