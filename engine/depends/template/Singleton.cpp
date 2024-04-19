//
// Created by onelei on 2024/4/19.
//
#include "Singleton.h"

namespace DivineBrush {
    template<typename T>
    T &Singleton<T>::GetInstance() {
        // 局部静态变量的初始化是线程安全的，在C++11及更高版本中得到保证
        static T instance;
        return instance;
    }
}//DivineBrush