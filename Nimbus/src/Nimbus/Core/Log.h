#pragma once
#define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#include "Nimbus.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/wincolor_sink.h"

namespace Nimbus
{
	class Log
	{
	public:
		static void Init();
		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::sinks::wincolor_stdout_sink_st> sink;

		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};


#define NIM_CORE_LOG Log::GetCoreLogger()
#define NIM_CLIENT_LOG Log::GetClientLogger()

#define ERROR_CHECK(check, msg) if(check) { NIM_CORE_LOG->error(msg); return false; }
}