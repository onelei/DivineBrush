//
// Created by onelei on 2024/7/8.
//

#ifndef ENGINE_AUDIOLISTENER_H
#define ENGINE_AUDIOLISTENER_H

#include <glm/glm.hpp>
#include "../Component/Component.h"

namespace DivineBrush {

    class AudioListener : public Component {
    public:
        AudioListener();

        ~AudioListener();

        void OnAwake() override;

        void OnUpdate() override;

    private:
        glm::vec3 lastPosition = glm::vec3(0);
    RTTR_ENABLE(Component);
    };
} // DivineBrush

#endif //ENGINE_AUDIOLISTENER_H
