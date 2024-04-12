//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_SINGLETON_H
#define ENGINE_SINGLETON_H

#include <mutex>

namespace DivineBrush {
    template<typename T>
    class Singleton {
    public:
        // 删除拷贝构造函数和赋值运算符，确保它们不可用
        Singleton(const Singleton &) = delete;

        Singleton &operator=(const Singleton &) = delete;

        // 提供一个静态方法来获取单例对象的引用
        static T &GetInstance() {
            // 局部静态变量的初始化是线程安全的，在C++11及更高版本中得到保证
            static T instance;
            return instance;
        }

    protected:
        // 保护构造函数，防止外部构造
        Singleton() {}

        // 允许派生类析构
        virtual ~Singleton() = default;
    };


} // DivineBrush

#endif //ENGINE_SINGLETON_H
