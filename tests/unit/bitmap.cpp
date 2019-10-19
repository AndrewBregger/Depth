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


int main() {
	test_constructor();

	test_set_bit();
	test_set_bit_large();

	test_unset_bit();
	test_unset_bit_large();
}

