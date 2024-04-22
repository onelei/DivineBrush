//
// Created by onelei on 2024/3/28.
//

#ifndef ENGINE_SELECTION_H
#define ENGINE_SELECTION_H

#include "../depends/node/Node.h"

namespace DivineBrush {

    class Selection {
    public:
        static void SetSelectedNode(Node *node) {
            selected_node = node;
        }

        static Node *GetSelectedNode() {
            return selected_node;
        }

    private:
        static Node *selected_node;
    };

} // DivineBrush

#endif //ENGINE_SELECTION_H
