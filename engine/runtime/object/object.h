//
// Created by onelei on 2024/2/29.
//

#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H

namespace DivineBrush {

    class Object {
    public:
        Object() = default;

        virtual ~Object() = default;

    public:
        virtual int getInstanceID();
    };

} // DivineBrush

#endif //ENGINE_OBJECT_H
