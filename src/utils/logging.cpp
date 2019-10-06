#include "logging.hpp"

std::shared_ptr<utils::logging::Logger> logger;
namespace utils {
	namespace logging {
		void init_logger() {
			logger = std::make_shared<Logger>(Logger("logs/depth.log"));
		}

		Logger::Logger(const std::string& name) {
			logger = spdlog::basic_logger_mt("logger", name, false);
		}

		Logger::~Logger() = default;
	}
}
