#pragma once
#include "common.hpp"
#include "t6zm/player_actor.hpp"

namespace t6zm
{
	class pointers
	{
	public:
		explicit pointers();
		~pointers();
	public:
		HWND m_hwnd{};

		uint32_t* m_swapchain_methods = NULL;

		PlayerActor* m_player;

	private:
		bool get_swapchain();

	};

	inline pointers* g_pointers{};
}
