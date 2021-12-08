#include "pointers.hpp"
#include "logger.hpp"

namespace t6zm
{
	pointers::pointers()
	{
		if (!this->get_swapchain())
			g_log->warning("POINTERS", "Failed to create windows.");

		this->m_hwnd = FindWindow(L"CoDBlackOps", L"Call of Duty®: Black Ops II - Zombies");
		if (!this->m_hwnd)
			g_log->warning("POINTERS", "Failed to get window handle.");

		g_pointers = this;
	}

	pointers::~pointers()
	{
		g_pointers = nullptr;
	}

	// Credits: https://github.com/Rebzzel/kiero
	bool pointers::get_swapchain()
	{
		WNDCLASSEX windowClass;
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = DefWindowProc;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = GetModuleHandle(NULL);
		windowClass.hIcon = NULL;
		windowClass.hCursor = NULL;
		windowClass.hbrBackground = NULL;
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = L"Kiero";
		windowClass.hIconSm = NULL;

		::RegisterClassEx(&windowClass);

		HWND window = ::CreateWindow(windowClass.lpszClassName, L"Kiero DirectX Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);

		HMODULE libD3D11;
		if ((libD3D11 = ::GetModuleHandle(L"d3d11.dll")) == NULL)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		void* D3D11CreateDeviceAndSwapChain;
		if ((D3D11CreateDeviceAndSwapChain = ::GetProcAddress(libD3D11, "D3D11CreateDeviceAndSwapChain")) == NULL)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0 };

		DXGI_RATIONAL refreshRate;
		refreshRate.Numerator = 60;
		refreshRate.Denominator = 1;

		DXGI_MODE_DESC bufferDesc;
		bufferDesc.Width = 100;
		bufferDesc.Height = 100;
		bufferDesc.RefreshRate = refreshRate;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SAMPLE_DESC sampleDesc;
		sampleDesc.Count = 1;
		sampleDesc.Quality = 0;

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc = sampleDesc;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = window;
		swapChainDesc.Windowed = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		IDXGISwapChain* swapChain;
		ID3D11Device* device;
		ID3D11DeviceContext* context;

		if (((long(__stdcall*)(
			IDXGIAdapter*,
			D3D_DRIVER_TYPE,
			HMODULE,
			UINT,
			const D3D_FEATURE_LEVEL*,
			UINT,
			UINT,
			const DXGI_SWAP_CHAIN_DESC*,
			IDXGISwapChain**,
			ID3D11Device**,
			D3D_FEATURE_LEVEL*,
			ID3D11DeviceContext**))(D3D11CreateDeviceAndSwapChain))(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevels, 2, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &featureLevel, &context) < 0)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		this->m_swapchain_methods = (uint32_t*)::calloc(205, sizeof(uint32_t));
		::memcpy(this->m_swapchain_methods, *(uint32_t**)swapChain, 18 * sizeof(uint32_t));
		::memcpy(this->m_swapchain_methods + 18, *(uint32_t**)device, 43 * sizeof(uint32_t)); // unused
		::memcpy(this->m_swapchain_methods + 18 + 43, *(uint32_t**)context, 144 * sizeof(uint32_t));

		swapChain->Release();
		swapChain = NULL;

		device->Release();
		device = NULL;

		context->Release();
		context = NULL;

		::DestroyWindow(window);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

		return true;
	}
}