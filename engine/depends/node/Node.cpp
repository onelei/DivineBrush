//
// Created by onelei on 2024/3/22.
//

#include "Node.h"

namespace DivineBrush {
    Node *Node::root_node = new Node();

    void Node::AddChild(Node *child) {
        if (child == nullptr) {
            return;
        }
        if (child->GetParent() != nullptr) {
            child->GetParent()->RemoveChild(child);
        }
        this->children.push_back(child);
        child->parent = this;
    }

    void Node::RemoveChild(Node *child) {
        if (child == nullptr) {
            return;
        }
        this->children.remove(child);
    }

    void Node::SetParent(Node *parent) {
        parent->AddChild(this);
    }

    void Node::Foreach(Node *node, std::function<void(Node *)> func) {
        for (auto child: node->children) {
            Foreach(child, func);
        }
        if (node != root_node) {
            func(node);
        }
    }

    void Node::Find(Node *node, std::function<bool(Node *)> function_check, Node **node_result) {
        for (auto child: node->children) {
            Find(child, function_check, node_result);
            if (*node_result != nullptr) {
                break;
            }
        }
        if (*node_result != nullptr) {
            return;
        }
        if (function_check(node)) {
            (*node_result) = node;
        }

    }
} // DivineBrush