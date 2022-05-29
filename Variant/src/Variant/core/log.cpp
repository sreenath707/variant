#include "vrpch.h"
#include "log.h"

namespace Variant {

	 std::shared_ptr<spdlog::logger> log::m_coreLogger;
	 std::shared_ptr<spdlog::logger> log::m_clientLogger;

	 void log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		 m_coreLogger = spdlog::stdout_color_mt("Variant");
		 m_clientLogger = spdlog::stdout_color_mt("Client");
	}
}