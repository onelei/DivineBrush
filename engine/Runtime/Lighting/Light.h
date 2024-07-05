//
// Created by onelei on 2024/5/14.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include "../Component/Component.h"
#include <glm/glm.hpp>

namespace DivineBrush {

    class Light : public Component {
        enum LightType {
            Sport,
            Directional,
            Point,
            Area,
        };
    public:
        Light();

        ~Light();

        void SetLightType(LightType type);

        void SetColor(glm::vec3 _color);

        void SetIntensity(float _intensity);

        void SetAttenuationConst(float _attenuationConst);

        void SetAttenuationLinear(float _attenuationLinear);

        void SetAttenuationQuadratic(float _attenuationQuadratic);

        void OnUpdate() override;

        LightType GetLightType() const {
            return lightType;
        }


        glm::vec3 GetColor() const {
            return color;
        }

        float GetIntensity() const {
            return intensity;
        }

        unsigned short GetLightIndex() const {
            return lightIndex;
        }

        float GetAttenuationConst() const {
            return attenuationConst;
        }

        float GetAttenuationLinear() const {
            return attenuationLinear;
        }

        float GetAttenuationQuadratic() const {
            return attenuationQuadratic;
        }

    private:
        static std::unordered_map<LightType, unsigned int> lightTypeCounts;
        LightType lightType = LightType::Directional;
        unsigned short lightIndex = 0;
        glm::vec3 color = glm::vec3(1.0f);
        float intensity = 1.0f;
        //PointLight
        //点光衰减常数项
        float attenuationConst = 0.0f;
        //点光衰减线性项
        float attenuationLinear = 0.0f;
        //点光衰减二次项
        float attenuationQuadratic = 0.0f;
    RTTR_ENABLE(Component);
    };

} // DivineBrush

#endif //ENGINE_LIGHT_H
