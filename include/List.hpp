#include <iostream>
#include <cstddef>
#include <initializer_list>
#include <typeinfo>

#pragma once
template<typename T>
class List {
private:
    struct Node {
        T data;
        Node *next;

        Node(T data) {
            this->data = data;
            this->next = nullptr;
        }
    };

    Node *ptr_begin;
    Node *ptr_end;
    size_t len_;

    class iterator {
    private:
        Node *ptr;
    public:
        iterator(Node *ptr_) {
            ptr = ptr_;
        }

        bool operator!=(const iterator &other) const {
            return (this->ptr != other.ptr);
        }

        T &operator*() const {
            return ptr->data;
        }

        iterator &operator++() {
            ptr = ptr->next;
            return *this;
        }
    };

public:
    iterator begin() const {
        return iterator(ptr_begin);
    }

    iterator end() const {
        return iterator(nullptr);
    }

    void append(T data) {
        auto new_node = new Node(data);
        if (len_ > 0)
            (*ptr_end).next = new_node;
        else
            ptr_begin = new_node;
        ptr_end = new_node;
        len_++;
    }

    List() {
        len_ = 0;
        ptr_begin = nullptr;
        ptr_end = nullptr;
    }

    List(std::initializer_list<T> values) {
        len_ = 0;
        for (auto &value : values)
            this->append(value);
    }

    void clear(){
        Node *cur = ptr_begin;
        Node *next;
        while (cur != nullptr) {
            next = cur->next;
            delete cur;
            cur = next;
        }
        len_ = 0;
        ptr_begin = nullptr;
        ptr_end = nullptr;
    }

    ~List() {
        clear();
    }

    friend std::ostream &operator<<(std::ostream &out, const List list) {
        T var;
        out << "List<" << typeid(var).name() << ">" << "[";
        for (const auto &elem : list)
            out << elem << ", ";
        out << "]\n";
        return out;
    }

    size_t size() const{
        return len_;
    }

    const T &get_back() const{
        return ptr_end->data;
    }
};