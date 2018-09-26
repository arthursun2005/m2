//
//  Tree.hpp
//  m2
//
//  Created by Arthur Sun on 9/23/18.
//  Copyright © 2018 Arthur Sun. All rights reserved.
//

#ifndef Tree_hpp
#define Tree_hpp

#include "Common.hpp"



template <class T>
struct m2Tree {
    typedef bool (*Comp)(const T&, const T&);
    m2Tree<T>* left;
    m2Tree<T>* right;
    m2Tree<T>* parent;
    T* node;
    m2Tree(){
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        node = nullptr;
    }
    m2Tree(m2Tree<T>* t){
        left = nullptr;
        right = nullptr;
        parent = t;
        node = nullptr;
    }
    bool find(const T&) const;
    bool find(T* const n) const;
    void insertBefore(T& n);
    void insert(T& n);
    void insert(T& n, Comp comp);
    void insert(m2Tree<T>* node);
    void destroy();
    int size() const;
    int getHeight() const;
    int getDepth() const;
    void data(T*, int) const;
    T* data() const;
    void sort();
};


template <class T>
void m2DeleteTree(m2Tree<T>* tree);

template <class T>
void m2DeleteNode(m2Tree<T>* tree);

template <class T>
void m2RemoveNode(m2Tree<T>& tree);

#endif /* Tree_hpp */
