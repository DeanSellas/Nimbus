#include "pch.h"
#include "Log.h"

namespace Nimbus
{
	Ref<spdlog::logger> Log::s_CoreLogger, Log::s_ClientLogger;
	Ref<spdlog::sinks::wincolor_stdout_sink_st> Log::sink;

	void Log::Init() {
		AllocConsole();
		sink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_st>();
		// sets pattern to be, color([timestamp] loggerName: message)
		spdlog::set_pattern("%^[%T] %n || %v%$");

		s_CoreLogger = std::make_shared<spdlog::logger>("Engine", sink);
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>("Client", sink);
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}