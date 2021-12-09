#include "common.hpp"
#include "features.hpp"
#include "hooking.hpp"
#include "logger.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "settings.hpp"
#include "thread_pool.hpp"

DWORD WINAPI main_thread(LPVOID)
{
	using namespace t6zm;

	while (!FindWindow(L"CoDBlackOps", L"Call of Duty®: Black Ops II - Zombies"))
		std::this_thread::sleep_for(1s);

	auto logger_instance = std::make_unique<Logger>(Logger::LogLevel::Verbose);
	try
	{
		g_log->info("MAIN", "Menu Initializing...");

		auto settings_instance = std::make_unique<settings>();
		g_settings->load();
		g_log->verbose("MAIN", "Settings initialized.");

		auto pointers_instance = std::make_unique<pointers>();
		g_log->verbose("MAIN", "Pointers initialized.");

		auto renderer_instance = std::make_unique<renderer>();
		g_log->verbose("MAIN", "Renderer initialized.");

		auto hooking_instance = std::make_unique<hooking>();
		g_log->verbose("MAIN", "Hooking initialized.");

		auto thread_pool_instance = std::make_unique<thread_pool>();
		g_log->verbose("MAIN", "Thread Pool initialized.");

		g_hooking->enable();
		g_log->info("MAIN", "Hooking enabled.");

		g_thread_pool->push(features::script_run);
		g_log->verbose("MAIN", "Started threaded feature script.");

		while (g_running)
			std::this_thread::sleep_for(500ms);

		g_hooking->disable();
		g_log->info("MAIN", "Hooking disabled.");

		g_thread_pool->destroy();
		g_log->verbose("MAIN", "Destroyed thread pool.");

		thread_pool_instance.reset();
		g_log->verbose("MAIN", "Thread Pool uninitialized.");

		hooking_instance.reset();
		g_log->verbose("MAIN", "Hooking uninitialized.");

		renderer_instance.reset();
		g_log->verbose("MAIN", "Renderer uninitialized.");

		pointers_instance.reset();
		g_log->verbose("MAIN", "Pointers uninitialized.");

		g_settings->attempt_save();
		settings_instance.reset();
		g_log->verbose("MAIN", "Settings saved and uninitialized.");
	}
	catch (const std::exception& ex)
	{
		g_log->error("MAIN", "Error in main thread:\n%s", ex.what());
	}

	g_log->info("MAIN", "Leaving...");
	logger_instance.reset();

	CloseHandle(g_thread);
	FreeLibraryAndExitThread(g_hmodule, 0);
}

BOOL WINAPI DllMain(HMODULE hmod, DWORD reason, LPVOID)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hmod);

		g_hmodule = hmod;
		g_thread = CreateThread(nullptr, 0, main_thread, nullptr, 0, &g_thread_id);
		break;
	case DLL_PROCESS_DETACH:
		g_running = false;
		break;
	}
	return true;
}