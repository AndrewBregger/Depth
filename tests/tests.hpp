#ifndef TEST_HPP_
#define TEST_HPP_

#include <iostream>

#define TEST_ASSERT(cond, message)  do { \
			if(!(cond)) { \
				std::cout << "Failed expr: " << #cond << "| " << message << std::endl; \
			} \
			else { \
				std::cout << message << ": ok" << std::endl; \
			}\
		} while(0)

#endif

#define TEST_ITERATION_BEGIN() bool __condition_value__ = true; u32 __iteration__ = 0

#define LOOP_ASSERT(cond) do { \
	if(!cond and __condition_value__) { \
		std::cout << "Failed at iteration " << __iteration__ << std::endl; \
	} \
	__condition_value__ = __condition_value__ && cond; \
	__iteration__++; \
} while(0)

#define TEST_ITERATION_END(message) TEST_ASSERT(__condition_value__, message)
