#ifndef MEMORY_HPP_
#define MEMORY_HPP_

// Should memory allocators be given a name so it can be refered to later in debug messages?

#include "common.hpp"
#include "utils/bitmap.hpp"
#include <cstdlib>


namespace mem {
    template <typename Type>
    struct ObjectPool {
        ObjectPool(u64 num_elements);

        ~ObjectPool();

        Type* allocate();

        void deallocate(Type* ptr);

        u32 first_available();

        inline u64 slots() { return num_elements; }

        u32 size() { return sz; }

        u64 num_elements{0};
        u32 sz{0};
        Type* pool{nullptr};
        util::Bitmap allocation_map;
    };

    template<typename Type>
    ObjectPool<Type>::ObjectPool(u64 num_elements) : num_elements(num_elements) {
    }

    template<typename Type>
    ObjectPool<Type>::~ObjectPool() {
        free(pool);
    }


    template <typename Type>
    Type* ObjectPool<Type>::allocate() {
        if(pool == nullptr)
            pool = (Type*) calloc(sizeof(Type), num_elements);

        auto index = first_available();
        if(index >= num_elements || index == util::Bitmap::INVALID_INDEX) {
            LOG_MSG("[OBJECT POOL]: Out of memory");
            return nullptr;
        }
        sz++;
        allocation_map.set_bit(index);
        return &pool[index];
    }

    template <typename Type>
    void ObjectPool<Type>::deallocate(Type* ptr) {
        // is this in bytes or has it been scaled already?
        auto index = ptr - pool;
        // I will find out when it segfaults.
        allocation_map.unset_bit(index);
        // is this valid?
        ptr->~Type();
        sz--;
    }

    template <typename Type>
    u32 ObjectPool<Type>::first_available() {
        // for if i want to change the name.
        // engine/utils/bitmap.hpp:74
        return allocation_map.first_index();
    }
}

#endif
