#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <cassert>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <utility>

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

template <typename T, typename... Args>
T* alloc(Args... args) {
	return new T(std::forward(args...));
}

#endif
