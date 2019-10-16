#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_

#include <typeinfo>

#include "noncopyable.hpp"
#include "common.hpp"

namespace utils {
	template <typename Type>
	class Singleton : private utils::NonCopyable {
		public:
			Singleton() : utils::NonCopyable() {
				if(instance == nullptr) {
					LOG_ERR("Creating a second instance: {}", typeid(Type).name());
					return;
				}
				instance = static_cast<Type*>(this);
			}

			~Singleton() {
				instance = nullptr;
			}

			static Type* get() {
				return instance;
			}

		private:
			static Type* instance;
	};

	template <class Type>
	Type* Singleton<Type>::instance = nullptr;
}
#endif
