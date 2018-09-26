//
//  Tree.cpp
//  m2
//
//  Created by Arthur Sun on 9/23/18.
//  Copyright © 2018 Arthur Sun. All rights reserved.
//

#include "Tree.hpp"

template <class T>
void m2Tree<T>::insert(T& n)
{
    if(node == nullptr){
        node = &n;
    }else if(left == nullptr){
        left = new m2Tree<T>(this);
        left->node = &n;
    }else if(right == nullptr){
        right = new m2Tree<T>(this);
        right->node = &n;
    }else if(left->getHeight() <= right->getHeight()) left->insert(n);
    else right->insert(n);
}

template <class T>
void m2Tree<T>::insert(T& n, Comp comp)
{
    if(node == nullptr) node = &n;
    else if(comp(n, *node)){
        if(left == nullptr){
            left = new m2Tree<T>(this);
            left->node = &n;
        }else left->insert(n, comp);
    }
    else{
        if(right == nullptr){
            right = new m2Tree<T>(this);
            right->node = &n;
        }else right->insert(n, comp);
    }
}

template <class T>
void m2Tree<T>::insertBefore(T &n)
{
    m2Tree<T> p = new m2Tree<T>();
    p->node = &n;
    if(parent != nullptr){
        p->parent = parent;
        if(parent->left == this){
            parent->left = p;
            p->left = this;
        }else{
            parent->right = p;
            p->right = this;
        }
    }
    parent = p;
}

template <class T>
void m2Tree<T>::insert(m2Tree<T>* node)
{
    if(left == nullptr){left = node;left->parent = this;}
    else if(right == nullptr){right = node;left->parent = this;}
    else if(left->getHeight() <= right->getHeight()) left->insert(node);
    else right->insert(node);
}

template <class T>
int m2Tree<T>::getHeight() const
{
    int l = left != nullptr ? left->getHeight() + 1 : 0;
    int r = right != nullptr ? right->getHeight() + 1 : 0;
    return l > r ? l : r;
}

template <class T>
int m2Tree<T>::getDepth() const
{
    return parent != nullptr ? parent->getDepth() + 1 : 0;
}

template <class T>
int m2Tree<T>::size() const
{
    int a = left != nullptr ? left->size() : 0;
    int b = right != nullptr ? right->size() : 0;
    return node != nullptr ? 1 : 0 + a + b;
}

template <class T>
void m2Tree<T>::destroy()
{
    if(left != nullptr){
        left->destroy();
        delete left;
        left = nullptr;
    }
    if(right != nullptr){
        right->destroy();
        delete right;
        right = nullptr;
    }
}

template <class T>
bool m2Tree<T>::find(const T& n) const
{
    if(*node == n) return true;
    if(left != nullptr && left->find(n)) return true;
    if(right != nullptr && right->find(n)) return true;
    return false;
}

template <class T>
bool m2Tree<T>::find(T* const n) const
{
    if(node == n) return true;
    if(left != nullptr && left->find(n)) return true;
    if(right != nullptr && right->find(n)) return true;
    return false;
}

template <class T>
void m2Tree<T>::data(T* data, int offset) const
{
    if(left != nullptr) left->data(data, offset);
    if(node != nullptr){
        *(data+offset) = *node;
        offset++;
    }
    if(right != nullptr) right->data(data, offset);
}

template <class T>
T* m2Tree<T>::data() const
{
    T a[size()];
    T* nodes = &a;
    data(nodes, 0);
    return nodes;
}

template <class T>
void m2DeleteTree(m2Tree<T>* tree)
{
    tree->destroy();
    delete tree;
    tree = nullptr;
}

template <class T>
void m2DeleteNode(m2Tree<T>* tree)
{
    if(tree->left != nullptr){
        tree->left->insert(tree->right);
        tree->left->parent = tree->parent;
        if(tree->parent != nullptr){
            if(tree->parent->left == tree) tree->parent->left = tree->left;
            else tree->parent->right = tree->left;
        }
    }else if(tree->right != nullptr){
        tree->right->parent = tree->parent;
        if(tree->parent != nullptr){
            if(tree->parent->left == tree) tree->parent->left = tree->right;
            else tree->parent->right = tree->right;
        }
    }
    delete tree;
    tree = nullptr;
}

template <class T>
void m2RemoveNode(m2Tree<T>& tree)
{
    if(tree.left != nullptr){
        tree.left->insert(tree.right);
        tree.left->parent = tree.parent;
        if(tree->parent != nullptr){
            if(tree.parent->left == tree) tree.parent->left = tree.left;
            else tree.parent->right = tree.left;
        }
    }else if(tree.right != nullptr){
        tree.right->parent = tree.parent;
        if(tree.parent != nullptr){
            if(tree.parent->left == tree) tree.parent->left = tree.right;
            else tree.parent->right = tree.right;
        }
    }
}
