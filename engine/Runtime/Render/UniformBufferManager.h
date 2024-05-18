//
// Created by onelei on 2024/5/17.
//

#ifndef ENGINE_UNIFORMBUFFERMANAGER_H
#define ENGINE_UNIFORMBUFFERMANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>

namespace DivineBrush {

    class UniformInfo {
    public:
        std::string name;
        int offset;
        short size;
    };

    class UniformBuffer {
    public:
        std::string name;
        std::string memberName;
        unsigned short size;
        unsigned int bind;
        unsigned int buffer;
    };


    class UniformBufferManager {
    public:
        static void Init();

        static void SetUniformInfoFloat(const std::string &name, const std::string &memberName, float value);

        static void SetUniformInfoVector3(const std::string &name, const std::string &memberName, glm::vec3 &value);

        static void SetUniformInfoInt(const std::string &name, const std::string &memberName, int value);

        static bool TryGetUniformBuffer(const std::string &name, UniformBuffer *&uniformBuffer);

        static bool TryGetUniformInfos(const std::string &name, std::vector<UniformInfo> *&uniformInfos);

    private:
        static void CreateUniformBuffer();

        static std::unordered_map<std::string, UniformBuffer> uniformBuffers;
        static std::unordered_map<std::string, std::vector<UniformInfo>> uniformInfos;
    };

} // DivineBrush

#endif //ENGINE_UNIFORMBUFFERMANAGER_H
