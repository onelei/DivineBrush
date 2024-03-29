//
// Created by onelei on 2024/3/22.
//

#ifndef ENGINE_NODE_H
#define ENGINE_NODE_H

#include <list>
#include <functional>

namespace DivineBrush {

    class Node {
    public :
        virtual ~Node() = default;

        void AddChild(Node *child);

        void RemoveChild(Node *child);

        static Node *GetRootNode() {
            return root_node;
        }

        static void Foreach(Node *node, std::function<void(Node *)> func);

        static void Find(Node *node, std::function<bool(Node *)> function_check, Node **node_result);

        Node *GetParent() {
            return parent;
        }

        std::list<Node *> GetChildren() {
            return children;
        }

        void SetParent(Node *parent);

    private :
        static Node *root_node;
        Node *parent = nullptr;
        std::list<Node *> children;
    };

} // DivineBrush

#endif //ENGINE_NODE_H
