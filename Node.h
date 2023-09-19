// Created by Muaaz Abed.
// Fully templated node class, can use in your project if credited.

#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>
#include <sstream>

template <typename E>
class Node{
    private:
        E data;
    public:
        Node* left;
        Node* right;
        Node()
        {
            left = nullptr;
            right = nullptr;
        }
        //Overloaded constructor
        Node(E newData)
        {
            data = newData;
            left = nullptr;
            right = nullptr;
        }

        //Destructor
        ~Node()
        {
            delete left;
            delete right;
        }

        //Returns data
        E getData()
        {
            return data;
        }

        //Sets data of node
        void setData(E param)
        {
            data=param;
        }

        //Returns left child node
        Node* getLeft()
        {
            return left;
        }

        //Sets left child node
        void setLeft(Node* node)
        {
            left = node;
        }

        //Returns right child node
        Node* getRight()
        {
            return right;
        }

        //Sets right child node
        void setRight(Node* node)
        {
            right = node;
        }

        //Overloads +=
        Node& operator+=(E& rhs)
        {
            this.data += rhs;
            return *this;
        }

        //Overloads <<
        friend std::ostream& operator<<(std::ostream& out, Node& obj)
        {
            Node<E> temp(obj.getData());
            E ret = temp.getData();
            out << ret;
            return out;
        }
};

#endif // NODE_H