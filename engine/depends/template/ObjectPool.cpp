//
// Created by onelei on 2024/4/12.
//

#include "ObjectPool.h"

namespace DivineBrush {
    template<typename T>
    std::list<T *> ObjectPool<T>::pool;
}//DivineBrush