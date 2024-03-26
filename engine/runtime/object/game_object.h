//
// Created by onelei on 2024/2/29.
//

#ifndef ENGINE_GAME_OBJECT_H
#define ENGINE_GAME_OBJECT_H

#include "object.h"
#include "component.h"
#include "../render/camera.h"
#include "../../depends/node/node.h"

namespace DivineBrush {
    class Component;
}

namespace DivineBrush {

    class GameObject : public Object, public Node {
    public:
        GameObject();

        GameObject(std::string name);

        ~GameObject();

        static std::string kTagMainCamera;

        static void RenderAll();

        static void UpdateAll();

        static void ForeachGameObject(std::function<void(GameObject *)> func);

        static GameObject*Find(std::string name);

        void ForeachComponent(std::function<void(Component *)> func);

    public:
        std::string GetName() {
            return this->name;
        }

        void SetName(std::string name) {
            this->name = name;
        }

        void SetTag(std::string tag) {
            this->tag = std::move(tag);
        }

        std::string GetTag() {
            return this->tag;
        }

        void SetLayer(unsigned char layer) {
            this->layer = layer;
        }

        unsigned char GetLayer() const {
            return this->layer;
        }

        void SetActive(bool is_active) {
            this->is_active = is_active;
        }

        bool IsActive() const {
            return this->is_active;
        }

        Component *AddComponent(const std::string &componentName);

        Component *GetComponent(const std::string &componentName);

        std::unordered_map<std::string, std::vector<Component *>> GetComponents() {
            return component_map;
        }

    private:
        std::string name;
        std::unordered_map<std::string, std::vector<Component *>> component_map;
        std::string tag;
        unsigned char layer = 0x01;
        bool is_active = true;
    };

} // DivineBrush

#endif //ENGINE_GAME_OBJECT_H
