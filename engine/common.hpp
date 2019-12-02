#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <cassert>
#include <cstdint>

#include <iostream>
#include <memory>
#include <utility>

#include <vector>
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "utils/logging.hpp"


template <typename K, typename V>
using HashMap = std::unordered_map<K, V>;

template <typename T>
using Vector = std::vector<T>;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

typedef u32 atom;


extern std::shared_ptr<utils::logging::Logger> logger;

#define LOG_ERR(...) log_error(__VA_ARGS__)
#define LOG_WARN(...) log_warning(__VA_ARGS__)
#define LOG_INFO(...) log_message(__VA_ARGS__)
#define LOG_MSG(...) log_message(__VA_ARGS__)

#define PERF_MSG_(fn, line, msg, ...) log_trace(fn, line, __VA_ARGS__)
#define PERF_MSG(msg, ...) PERF_MSG_(__FUNCTION__, __LINE__, __VA_ARGS__)


template <typename Msg, typename... Args>
inline void log_warning(const Msg& msg, Args... args) {
	logger->warn(msg, args...);
}

template <typename Msg, typename... Args>
inline void log_error(const Msg& msg, Args... args) {
	logger->error(msg, args...);
}

template <typename Msg, typename... Args>
inline void log_message(const Msg& msg, Args... args) {
	logger->message(msg, args...);
}

template <typename Msg, typename... Args>
inline void log_debug(const Msg& msg, Args... args) {
	logger->debug(msg, args...);
}

template <typename Msg, typename... Args>
inline void log_trace(const char* function, u32 line, const Msg& msg, Args... args) {
	logger->trace(function, line, msg, args...);
}


std::ostream& operator<< (std::ostream& out, const glm::vec4& v);
std::ostream& operator<< (std::ostream& out, const glm::vec3& v);
std::ostream& operator<< (std::ostream& out, const glm::vec2& v);

std::ostream& operator<< (std::ostream& out, const glm::mat4& v);

void glCheck_(const char* file, const char* function, u32 line);

#define glCheck(fn) do { fn; glCheck_(__FILE__, __FUNCTION__, __LINE__); } while(0)

template <typename Type, template <typename> typename Allocator, typename... Args>
Type* allocate(Allocator<Type>& alloc, Args... args) {
	Type* ptr = alloc.allocate();
	if(ptr)
		return new(ptr) Type(args...);
	return nullptr;
}
template <typename Type, template <typename> typename Allocator>
void deallocate(Allocator<Type>& alloc, Type*& ptr) {
	alloc.deallocate(ptr);
	ptr = nullptr;
}

template <typename T, typename... Args>
T* alloc(Args... args) {
	return new T(std::forward(args...));
}

template <typename T>
void dealloc(T* ptr) {
	delete ptr;
}

template <typename T>
T* allocate(size_t num) {
	return new T[num];
}

template <typename T>
void deallocate(T*& ptr) {
	delete[] ptr;
	ptr = nullptr;
}

enum PixelFormat {
	Red,
	Alpha,
	Depth,
	Stencil,
	Rgb,
	Rgba,
};

u32 gl_pixel_format(PixelFormat);

PixelFormat pixel_format(u32 format);


namespace std {
	template <>
	struct hash<std::pair<u32, u32>> {
		size_t operator() (const std::pair<u32, u32>& val) const;
	};
}

#endif
