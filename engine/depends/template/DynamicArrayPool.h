//
// Created by onelei on 2024/3/6.
//

#ifndef ENGINE_DYNAMICARRAYPOOL_H
#define ENGINE_DYNAMICARRAYPOOL_H

#include <vector>
#include <stack>

namespace DivineBrush {
    template<typename T>
    class DynamicArrayPool {
    public:
        DynamicArrayPool() = default;

        ~DynamicArrayPool() {
            while (!_pool.empty()) {
                delete[] _pool.top().first;
                _pool.pop();
            }
        }

        T *Get(size_t size) {
            if (!_pool.empty()) {
                auto arr = _pool.top();
                _pool.pop();
                if (arr.second >= size) {
                    return arr.first;
                } else {
                    // 旧数组大小不够，删除并创建一个足够大的新数组
                    delete[] arr.first;
                }
            }
            return new T[size];
        }

        void Release(T *arr, size_t size) {
            _pool.push({arr, size});
        }

    private:
        std::stack<std::pair<T *, size_t>> _pool; // 保存数组指针和对应的大小
    };
} // DivineBrush
#endif //ENGINE_DYNAMICARRAYPOOL_H
