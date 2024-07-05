//
// Created by onelei on 2024/2/29.
//

#ifndef ENGINE_GAMEOBJECT_H
#define ENGINE_GAMEOBJECT_H

#include "vector"
#include "Object.h"
#include "Component.h"
#include "../Render/Camera.h"
#include "../../depends/node/Node.h"
#include "rttr/registration.h"

using namespace rttr;

namespace DivineBrush {
    class Component;

    class Transform;

    class GameObject : public Object, public Node {
    public:
        GameObject(const char *name);

        ~GameObject();

        static std::string kTagMainCamera;

        static void RenderAll();

        static void UpdateAll();

        static void FixUpdateAll();

        static void ForeachGameObject(std::function<void(GameObject *)> func);

        static GameObject *Find(std::string name);

        void ForeachComponent(std::function<void(Component *)> func);

    public:
        const char *GetName() {
            return this->name;
        }

        void SetName(const char *name) {
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

        Transform *GetTransform() {
            return this->transform;
        }

        Component *AddComponent(const std::string &componentName);

        Component *AddComponentByLua(std::string componentName, Component *component);

        Component *GetComponent(const std::string &componentName);

        template<class T = Component>
        T *GetComponent() {
            type t = type::get<T>();
            auto componentName = t.get_name().to_string();
            auto component = GetComponent(componentName);
            if (component == nullptr) {
                //从子类里面查找
                auto derived_classes = t.get_derived_classes();
                for (auto &derived_class : derived_classes) {
                    component = GetComponent(derived_class.get_name().to_string());
                    if (component != nullptr) {
                        break;
                    }
                }
            }
            return dynamic_cast<T *>(component);
        }

        template<class T = Component>
        T *AddComponent() {
            type t = type::get<T>();
            auto componentName = t.get_name().to_string();
            auto component = AddComponent(componentName);
            if (component == nullptr) {
                return nullptr;
            }
            return dynamic_cast<T *>(component);
        }

        std::unordered_map<std::string, std::vector<Component *>> GetComponents() {
            return component_map;
        }

    protected:
        Transform *transform;
    private:
        const char *name;
        std::unordered_map<std::string, std::vector<Component *>> component_map;
        std::string tag;
        unsigned char layer = 0x01;
        bool is_active = true;
    };

} // DivineBrush

#endif //ENGINE_GAMEOBJECT_H
