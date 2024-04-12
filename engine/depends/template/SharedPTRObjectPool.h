//
// Created by onelei on 2024/4/12.
//

#ifndef ENGINE_SHAREDPTROBJECTPOOL_H
#define ENGINE_SHAREDPTROBJECTPOOL_H

#include <iostream>
#include <list>
#include <memory>

namespace DivineBrush {
    template<typename T>
    class SharedPTRObjectPool {
    public:
        // 从池中获取一个对象
        static std::shared_ptr<T> Get() {
            if (pool.empty()) {
                return std::shared_ptr<T>(new T());
            } else {
                // 从池中取一个对象，并从池中移除
                auto obj = pool.front();
                pool.pop_front();
                return obj;
            }
        }

        // 将使用完毕的对象归还池中
        static void Release(std::shared_ptr<T> obj) {
            pool.push_back(obj);
        }

    private:
        static std::list<std::shared_ptr<T>> pool; // 使用链表存储池中的对象
    };

} // DivineBrush

#endif //ENGINE_SHAREDPTROBJECTPOOL_H
