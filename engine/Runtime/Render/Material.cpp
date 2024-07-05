//
// Created by onelei on 2024/3/14.
//

#include "Material.h"
#include <rapidxml/rapidxml.hpp>
#include "rapidxml/rapidxml_utils.hpp"
#include "../Application.h"
#include "../RenderPipeline/RenderCommandBuffer.h"
#include <string>
#include <filesystem>

namespace DivineBrush {
    void Material::Parse(const std::string &materialPath) {
        //解析xml
        rapidxml::file<> xml_file((Application::GetDataPath() + materialPath).c_str());
        rapidxml::xml_document<> document;
        document.parse<0>(xml_file.data());
        //根节点
        auto material_node = document.first_node("material");
        if (material_node == nullptr) {
            return;
        }
        auto material_shader_attribute = material_node->first_attribute("shader");
        if (material_shader_attribute == nullptr) {
            return;
        }
        shader = Shader::Find(material_shader_attribute->value());
        //解析Texture
        auto material_texture_node = material_node->first_node("texture");
        while (material_texture_node != nullptr) {
            auto texture_name_attribute = material_texture_node->first_attribute("name");
            if (texture_name_attribute == nullptr) {
                return;
            }
            auto texture_image_attribute = material_texture_node->first_attribute("image");
            if (texture_image_attribute == nullptr) {
                return;
            }
            std::string shader_property_name = texture_name_attribute->value();
            std::string image_path = texture_image_attribute->value();
            textures.emplace_back(shader_property_name,image_path.empty() ? nullptr : Texture2D::LoadCompressFile(image_path));
            material_texture_node = material_texture_node->next_sibling("texture");
        }
    }

    void Material::SetTexture(const std::string &shaderPropertyName, Texture2D *texture) {
        if (texture == nullptr) {
            return;
        }
        for (auto &pair: textures) {
            if (pair.first == shaderPropertyName) {
                delete (pair.second);
                pair.second = texture;
                break;
            }
        }
    }

    void Material::SetUniformInt(const std::string &shaderPropertyName, int value) {
        uniformIntMap[shaderPropertyName] = value;
    }

    void Material::SetUniformFloat(const std::string &shaderPropertyName, float value) {
        uniformFloatMap[shaderPropertyName] = value;
    }

    void Material::SetUniformVector3(const std::string &shaderPropertyName, glm::vec3 &value) {
        uniformVector3Map[shaderPropertyName] = value;
    }

    void Material::Render(GLuint shaderProgramHandle) {
        for (int texture_index = 0; texture_index < textures.size(); ++texture_index) {
            auto textureUnit = GL_TEXTURE0 + texture_index;
            auto texture2d = textures[texture_index].second;
            if (texture2d == nullptr)
                continue;
            auto textureHandle = texture2d->GetTextureHandle();
            RenderCommandBuffer::ActiveAndBindTextureHandler(textureUnit, textureHandle);

            //设置Shader程序从纹理单元读取颜色数据
            auto uniformName = textures[texture_index].first.c_str();
            RenderCommandBuffer::SetUniformIntHandler(shaderProgramHandle, const_cast<char *>(uniformName),
                                                      texture_index);
        }
        for (auto& pair:uniformIntMap){
            RenderCommandBuffer::SetUniformFloatHandler(shaderProgramHandle,pair.first.c_str(), pair.second);
        }
        for (auto& pair:uniformFloatMap){
            RenderCommandBuffer::SetUniformFloatHandler(shaderProgramHandle,pair.first.c_str(), pair.second);
        }
        for (auto& pair:uniformVector3Map) {
            RenderCommandBuffer::SetUniformVector3Handler(shaderProgramHandle, pair.first.c_str(), pair.second);
        }
    }

    void Material::LoadFromAssimpMaterial(const aiScene* scene, const aiMaterial *material, const std::string& fullPath) {
        aiString imagePath;
        if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            material->GetTexture(aiTextureType_DIFFUSE, 0, &imagePath);
            // Combine model directory with texture relative path
            //利用此方法判断是否是FBX模型内嵌贴图
            auto tex = scene->GetEmbeddedTexture(imagePath.C_Str());
            if (tex != nullptr)
            {
                //有内嵌贴图
                auto texture = Texture2D::LoadFile(tex, false);
                std::string textureKey = "u_diffuse_texture";
                if (!Contains(textureKey)) {
                    textures.emplace_back(textureKey, texture);
                }
            } else {
                auto modelDir = std::filesystem::path(fullPath).parent_path();
                std::filesystem::path fullTexturePath = modelDir / imagePath.C_Str();
                auto texture = Texture2D::LoadFile(fullTexturePath.string());
                std::string textureKey = "u_diffuse_texture";
                if (!Contains(textureKey)) {
                    textures.emplace_back(textureKey, texture);
                }
            }
        }

//        aiColor4D color;
//        if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, color)) {
//            glm::vec3 diffuseColor(color.r, color.g, color.b);
//            SetUniformVector3("u_color", diffuseColor);
//        }
//
//        float shininess;
//        if (AI_SUCCESS == material->Get(AI_MATKEY_SHININESS, shininess)) {
//            SetUniformFloat("u_specular_highlight_shininess", shininess);
//        }
    }

    bool Material::Contains(const std::string& key) {
        return std::any_of(textures.begin(), textures.end(), [&key](const auto& pair) {
            return pair.first == key;
        });
    }

} // DivineBrush