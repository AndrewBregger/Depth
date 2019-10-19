#ifndef UTILS_LOGGING_HPP_
#define UTILS_LOGGING_HPP_

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

// #include "common.hpp"

namespace utils {
	namespace logging {

		void init_logger();

		class Logger {
			public:
				explicit Logger(const std::string& name);
				~Logger();
					
				template<typename... Args>
				void warn(const std::string& msg, Args... args) {
					if(to_console) {
						spdlog::warn(msg, args...);
					}
					else {
						logger->warn(msg.c_str(), args...);
					}
				}

				template<typename... Args>
				void error(const std::string& msg, Args... args) {
					logger->error(msg.c_str(), args...);
				}

				template <typename... Args>
				void debug(const std::string& msg, Args... args) {
					logger->debug(msg.c_str(), args...);
				}

				template<typename... Args>
				void message(const std::string& msg, Args... args) {
					spdlog::info(msg.c_str(), args...);
				}

				template<typename... Args>
				void trace(const char* function, int line, const std::string& msg, Args... args) {
					std::string m = "Function {} Line {} | " + msg;
					logger->trace(m.c_str(), function, line, args...);
				}

				inline void send_to_console(bool console) {
					to_console = console;
				}

				inline void send_debug_to_console(bool console) {
					debug_to_console = console;
				}

				inline void send_error_to_console(bool console) {
					err_to_console = console;
				}

			private:
				// send everying to console
				bool to_console{false};
				// send only debug to console
				bool debug_to_console{true};
				// send error messages to console
				bool err_to_console{false};
				// Crash on error messages.
				bool err_crash{false};
				/// file sink
				std::shared_ptr<spdlog::logger> logger;
		};
	}
}

#endif
