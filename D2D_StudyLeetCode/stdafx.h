#pragma once
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN  

///////////////////////////////////////////////////////
/// Standard Application Framework Extension Header ///
///////////////////////////////////////////////////////

//PopUpConsole
#ifdef _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif

// Windows Header
#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>

// C Runtime Header
#include <cassert>

// C++ Runtime Header
#include <string>
#include <string>
#include <chrono>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <array>
#include <fstream>

using namespace std;

// Libraries

// WRL : to use COM Interface
#include <wrl.h>
using namespace Microsoft;
using namespace WRL;

// DirectX D3D11
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")


// DirectXTK 
#include "_Libraries/DirectXTK/SimpleMath.h"
using namespace DirectX;
using namespace SimpleMath;

// DirectXTex
#include "_Libraries/DirectXTex/DirectXTex.h"
#ifdef _M_X64
#ifdef _DEBUG
#pragma comment(lib, "_Libraries/DirectXTex/x64/Debug/DirectXTex.lib")
#elif NDEBUG
#pragma comment(lib, "_Libraries/DirectXTex/x64/Release/DirectXTex.lib")
#endif

#elif _M_IX86
#ifdef _DEBUG
#pragma comment(lib, "_Libraries/DirectXTex/Win32/Debug/DirectXTex.lib")
#elif NDEBUG
#pragma comment(lib, "_Libraries/DirectXTex/Win32/Release/DirectXTex.lib")
#endif

#endif

// Macros

// Utilities
#define CHECK(hr) {assert(SUCCEEDED(hr));}
#define SUPER __super
#define SAFE_DELETE(p) {if(p){delete(p); p = nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p){delete[](p); p = nullptr;}}
#define SAFE_RELEASE(p) {if(p) { p->Release(); p =nullptr;}}

// Window
#define WIN_DEFAULT_WIDTH 1280
#define WIN_DEFAULT_HEIGHT 720
#define WIN_CENTER_X (WIN_DEFAULT_WIDTH / 2)
#define WIN_CENTER_Y (WIN_DEFAULT_HEIGHT / 2)

// Singleton Template
#define DECLARE_SINGLETON(CLASS_NAME)							     \
private:														     \
CLASS_NAME();													     \
~CLASS_NAME();														 \
public:																 \
	CLASS_NAME(const CLASS_NAME& other) = delete;					 \
	CLASS_NAME& operator=(const CLASS_NAME& other) = delete;		 \
	CLASS_NAME(const CLASS_NAME&& other) = delete;					 \
	CLASS_NAME& operator=(const CLASS_NAME&& other) = delete;	     \
public:																 \
static CLASS_NAME* Get()											 \
{																	 \
	static CLASS_NAME instance;										 \
	return &instance;												 \
}

// Extern Global
extern HWND g_handle;
extern float g_winWidth;
extern float g_winHeight;

// Graphics
#include "Program/Graphics.h"
#define GRAPHICS Graphics::Get()
#define DEVICE Graphics::GetDevice()
#define DC Graphics::GetDC()