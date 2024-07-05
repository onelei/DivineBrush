//
// Created by onelei on 2024/3/26.
//

#ifndef ENGINE_TEXT_H
#define ENGINE_TEXT_H

#include <glm/glm.hpp>
#include "../Component/Component.h"
#include "Font.h"

namespace DivineBrush::UI {

    class Text : public Component {
    public:
        Text();

        ~Text();

        void SetText(const std::string text);

        std::string GetText() { return text; }

        void SetFont(Font *font);

        Font *GetFont() { return font; }

        void SetSize(float size);

        float GetSize() { return size; }

        void SetColor(const glm::vec4 &color);

        glm::vec4 GetColor() { return color; }

        void OnUpdate() override;

        void OnPreprocessRender() override;

        void OnPostprocessRender() override;

    private:
        std::string text;
        Font *font = nullptr;
        float size;
        glm::vec4 color;
    };

} // DivineBrush

#endif //ENGINE_TEXT_H
