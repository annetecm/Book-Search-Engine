#ifndef QUEUE_ARRAY_HPP
#define QUEUE_ARRAY_HPP
#include <stdexcept>
#include <iostream>

template <typename T>
class QueueA {
private:
    T* array_;           
    int capacity_;       
    int front_;          
    int rear_;           
    int size_;    

    void resize() {
        int new_capacity = capacity_ * 2;
        T* new_array = new T[new_capacity];
        for (int i = 0; i < size_; i++) {
            new_array[i] = array_[(front_ + i) % capacity_];
        }
        delete[] array_;
        array_ = new_array;
        front_ = 0;
        rear_ = size_ - 1;
        capacity_ = new_capacity;
    }       

public:
    QueueA() : front_(0), rear_(-1), size_(0), capacity_(2) {
        array_ = new T[capacity_];
    }
    ~QueueA() {
        delete[] array_;
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("La queue está vacía.");
        }
        return array_[front_];
    }

    int size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void clear() {
        front_ = 0;
        rear_ = capacity_ - 1;
        size_ = 0;
    }

    void push(const T& value) {
        if (size_ == capacity_) {
            resize();  
        }
        rear_ = (rear_ + 1) % capacity_;  
        array_[rear_] = value;
        size_++;
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("La queue está vacía.");
        }
        front_ = (front_ + 1) % capacity_; 
        size_--;
    }
};


#endif
