#ifndef BITMAP_HPP_
#define BITMAP_HPP_

#include "common.hpp"

namespace util {
	u8 change_bit(u8 val, u8 offset, u8 to_set);

	struct Bitmap {
		/// Bitmap constructor.
		Bitmap(u32 size = 10);

		~Bitmap();
		
		/// The number of filled bits this bitmap currently contains.
		u32 size();

		void set_bit(u32 bit);

		void unset_bit(u32 bit);

		bool check(u32 bit);

		bool valid(u32 bit);

		void resize(u32 bit);

		static u32 compute_bytes(u32 bits);
		
		/// The number of total bits this bitmap supports.
		u32 capacity();

		u8* map{nullptr};
		u32 cap{0};
		u32 sz{0};
	};
}

#endif
