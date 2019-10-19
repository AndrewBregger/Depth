#include "bitmap.hpp"
#include <cstdlib>
#include <cstring>

namespace util {

#define GET_VALUE(val, offset) (((val) >> (offset)))
#define INDEX(bit) ((bit) / (u32) ELEMENT_SIZE)
#define OFFSET(bit) ((bit) % (u32) ELEMENT_SIZE)
		

	const u8 ELEMENT_SIZE = 8;
	
	u8 change_bit(u8 val, u8 offset, u8 to_set) {
		return (val & ~(1 << offset) | (to_set << offset));
	}

	Bitmap::Bitmap(u32 cap) {
		cap = Bitmap::compute_bytes(cap);
		map = allocate<u8>(cap);	
	}

	Bitmap::~Bitmap() {
		delete[] map;
	}

	void Bitmap::set_bit(u32 bit) {

		if(!valid(bit))
			resize(bit);

		u32 index = INDEX(bit);
		bit = OFFSET(bit);

		map[index] = change_bit(map[index], bit, 1);
	}

	void Bitmap::unset_bit(u32 bit) {
		u32 index = INDEX(bit);
		bit = OFFSET(bit);

		map[index] = change_bit(map[index], bit, 0);
	}

	bool Bitmap::check(u32 bit) {
		u32 index = INDEX(bit);
		bit = OFFSET(bit);
		return GET_VALUE(map[index], bit) & 0x1;
	}

	bool Bitmap::valid(u32 bit) {
		u32 index = INDEX(bit);
		return index >= cap;
	}

	void Bitmap::resize(u32 cap) {
		// auto temp = realloc(map, sizeof(u8) * cap);

		// if(temp == nullptr) {
		// LOG_INFO("Error reallocating memory for Bitmap");
		u8* buffer = allocate<u8>(cap);	
		memcpy(buffer, map, cap);
		free(map);
		map = buffer;
		// }

		this->cap = cap;
	}

	u32 Bitmap::size() {
		return sz;
	}
	
	u32 Bitmap::capacity() {
		return cap;
	}

	u32 Bitmap::compute_bytes(u32 bits) {
		u32 elements = INDEX(bits);
		return elements;
	}
}
