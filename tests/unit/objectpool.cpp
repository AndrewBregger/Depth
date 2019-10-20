#include "tests.hpp"
#include "memory.hpp"
#include <fstream>

struct Vec {
    i32 x, y, z;
    Vec(i32 x, i32 y, i32 z) : x(x), y(y), z(z) {}

    // std::ostream& operator<< (std::ostream& out, const Vec& vec) {

	//     std::cout << vertex->x << " " << vertex->y <<  " " << vertex->z <<  " " << std::endl;
    // }

    bool operator== (const Vec& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

void test_constructor() {
    mem::ObjectPool<Vec> vec_pool(3);

}

void test_allocate() {
    mem::ObjectPool<Vec> vec_pool(3);

    Vec* vec = allocate(vec_pool, 1 , 2 , 3 );

    TEST_ASSERT(*vec == Vec(1 , 2 , 3 ) and vec_pool.size() == 1, "ObjectPool::allocate");
}

void test_multi_allocate() {
    mem::ObjectPool<Vec> vec_pool(3);

    Vec* vec = allocate(vec_pool,  1 , 2 , 3 );
    Vec* vec2 = allocate(vec_pool, 1 , 3 , 3 );

    TEST_ASSERT(*vec == Vec(1 , 2 , 3 ) and *vec2 == Vec(1 , 3 , 3 ) and vec_pool.size() == 2, "ObjectPool::allocate multi");
}

void test_multi_allocate_and_removale() {
    mem::ObjectPool<Vec> vec_pool(3);

    Vec* vec = allocate(vec_pool,  1 , 2 , 3 );
    Vec* vec2 = allocate(vec_pool, 1 , 3 , 3 );

    TEST_ASSERT(*vec == Vec(1 , 2 , 3 ) and *vec2 == Vec(1 , 3 , 3 ) and vec_pool.size() == 2, "ObjectPool::allocate 2 allocs");

    
    Vec* vec3 = allocate(vec_pool, 1 , 3 , 3 );
    TEST_ASSERT(*vec3 == Vec(1 , 3 , 3 ) and vec_pool.size() == 3, "ObjectPool::allocate 1 alloc");

    deallocate(vec_pool, vec3);
    TEST_ASSERT(*vec == Vec(1 , 2 , 3 ) and *vec2 == Vec(1 , 3 , 3 ) and vec_pool.size() == 2 and vec3 == nullptr, "ObjectPool::allocate 2 allocs");

}

void test_multi_allocate_and_full() {
    mem::ObjectPool<Vec> vec_pool(3);

    Vec* vec = allocate(vec_pool,  1 , 2 , 3 );
    Vec* vec2 = allocate(vec_pool, 1 , 3 , 3 );
    Vec* vec3 = allocate(vec_pool, 1 , 3 , 3 );
    Vec* invalid = allocate(vec_pool, 1 , 2 , 3 );

    TEST_ASSERT(invalid == nullptr and vec_pool.size() == 3, "ObjectPool::allocate out of memory");
}

int main() {
    test_constructor();
    test_allocate();
    test_multi_allocate();
    test_multi_allocate_and_removale();
    test_multi_allocate_and_full();
}