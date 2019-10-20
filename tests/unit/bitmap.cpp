#include "tests.hpp"
#include "utils/bitmap.hpp"

void test_constructor() {
	util::Bitmap bitmap;	
	TEST_ASSERT(bitmap.map != nullptr, "Bitmap::Bitmap");
}

void test_set_bit() {
	util::Bitmap bitmap;	

	bitmap.set_bit(5);

	TEST_ASSERT(bitmap.check(5), "Bitmap::set_bit");
}

void test_set_bit_large() {
	util::Bitmap bitmap(64);

	bitmap.set_bit(41);

	TEST_ASSERT(bitmap.check(41), "Bitmap::set_bit large");
}

void test_unset_bit() {
	util::Bitmap bitmap;	

	bitmap.set_bit(3);
	bitmap.unset_bit(3);

	TEST_ASSERT(!bitmap.check(3), "Bitmap::set_bit");
}

void test_unset_bit_large() {
	util::Bitmap bitmap(64);	

	bitmap.set_bit(41);
	bitmap.unset_bit(41);

	TEST_ASSERT(!bitmap.check(41), "Bitmap::set_bit large");
}

void test_first_index() {
	util::Bitmap bitmap(8);

	bitmap.set_bit(0);
	bitmap.set_bit(1);
	bitmap.set_bit(3);
	bitmap.set_bit(6);
	bitmap.set_bit(2);
	bitmap.set_bit(7);
	bitmap.set_bit(4);

	TEST_ASSERT(bitmap.first_index() == 5, "Bitmap::first_index");
}

void test_iterator() {
	util::Bitmap bitmap(8);

	bitmap.set_bit(0);
	bitmap.set_bit(2);
	bitmap.set_bit(3);
	bitmap.set_bit(4);
	bitmap.set_bit(6);
	bitmap.set_bit(7);

	bool expected[] = {true, false, true, true, true, false, true, true};
	u32 actual_index = 0;

	TEST_ITERATION_BEGIN();

	for(auto [index, value] : bitmap) {
		LOOP_ASSERT(index == actual_index and value == expected[actual_index]);
		actual_index++;
	}

	TEST_ITERATION_END("Bitmap::Iterators");
}

void test_iterator_large() {
}


int main() {
	test_constructor();

	test_set_bit();

	test_set_bit_large();

	test_unset_bit();

	test_unset_bit_large();

	test_first_index();

	test_iterator();
}

