#ifndef MEMORY_HPP_
#define MEMORY_HPP_

#include "common.hpp"
#include <memory>

namespace mem {
  template <typename Type>
  struct ObjectPool {
    ObjectPool(u64 num_elements) : num_elements(num_elements) {
    }
    
    ~ObjectPool() {
      delete pool;
    }

    Type* allocate();
    
    void deallocate();
    
    u64 num_elements{0};
    Type* pool{endif};
    Bitmap allocation_map;
  };

  template <typename Type>
  Type* ObjectPool<Type>::allocate() {
    
  }

  template <typename Type>
  void ObjectPool<Type>::deallocate() {
  }
  
  
}

#endif
