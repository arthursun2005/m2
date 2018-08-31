//
//  Pool.hpp
//  m2
//
//  Created by Arthur Sun on 8/25/18.
//  Copyright © 2018 Arthur Sun. All rights reserved.
//

#ifndef Pool_hpp
#define Pool_hpp

#include "Common.hpp"

#define m2_null_element (-1)
#define m2_pool_not_empty 1
#define m2_pool_empty 2

namespace m2 {
    struct Pool
    {
    protected:
        struct _object_
        {
            void* Element;
            uint32_t next;
            uint8_t used;
        };
    public:
        _object_* Objects;
        uint32_t freeElement;
        uint32_t count;
        uint32_t capacity;
        Pool();
        ~Pool();
        /// @brief Initialize a position
        uint32_t Create();
        /// @brief Free a position
        void Free(uint32_t i);
        /// @brief Add a pointer reference
        uint32_t Add(void*);
        /// @brief Set a pointer reference
        void Set(uint32_t i, void*);
        /// @brief Read a pointer
        inline void* operator [] (uint32_t i) const
        {
            if(i >= capacity) return nullptr;
            return Objects[i].Element;
        }
        /// @brief Write to a pointer
        inline void*& operator [] (uint32_t i)
        {
            return Objects[i].Element;
        }
        /// @brief Read the state of a position
        inline uint8_t operator () (uint32_t i) const
        {
            if(i >= capacity) return 0;
            return Objects[i].used;
        }
    };
}

#endif /* Pool_hpp */
