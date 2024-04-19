//
// Created by onelei on 2024/4/12.
//

#ifndef ENGINE_OBJECTPOOL_H
#define ENGINE_OBJECTPOOL_H

#include <iostream>
#include <list>

namespace DivineBrush {

    template<typename T>
    class ObjectPool {
    public:
        // 从池中获取一个对象
        static T *Get();

        // 将对象归还池中
        static void Release(T *obj);

        // 析构函数中清理所有对象
        static void Clear();

    private:
        static std::list<T *> pool; // 改用裸指针存储对象
    };
}// DivineBrush

#endif //ENGINE_OBJECTPOOL_H
