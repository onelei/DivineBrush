//
// Created by onelei on 2024/3/19.
//

#ifndef ENGINE_DEBUG_H
#define ENGINE_DEBUG_H

#include <string>
#include "spdlog/spdlog.h"

#define DEBUG_LOG SPDLOG_INFO
#define DEBUG_LOG_WARN SPDLOG_WARN
#define DEBUG_LOG_ERROR SPDLOG_ERROR

namespace DivineBrush {
    class Debug {
    public:
        static void Init();
        static void Log(const std::string& message);
        static void LogEditor(const std::string& message);
        static void LogWarning(const std::string& message);
        static void LogError(const std::string& message);
        static void LogException(const std::string& message);
    };
} // DivineBrush

#endif //ENGINE_DEBUG_H
