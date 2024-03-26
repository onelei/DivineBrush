//
// Created by onelei on 2024/3/21.
//

#ifndef ENGINE_RENDER_CONTROL_H
#define ENGINE_RENDER_CONTROL_H

#include <unordered_map>

namespace DivineBrush {

    class RenderControl {
    public:
        enum class RenderState {
            None,
            StencilTest,
        };

        static void Enable(RenderState render_state);

        static void Disable(RenderState render_state);

    private:
        static std::unordered_map<RenderState, bool> render_state_map;
    };

} // DivineBrush

#endif //ENGINE_RENDER_CONTROL_H
