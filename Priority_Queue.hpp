#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm> 

struct Element {
     int value;
     int priority;
        
        //comparador para prioridad
     bool operator<(const Element& other) const {
            return priority > other.priority;
        }
};

class PriorityQueue {
private:
    std::vector<Element> queue;

public:
    // constructor vacio
    PriorityQueue() {}

    int top() const {
        if (!queue.empty()) {
            return queue.front().value;
        }
        throw std::runtime_error("La cola esta vacia.");
    }

    size_t size() const {
        return queue.size();
    }

    bool empty() const {
        return queue.empty();
    }

    void clear() {
        queue.clear();
    }

    // inserta segun prioridad
    void push(int value, int priority) {
        Element newElement = {value, priority};
        queue.push_back(newElement);
        
        std::sort(queue.begin(), queue.end());
    }

    void pop() {
        if (!queue.empty()) {
            queue.erase(queue.begin());
        } else {
            throw std::runtime_error("La cola esta vacia.");
        }
    }
};

#endif