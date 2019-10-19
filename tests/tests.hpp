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
