//
// Created by onelei on 2024/4/12.
//

#ifndef ENGINE_OBJECTPOOL_H
#define ENGINE_OBJECTPOOL_H

#include <mutex>
#include <list>

namespace DivineBrush {

    template<typename T>
    class ObjectPool {
    public:
        // 从池中获取一个对象
        static T* Get() {
            std::lock_guard<std::mutex> lock(mutex);
            if (pool.empty()) {
                return new T();
            } else {
                T* obj = pool.front();
                pool.pop_front();
                return obj;
            }
        }

        // 将对象归还池中
        static void Release(T* obj) {
            std::lock_guard<std::mutex> lock(mutex);
            pool.push_back(obj);
        }

        // 析构函数中清理所有对象
        static void Clear() {
            std::lock_guard<std::mutex> lock(mutex);
            for (T* obj : pool) {
                delete obj;
            }
            pool.clear();
        }

    private:
        static std::list<T*> pool;  // 使用裸指针存储对象
        static std::mutex mutex;    // 用于保证线程安全
    };

    template<typename T>
    std::list<T*> ObjectPool<T>::pool;

    template<typename T>
    std::mutex ObjectPool<T>::mutex;
}// DivineBrush

#endif //ENGINE_OBJECTPOOL_H
