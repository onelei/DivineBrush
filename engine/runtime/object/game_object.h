//
// Created by onelei on 2024/2/29.
//

#ifndef ENGINE_GAME_OBJECT_H
#define ENGINE_GAME_OBJECT_H

#include "object.h"
#include "component.h"

namespace DivineBrush {
    class Component;
}

namespace DivineBrush {

    class GameObject : public Object {
    public:
        GameObject();

        GameObject(std::string name);

        ~GameObject() override = default;

        static std::string kTagMainCamera;
    public:
        std::string GetName(){
           return this->name;
        }

        void SetName(std::string name){
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

        Component *AddComponent(const std::string& componentName);

        Component *GetComponent(const std::string& componentName);

        virtual void start();

        virtual void update();

        virtual void fixedUpdate();

        virtual void lateUpdate();

        virtual void onEnable();

        virtual void onDisable();

        virtual void onDestroy();

    private:
        std::string name;
        std::unordered_map<std::string, std::vector<Component *>> component_map;
        std::string tag;
        unsigned char layer = 0x01;
    };

} // DivineBrush

#endif //ENGINE_GAME_OBJECT_H
