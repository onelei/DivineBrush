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
        rapidxml::xml_node<> *material_node = document.first_node("material");
        if (material_node == nullptr) {
            return;
        }
        rapidxml::xml_attribute<> *material_shader_attribute = material_node->first_attribute("shader");
        if (material_shader_attribute == nullptr) {
            return;
        }
        shader = Shader::Find(material_shader_attribute->value());
        //解析Texture
        rapidxml::xml_node<> *material_texture_node = material_node->first_node("texture");
        while (material_texture_node != nullptr) {
            rapidxml::xml_attribute<> *texture_name_attribute = material_texture_node->first_attribute("name");
            if (texture_name_attribute == nullptr) {
                return;
            }
            rapidxml::xml_attribute<> *texture_image_attribute = material_texture_node->first_attribute("image");
            if (texture_image_attribute == nullptr) {
                return;
            }
            std::string shader_property_name = texture_name_attribute->value();
            std::string image_path = texture_image_attribute->value();
            textures.emplace_back(texture_name_attribute->value(),
                                  image_path.empty() ? nullptr : Texture2d::LoadCompressFile(image_path));
            material_texture_node = material_texture_node->next_sibling("texture");
        }
    }

    void Material::SetTexture(const std::string &shaderPropertyName, Texture2d *texture) {
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

    void Material::LoadFromAssimpMaterial(aiMaterial *material, std::string fullPath) {
        aiString str;
        if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
            // Combine model directory with texture relative path
            auto modelDir = std::filesystem::path(fullPath).parent_path();
            std::filesystem::path fullTexturePath = modelDir / str.C_Str();
            auto texture = Texture2d::LoadFile(fullTexturePath.string());
            SetTexture("u_diffuse_texture", texture);
        }

        aiColor4D color;
        if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, color)) {
            glm::vec3 diffuseColor(color.r, color.g, color.b);
            SetUniformVector3("u_color", diffuseColor);
        }

        float shininess;
        if (AI_SUCCESS == material->Get(AI_MATKEY_SHININESS, shininess)) {
            SetUniformFloat("u_specular_highlight_shininess", shininess);
        }
    }

} // DivineBrush