#ifndef BITMAP_HPP_
#define BITMAP_HPP_

#include "common.hpp"

namespace util {
	u8 change_bit(u8 val, u8 offset, u8 to_set);

	struct Bitmap {
		struct Iterator {
			std::pair<u32, bool> value;
			u8* map;
			u32 cap;

			Iterator();
			Iterator(u8* map, u32 cap);


			Iterator operator++ ();
			Iterator operator++ (int);

			bool operator== (const Iterator& other) const;
			bool operator!= (const Iterator& other) const;

			std::pair<u32, bool> operator* () const;
		};

		static const u32 INVALID_INDEX = (u32) -1;

		typedef Iterator iterator;
		typedef const Iterator const_iterator;

		/// Bitmap constructor.
		Bitmap(u32 size = 8);

		~Bitmap();
		
		/// The number of filled bits this bitmap currently contains.
		u32 size();

		void set_bit(u32 bit);

		void unset_bit(u32 bit);

		bool check(u32 bit);

		bool valid(u32 bit);

		void resize(u32 bit);

		// the name is not good.
		u32 first_index();

		static u32 compute_bytes(u32 bits);
		
		/// The number of total bits this bitmap supports.
		u32 capacity();



		iterator begin();
		iterator end();

		const_iterator begin() const;
		const_iterator end() const;

		u8* map{nullptr};
		u32 cap{0};
		u32 sz{0};
	};
}

#endif
