//
// Created by onelei on 2024/3/21.
//

#include "render_control.h"
#include <GLFW/glfw3.h>

namespace DivineBrush {
    std::unordered_map<RenderControl::RenderState, bool> RenderControl::render_state_map;

    void RenderControl::Enable(RenderControl::RenderState render_state) {
        if (render_state_map.find(render_state) != render_state_map.end() && render_state_map[render_state]) {
            return;
        }
        switch (render_state) {
            case RenderState::None:
                break;
            case RenderState::StencilTest:
                glEnable(GL_STENCIL_TEST);
                break;
        }
        render_state_map[render_state] = true;
    }

    void RenderControl::Disable(RenderControl::RenderState render_state) {
        if (render_state_map.find(render_state) != render_state_map.end() && !render_state_map[render_state]) {
            return;
        }
        switch (render_state) {
            case RenderState::None:
                break;
            case RenderState::StencilTest:
                glDisable(GL_STENCIL_TEST);
                break;
        }
        render_state_map[render_state] = false;
    }
} // DivineBrush