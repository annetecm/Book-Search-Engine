#ifndef STACK_ARRAY_HPP
#define STACK_ARRAY_HPP

#include <iostream>
#include <stdexcept>

template <typename T>

class StackA{
    private:
     T* data_;           
    size_t size_{ 0 };  
    size_t capacity_; 
    void resize(size_t nueva_capacidad)
    {
        T* nuevo_data = new T[nueva_capacidad];  
        for (size_t i = 0; i < size_; ++i) {
            nuevo_data[i] = data_[i];
        }
        delete[] data_;
        data_ = nuevo_data; 
        capacity_ = nueva_capacidad;
    }

    public:
    StackA() : data_(new T[1]), capacity_(1) {}
    ~StackA() {
        clear();
    }

    bool empty() const{
        return size_ == 0;
    }

    size_t size() const{
        return size_;
    }

    void clear(){
        size_ = 0;
    }

    void push(const T& value) {
        if (size_ == capacity_) {
            resize(capacity_ * 2); // Duplica la capacidad si está llena
        }
        data_[size_++] = value; // Insertar el valor y aumentar el tamaño
    }

    // Inserta un nuevo elemento (paso por referencia rvalue)
    void push(T&& value) {
        if (size_ == capacity_) {
            resize(capacity_ * 2); // Duplica la capacidad si está llena
        }
        data_[size_++] = std::move(value); // Insertar usando std::move
    }

    void pop(){
        if (empty()) {
            throw std::out_of_range("La pila esta vacia");
        }
        --size_; 
    }

    T& top(){
        if (empty()) {
            throw std::out_of_range("La pila esta vacia");
        }
        return data_[size_ - 1]; 
    }

    const T& top() const
    {
        if (empty()) {
            throw std::out_of_range("La pila esta vacia");
        }
        return data_[size_ - 1]; 
    }





};

#endif