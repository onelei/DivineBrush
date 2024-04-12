//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_RINGBUFFER_H
#define ENGINE_RINGBUFFER_H

#include <iostream>
#include <vector>

namespace DivineBrush {
    template<typename T>
    class RingBuffer {
    private:
        std::vector<T> buffer;
        size_t head;
        size_t tail;
        size_t capacity;
        size_t size;
        bool full;

    public:
        explicit RingBuffer(size_t capacity)
                : buffer(capacity), head(0), tail(0), capacity(capacity), size(0), full(false) {}

        bool IsFull() const {
            return full;
        }

        bool IsEmpty() const {
            return size == 0;
        }

        void Enqueue(T item) {
            if (IsFull()) {
                throw std::runtime_error("Buffer is full");
            }
            buffer[tail] = item;
            tail = (tail + 1) % capacity;
            size++;
            full = size == capacity;
        }

        T Dequeue() {
            if (IsEmpty()) {
                throw std::runtime_error("Buffer is empty");
            }
            T item = buffer[head];
            head = (head + 1) % capacity;
            size--;
            full = false;
            return item;
        }

        T Peek() const {
            if (IsEmpty()) {
                throw std::runtime_error("Buffer is empty");
            }
            return buffer[head];
        }

        size_t GetSize() const {
            return size;
        }
    };
} // DivineBrush

#endif //ENGINE_RINGBUFFER_H
