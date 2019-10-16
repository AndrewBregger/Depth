#ifndef NONCOPYABLE_HPP_
#define NONCOPYABLE_HPP_

namespace utils {
	/// A class to remove function so that a derived type cannot
	/// be copied but can be moved.
	class NonCopyable {
		public:
			NonCopyable() = default;

			NonCopyable(NonCopyable&&) = default;

			~NonCopyable() = default;

		private:
			NonCopyable(const NonCopyable&) = delete;
			NonCopyable operator= (const NonCopyable&) = delete;
	};
}

#endif
