//
//  Pool.cpp
//  m2
//
//  Created by Arthur Sun on 8/25/18.
//  Copyright © 2018 Arthur Sun. All rights reserved.
//

#include "Pool.hpp"


namespace m2 {
    Pool::Pool()
    {
        capacity = 16;
        count = 0;
        freeElement = 0;
        Objects = (_object_*)malloc(capacity * sizeof(_object_));
        memset(Objects, 0, capacity * sizeof(_object_));
        for(uint32_t i=0;i<capacity-1;i++){
            Objects[i].next = i + 1;
        }
        Objects[capacity-1].next = m2_null_element;
    }
    Pool::~Pool(){
        free(Objects);
    }
    uint32_t Pool::Create(){
        if(freeElement == m2_null_element){
            _object_* old = Objects;
            capacity *= 2;
            Objects = (_object_*)malloc(capacity * sizeof(_object_));
            memset(Objects+count, 0, count * sizeof(_object_));
            memcpy(Objects, old, count * sizeof(_object_));
            free(old);
            for(uint32_t i=count;i<capacity-1;i++){
                Objects[i].next = i + 1;
            }
            Objects[capacity-1].next = m2_null_element;
            freeElement = count;
        }
        uint32_t i = freeElement;
        freeElement = Objects[i].next;
        Objects[i].used = m2_pool_not_empty;
        count++;
        return i;
    }
    void Pool::Free(uint32_t i){
        Objects[i].next = freeElement;
        Objects[i].used = m2_pool_empty;
        freeElement = i;
        count--;
    }
    uint32_t Pool::Add(void* a)
    {
        uint32_t i = Create();
        Objects[i].Element = a;
        return i;
    }
    void Pool::Set(uint32_t i, void* a)
    {
        Objects[i].used = m2_pool_not_empty;
        Objects[i].Element = a;
        if(i == freeElement) freeElement = Objects[i].next;
    }
}
