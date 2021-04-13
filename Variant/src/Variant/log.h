#pragma once
#include "vrpch.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "core.h"

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

