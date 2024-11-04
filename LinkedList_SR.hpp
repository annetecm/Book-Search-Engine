//=================================================================================================================
/**
 *  Example of implementation of a class that defines linked lists.
 */
 //=================================================================================================================

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

// Includes
#include <stdexcept>    // For std::out_of_range
#include <iostream>

/**
 *  A class that defines a node of a linked list.
 * 
 *  @tparam T   The type of the data stored in the node.
 */
template <typename T>
class Node {

public:

    T data;         /**< The data value stored in the node. */

    Node* next;     /**< Pointer to the next node in the linked list. */

    
    /**
     *  Constructs a new Node object with the given value.
     * 
     *  @param[in]  value   The value to be stored in the node.
     */
    Node(const T& value) 
    {
        data = value;
        next = nullptr;
    }
    
    /**
     *  Constructs a new Node object by moving the given value.
     * 
     *  @param[in]  value   The value to be stored in the node.
     */
    Node(T&& value) 
    {
        data = std::move(value);
        next = nullptr;
    }
};

/**
 *  A class that defines a linked list.
 *
 *  @tparam T   The type of the data stored in the linked list.
 */
template <typename T>
class LinkedList {

private:

    Node<T>* head_{ nullptr };    /**< Pointer to the first node in the linked list. */

    unsigned int size_{0};

public:

    /**
     *  Default constructor. The list is empty.
     */
    LinkedList() = default;

    // Constructor for a list of n elements 
    LinkedList(int numElements, T initialValue) : head_(nullptr), size_(0) {
        for (int i = 0; i < numElements; ++i) {
            push_back(initialValue);
        }
    }

    /**
     *  Class destructor
     */
    ~LinkedList() 
    {
        clear();
    }

    unsigned int size() const
    {
        return size_;
    }   

    /**
     *  Checks if the list is empty.
     *
     *  @return True if the list is empty, false otherwise.
     */
    bool empty() const
    {
        return head_ == nullptr;
    }

    /**
     *  Clears the linked list by deleting all nodes.
     */
    void clear()
    {
        Node<T>* current = head_;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head_ = nullptr;
        size_ = 0;
    }

    /**
     *  Adds a new node with the given value to the front of the list.
     *
     *  @param[in]  value   The value to add to the front.
     */
    void push_front(const T& value)
    {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head_;
        head_ = newNode;
        size_++;
    }

    /**
     *  Adds a new node by moving the given value to the front of the list.
     *
     *  @param[in]  value   The value to move to the front.
     */
    void push_front(T&& value)
    {
        Node<T>* newNode = new Node<T>(std::move(value));
        newNode->next = head_;
        head_ = newNode;
        size_++;
    }

    /**
     *  Removes the node at the front of the list.
     */
    void pop_front()
    {
        if (!empty()) {
            Node<T>* oldHead = head_;
            head_ = head_->next;
            delete oldHead;
            size_--;
        }
    }

    Node<T>* getHead() const {
        return head_;
    }

    /**
     *  Returns a reference to the value of the first node.
     *
     *  @return The data of the first node.
     */
    T& front()
    {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head_->data;
    }

    /**
     *  Returns a reference to the value of the first node.
     *
     *  @return The data of the first node.
     */
    const T& front() const
    {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head_->data;
    }

    /**
     *  Inserts a new node with the given value after the provided node.
     *
     *  @param[in]  node    The node after which to insert the new node.
     *  @param[in]  value   The value to insert.
     */
    void insert_after(Node<T>* node, const T& value)
    {
        if (node != nullptr) {
            Node<T>* newNode = new Node<T>(value);
            newNode->next = node->next;
            node->next = newNode;
            size_++;
        }
    }

    /**
     *  Removes the node after the provided node.
     *
     *  @param[in]  node The node after which to erase the next node.
     */
    void erase_after(Node<T>* node)
    {
        if (node != nullptr && node->next != nullptr) {
            Node<T>* toDelete = node->next;
            node->next = toDelete->next;
            delete toDelete;
            size_--;
        }
    }

    /**
     *  Finds the first node containing the given value.
     *
     *  @param[in]  value   The value to find.
     * 
     *  @return Pointer to the node containing the value, or nullptr if not found.
     */
    Node<T>* find(const T& value)
    {
        Node<T>* current = head_;

        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }

        return nullptr;
    }

    /// Returns the value of the index entered
    /// @param index Position to be searched
    /// @return Pointer to the node containing the value, or nullptr if not found.
    int at(int index) {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Index out of range");
        }

        Node<T>* current = head_;
        int counter = 0;

        while (counter < index) {
            current = current->next;
            counter++;
        }

        return current->data;
    }

    // Adds a value at the end of the list
    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if (head_ == nullptr) {
            // If the list is empthy the new node is the head
            head_ = newNode;
        } else {
            Node<T>* current = head_;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size_++;
    }

    void pop_back() {
        if (head_ == nullptr) {
            std::cout << "The list is empty, you can't pop back" << std::endl;
            return;
        }

        if (head_->next == nullptr) {
            delete head_;
            head_ = nullptr;
        } else {
            Node<T>* current = head_;
            while (current->next->next != nullptr) {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
        size_--;
    }

    ///Prints the list, if empty prints nullptr
    void print() {
        Node<T>* current = head_;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr\n";
    }
};

#endif
//=================================================================================================================
//  END OF FILE
//=================================================================================================================