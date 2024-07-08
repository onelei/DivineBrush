//
// Created by onelei on 2024/3/19.
//

#include <iostream>
#include "debug.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#define DEBUG

namespace DivineBrush {

    void Debug::Init() {
        try {
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_level(spdlog::level::trace);

            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/player.log", true);
            file_sink->set_level(spdlog::level::trace);

            // you can even set multi_sink logger as default logger
            spdlog::set_default_logger(
                    std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list({console_sink, file_sink})));
            //spdlog::set_pattern("[%H:%M:%S %z] [source %s] [function %!] [line %#] [%^%l%$] %v");
            spdlog::set_pattern("[%H:%M:%S %z] [%s] [line %#] [%^%l%$] %v");
            spdlog::stdout_color_mt("console");

            DEBUG_LOG("log start");
        }
        catch (const spdlog::spdlog_ex &ex) {
            std::cout << "Log init failed: " << ex.what() << std::endl;
        }
    }

    void Debug::Log(const std::string &message) {
        SPDLOG_INFO(message);
    }

    void Debug::LogEditor(const std::string &message) {
#if defined(DEBUG)
        SPDLOG_INFO(message);
#endif
    }

    void Debug::LogWarning(const std::string &message) {
        SPDLOG_WARN(message);
    }

    void Debug::LogError(const std::string &message) {
        SPDLOG_ERROR(message);
    }

    void Debug::LogException(const std::string &message) {
        SPDLOG_CRITICAL(message);
    }
} // DivineBrush