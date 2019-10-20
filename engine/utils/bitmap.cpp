#include "bitmap.hpp"
#include <cstdlib>
#include <cstring>

namespace util {

#define GET_VALUE(val, offset) (((val) >> (offset)) & 0x1) 
#define INDEX(bit) ((bit) / (u32) ELEMENT_SIZE)
#define OFFSET(bit) ((bit) % (u32) ELEMENT_SIZE)
		

	const u8 ELEMENT_SIZE = 8;
	
	u8 change_bit(u8 val, u8 offset, u8 to_set) {
		return (val & ~(1 << offset) | (to_set << offset));
	}

	Bitmap::Bitmap(u32 cap) {
		this->cap = Bitmap::compute_bytes(cap);
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

		sz++;

		map[index] = change_bit(map[index], bit, 1);
	}

	void Bitmap::unset_bit(u32 bit) {
		u32 index = INDEX(bit);
		bit = OFFSET(bit);

		sz--;

		map[index] = change_bit(map[index], bit, 0);
	}

	bool Bitmap::check(u32 bit) {
		u32 index = INDEX(bit);
		bit = OFFSET(bit);
		return GET_VALUE(map[index], bit) & 0x1;
	}

	bool Bitmap::valid(u32 bit) {
		u32 index = INDEX(bit);
		return index < cap;
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

	u32 Bitmap::first_index() {
		for(u32 i = 0; i < cap; ++i) {
			// if this element is empty the return the first element
			if(map[i] == 0)
				return i * ELEMENT_SIZE;
			// if this element is full then ignore it.
			if(map[i] == 255)
				continue;
			for(u32 j = 0; j < ELEMENT_SIZE; ++j) {
				u32 val = GET_VALUE(map[i], j);
				if(val == 0)
					return i * ELEMENT_SIZE + j;
			}
		}
		return INVALID_INDEX;
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

	Bitmap::iterator Bitmap::begin() {
		return const_cast<const Bitmap&>(*this).begin();
	}

	Bitmap::iterator Bitmap::end() {
		return const_cast<const Bitmap&>(*this).end();
	}

	Bitmap::const_iterator Bitmap::begin() const {
		return Iterator(map, cap);
	}

	Bitmap::const_iterator Bitmap::end() const {
		return Iterator();
	}

	Bitmap::Iterator::Iterator() : value(std::make_pair(0, false)), map(nullptr), cap(0) {
	}

	Bitmap::Iterator::Iterator(u8* map, u32 cap) : value(std::make_pair(0, GET_VALUE(map[0], 0))),
		map(map), cap(cap) {
	}

	Bitmap::Iterator Bitmap::Iterator::operator++ () {
		Bitmap::Iterator save = *this;

		u32 next_index = INDEX(++value.first);
		u32 offset = OFFSET(value.first);

		if(next_index < cap)
			value.second = GET_VALUE(map[next_index], offset);
		else {
			map = nullptr;
			value = std::make_pair(0, false);
			cap = 0;
		}

		return save;
	}

	Bitmap::Iterator Bitmap::Iterator::operator++ (int) {
		u32 next_index = INDEX(++value.first);
		u32 offset = OFFSET(value.first);

		if(next_index < cap)
			value.second = GET_VALUE(map[next_index], offset);
		else {
			map = nullptr;
			value = std::make_pair(0, false);
			cap = 0;
		}

		return *this;
	}

	std::pair<u32, bool> Bitmap::Iterator::operator* () const {
		return value;
	}

	bool Bitmap::Iterator::operator== (const Iterator& other) const {
		// if these are the same then the cap will be the same
		return map == other.map && value == other.value;
	}

	bool Bitmap::Iterator::operator!= (const Iterator& other) const {
		return !(*this == other);
	}
}
