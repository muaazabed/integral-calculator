// Created by Muaaz Abed.
// Fully templated binary tree class, can use in your project if credited.

#ifndef BINTREE_H
#define BINTREE_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include "Node.h"

using namespace std;

template <typename E>
class BinTree
{
    private:
        Node<E>* root;
        
        //Searches recursively for a node with the given data
        Node<E>* searchRec(Node<E>* node, E data)
        {
            if(node)
            {
                if(data == node.getData()) // If exponent is the same
                    return node;
                else if(data < node.getData()) // If exponent is less
                    searchRec(node.getLeft(),data);
                else if(node.getData() < data) // If exponent is more
                    searchRec(node.getRight(),data);
                else
                    return nullptr;
            }
            return nullptr;
        }
        
        //Inserts node using recursive search method
        void insertRec(Node<E>* node, E data)
        {
            //If exponent is the same
            if(data == node->getData())
            {
                node->setData(node->getData()+data);
                return;
            }
            
            //If coefficients are different
            if(data != node->getData())
            {
                node->setData(node->getData()+data);
                return;
            }
            else if(data < node->getData()) // If coefficient is less
            {
                if(node->getLeft()==nullptr)
                {
                    Node<E> *left = new Node<E>(data);
                    node->setLeft(left);
                }
                else
                {
                    insertRec(node->getLeft(),data);
                    return;
                }
            }
            else //If coefficient is more
            {
                if(node->getRight()==nullptr)
                {
                    Node<E> *right = new Node<E>(data);
                    node->setRight(right);
                }
                else
                {
                    insertRec(node->getRight(),data);
                    return;
                }
            }
        }
        
        //Returns parent of data using recursive method
        Node<E>* getParentRec(Node<E>* node, E data)
        {
            if(node == nullptr)
                return nullptr;
            if(node->getLeft()->getData() == data || node->getRight()->getData() == data)
                return node;
            else if(data < node.getData())
                return getParentRec(node->getLeft(), data);
            else
                return getParentRec(node->getRight(), data);
        }
        
        //Recursively searches for node to remove
        bool removeRec(Node<E>* parent, Node<E>* curr)
        {
            if(curr == nullptr)
                return false;
            //If both children exist
            if((curr->getLeft() != nullptr) && (curr->getRight() != nullptr))
            {
                Node<E>* succ = curr->getRight();
                Node<E>* succPar = curr;
                while(succ->getLeft())
                {
                    succPar = succ;
                    succ = succ->getLeft();
                }
                removeRec(succPar, succ);
            }
            //If the current node is equal to the root node
            else if(curr == root)
            {
                if(root->getLeft())
                    root = root->getLeft();
                else
                    root = root->getRight();
            }
            //If only the left node exists
            else if(root->getLeft())
            {
                if(parent->getLeft() == curr)
                    parent->setLeft(curr->getLeft());
                else
                    parent->setRight(curr->getLeft());
            }
            //If only the right node exists
            else
            {
                if(parent->getLeft() == curr)
                    parent->setLeft(curr->getRight());
                else
                    parent->setRight(curr->getRight());
            }
            return true;
        }
        
        //Recursively erases every node from the tree
        void eraseRec(Node<E>* curr)
        {
            if(curr)
            {
                eraseRec(curr->getLeft());
                delete curr;
                eraseRec(curr->getRight());
            }
        }
        
        //Recursively gets height of tree
        int getHeightRec(Node<E>* node)
        {
            if(node == nullptr)
                return -1;
            int left = getHeightRec(node->getLeft());
            int right = getHeightRec(node->getRight());
            if(left < right)
                return 1 + right;
            return 1 + left;
        }
        
        //Recursively prints every node in the tree
        void printRec(Node<E>* curr)
        {
            E primo = getFirst();
            string first = primo.print().str();
            if(curr)
            {
                printRec(curr->getRight()); //Iterates all the way right
                E data = curr->getData();
                string ret = data.print().str();
                
                if(ret==first)
                {
                    if(ret.at(1)=='-')
                    {
                        if(ret.at(3)=='(')
                            ret = "(-" + ret.substr(4);
                        else
                            ret = "-" + ret.substr(3);
                    }
                    else if(ret.at(1)=='+')
                        ret = ret.substr(3);
                }
                cout << ret;
                printRec(curr->getLeft()); //Iterates all the way left
            }
        }
        
        //Recursively finds first node
        Node<E>* getFirstRec(Node<E>* curr)
        {
            if(curr->getRight())
                return getFirstRec(curr->getRight());
            else
               return curr;
        }
    
    public:
        BinTree()
        {
            root = nullptr;
        }
        
        //Begins search for node with given data
        Node<E>* search(E data)
        {
            return searchRec(root,data);
        }
        
        //Begins search for place to insert node
        void insert(E data)
        {
            if(root == nullptr)
            {
                Node<E> *node = new Node<E>(data);
                root = node;
            }
            else
                insertRec(root,data);
        }
        
        //Begins search for node with parent of given data
        Node<E>* getParent(E data)
        {
            return getParentRec(root, data);
        }
        
        //Begins search for node to remove
        bool remove(E data)
        {
            Node<E>* node = search(data);
            Node<E>* par = getParent(data);
            return removeRec(par, node);
        }
        
        //Begins erasure of every node from the tree
        void erase()
        {
            eraseRec(root);
        }
        
        //Gets height of tree
        int getHeight()
        {
            return getHeightRec(root);
        }
        
        //Begins printing of every node in the tree
        void print()
        {
            printRec(root);
        }
        
        //Gets first node
        E getFirst()
        {
            Node<E>* op = getFirstRec(root);
            E data = op->getData();
            return data;
        }
};

#endif