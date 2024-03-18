//
// Created by onelei on 2024/2/29.
//

#include "game_object.h"
#include "rttr/registration.h"

using namespace rttr;
namespace DivineBrush {
    std::string GameObject::kTagMainCamera = "MainCamera";
    std::vector<GameObject *> GameObject::game_objects;

    GameObject::GameObject() {
        this->SetName("GameObject");
        game_objects.push_back(this);
    }

    GameObject::GameObject(std::string name) {
        this->SetName(name);
        game_objects.push_back(this);
    }

    GameObject::~GameObject() {
        game_objects.erase(std::remove(game_objects.begin(), game_objects.end(), this), game_objects.end());
    }

    Component *GameObject::AddComponent(const std::string &componentName) {
        type t = type::get_by_name(componentName);
        variant var = t.create();
        Component *component = var.get_value<Component *>();
        component->SetGameObject(this);
        component->Awake();
        if (component_map.find(componentName) == component_map.end()) {
            std::vector<Component *> componentVec;
            componentVec.push_back(component);
            component_map[componentName] = componentVec;
        } else {
            component_map[componentName].push_back(component);
        }
        return component;
    }

    Component *GameObject::GetComponent(const std::string &componentName) {
        if (component_map.find(componentName) != component_map.end()) {
            return component_map[componentName][0];
        }
        return nullptr;
    }

    void GameObject::RenderAll(Camera *camera) {
        //剔除不需要渲染的物体
        for (auto &gameObject : game_objects) {
            auto mesh_render = dynamic_cast<MeshRender *>(gameObject->GetComponent("MeshRender"));
            if(!mesh_render) {
                continue;
            }
            //对两个数的位进行逐位的与(AND)操作。如果两个相应的位都为1，则该位的结果为1；否则，为0。
            if((mesh_render->GetGameObject()->GetLayer()&camera->GetCullingMask()) == 0x00){
                continue;
            }
            //从当前Camera获取View Projection
            mesh_render->SetView(camera->GetView());
            mesh_render->SetProjection(camera->GetProjection());
            mesh_render->Render();
        }
    }

    void GameObject::start() {

    }

    void GameObject::update() {

    }

    void GameObject::fixedUpdate() {

    }

    void GameObject::lateUpdate() {

    }

    void GameObject::onEnable() {

    }

    void GameObject::onDisable() {

    }

    void GameObject::onDestroy() {

    }
} // DivineBrush