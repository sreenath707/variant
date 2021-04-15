#pragma once
#include "vrpch.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "core.h"

#define VR_client_warn(...) Variant::log::getClientLogger()->warn(__VA_ARGS__) 
#define VR_client_info(...) Variant::log::getClientLogger()->info(__VA_ARGS__) 
#define VR_client_error(...) Variant::log::getClientLogger()->error(__VA_ARGS__) 

#define VR_core_warn(...)  Variant::log::getCoreLogger()->warn(__VA_ARGS__) 
#define VR_core_info(...)  Variant::log::getCoreLogger()->info(__VA_ARGS__) 
#define VR_core_error(...) Variant::log::getCoreLogger()->error(__VA_ARGS__) 

namespace Variant {

	class VR_API log
	{
	
		static std::shared_ptr<spdlog::logger> m_coreLogger;
		static std::shared_ptr<spdlog::logger> m_clientLogger;
	public:

		static void init();
		static std::shared_ptr<spdlog::logger> getCoreLogger() { return m_coreLogger; }
		static std::shared_ptr<spdlog::logger> getClientLogger() { return m_clientLogger; }

	};

}

