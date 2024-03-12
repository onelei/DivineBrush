//
// Created by onelei on 2024/3/6.
//

#ifndef ENGINE_ARRAY_POOL_H
#define ENGINE_ARRAY_POOL_H

#include <vector>
#include <stack>

namespace DivineBrush {
    template<typename T>
    class ArrayPool {
    public:
        ArrayPool(size_t arraySize, size_t initialCapacity)
                : _arraySize(arraySize) {
            for (size_t i = 0; i < initialCapacity; ++i) {
                _pool.push(new T[_arraySize]);
            }
        }

        ~ArrayPool() {
            // 清理所有已分配的数组
            while (!_pool.empty()) {
                delete[] _pool.top();
                _pool.pop();
            }
        }

        T *Get() {
            if (_pool.empty()) {
                // 池中无可用数组，分配新的数组
                return new T[_arraySize];
            } else {
                // 从池中获取一个数组并返回
                T *arr = _pool.top();
                _pool.pop();
                return arr;
            }
        }

        void Release(T *arr) {
            // 将不再使用的数组返回池中以供再次使用
            _pool.push(arr);
        }

    private:
        size_t _arraySize; // 每个数组的大小
        std::stack<T *> _pool; // 未被使用的数组的栈
    };
} // DivineBrush
#endif //ENGINE_ARRAY_POOL_H
