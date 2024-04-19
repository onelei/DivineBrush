//
// Created by onelei on 2024/4/19.
//
#include "ObjectPool.h"

namespace DivineBrush {
    template<typename T>
    std::list<T *> ObjectPool<T>::pool;

    template<typename T>
    T *ObjectPool<T>::Get() {
        //return new T();
        if (pool.empty()) {
            return new T();
        } else {
            T *obj = pool.front();
            pool.pop_front();
            return obj;
        }
    }

    // 将对象归还池中
    template<typename T>
    void ObjectPool<T>::Release(T *obj) {
        //delete obj;
        pool.push_back(obj);
    }

    // 析构函数中清理所有对象
    template<typename T>
    void ObjectPool<T>::Clear() {
        for (auto obj: pool) {
            delete obj;
        }
        pool.clear();
    }
}//DivineBrush