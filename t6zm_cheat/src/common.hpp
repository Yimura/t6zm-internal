#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <Windows.h>

#include <atomic>

#include <filesystem>
#include <fstream>

#include <thread>

#include <nlohmann/json.hpp>
#include <imgui.h>

using namespace std::chrono_literals;

inline HMODULE g_hmodule;
inline HANDLE g_thread;
inline DWORD g_thread_id;

inline std::atomic<bool> g_running = true;