//
// Created by onelei on 2024/4/1.
//

#ifndef ENGINE_LUABINDER_H
#define ENGINE_LUABINDER_H
#include "sol/sol.hpp"

namespace DivineBrush {

    class LuaBinder {
    public:
        // 初始化
        void Init();
    private:
        sol::state solState;
    };

} //  DivineBrush
#endif //ENGINE_LUABINDER_H
