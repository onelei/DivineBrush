//
// Created by onelei on 2024/4/12.
//

#include "SharedPTRObjectPool.h"

namespace DivineBrush {
    template<typename T>
    std::list<std::shared_ptr<T>> SharedPTRObjectPool<T>::pool;
} // DivineBrush