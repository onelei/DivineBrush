//
// Created by onelei on 2024/3/26.
//

#include "Text.h"
#include "rttr/registration.h"
#include "../Render/MeshFilter.h"
#include "../Component/GameObject.h"

namespace DivineBrush::UI {
    using namespace rttr;

    RTTR_REGISTRATION {
        registration::class_<Text>("Text")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    Text::Text() {

    }

    Text::~Text() {

    }

    void Text::SetText(const std::string text) {
        if (this->text == text) {
            return;
        }
        this->text = text;
        is_dirty = true;
    }

    void Text::SetFont(Font *font) {
        if (this->font == font) {
            return;
        }
        this->font = font;
        is_dirty = true;
    }

    void Text::SetSize(float size) {
        if (this->size == size) {
            return;
        }
        this->size = size;
        is_dirty = true;
    }

    void Text::SetColor(const glm::vec4 &color) {
        if (this->color == color) {
            return;
        }
        this->color = color;
        is_dirty = true;
    }

    void Text::OnUpdate() {
        if (font == nullptr) {
            return;
        }
        auto fontTexture = font->GetFontTexture();
        if (fontTexture == nullptr) {
            return;
        }
        Component::OnUpdate();

        auto mesh_filter = dynamic_cast<MeshFilter *>(gameObject->GetComponent("MeshFilter"));
        if (mesh_filter == nullptr) {
            //挂上 MeshFilter 组件
            mesh_filter = dynamic_cast<MeshFilter *>(gameObject->AddComponentByName("MeshFilter"));
            //创建 Material
            auto material = new Material();//设置材质
            material->Parse("material/text.mat");
            //挂上 MeshRender 组件
            auto mesh_render = dynamic_cast<MeshRender *>(gameObject->AddComponentByName("MeshRender"));
            mesh_render->SetMaterial(material);
            //使用文字贴图
            material->SetTexture("u_diffuse_texture", fontTexture);
        }
        if (is_dirty) {
            is_dirty = false;
            std::vector<Font::Character *> character_vec = font->LoadString(text);
            //遍历每个字符进行绘制
            std::vector<MeshFilter::Vertex> vertex_vector;
            std::vector<unsigned short> index_vector(character_vec.size() * 6);
            int x = 0;
            std::vector<unsigned short> index = {0, 1, 2, 0, 2, 3};
            //合并Mesh
            for (int i = 0; i < character_vec.size(); ++i) {
                auto character = character_vec[i];
                unsigned short width = (character->right_bottom_x - character->left_top_x) * fontTexture->GetWidth();
                unsigned short height = (character->right_bottom_y - character->left_top_y) * fontTexture->GetHeight();
                vertex_vector.insert(vertex_vector.end(), {
                        {{x,         -height,   0.0f}, color, {character->left_top_x,     character->left_top_y}},
                        {{x + width, -height,   0.0f}, color, {character->right_bottom_x, character->left_top_y}},
                        {{x + width, 0.0f, 0.0f}, color, {character->right_bottom_x, character->right_bottom_y}},
                        {{x,         0.0f, 0.0f}, color, {character->left_top_x,     character->right_bottom_y}}
                });
                x += width;
                for (int j = 0; j < index.size(); ++j) {
                    index_vector[i * index.size() + j] = index[j] + i * 4;
                }
            }
            mesh_filter->CreateMesh(vertex_vector, index_vector);
        }
    }

    void Text::OnPreprocessRender() {
        Component::OnPreprocessRender();
    }

    void Text::OnPostprocessRender() {
        Component::OnPostprocessRender();
    }

} // DivineBrush