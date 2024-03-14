#include "stdafx.h"
#include "Program/Window.h"

// Extern Global (stdafx)
HWND g_handle = nullptr;
float g_winWidth = WIN_DEFAULT_WIDTH;
float g_winHeight = WIN_DEFAULT_HEIGHT;

/// <summary>
/// Defines basic window desc. Generates and Run Program window
/// </summary>
/// <param name="hInstance">Program Handle Instance - Permalink and starting point of program of (Received from OS)</param>
/// <param name="hPrevInstance">hInstance in 16bit OS Env</param>
/// <param name="lpCmdLine">Receive Command Param</param>
/// <param name="nCmdShow">How to show Window</param>
/// <returns></returns>
int APIENTRY wWinMain(  _In_ HINSTANCE hInstance,
                        _In_opt_ HINSTANCE hPrevInstance,
                        _In_ LPWSTR    lpCmdLine,
                        _In_ int       nCmdShow)
{
    WinDesc desc;
    desc.appName = L"D2D_CodeLeet";
    desc.instance = hInstance;
    desc.handle = nullptr;
    desc.width = WIN_DEFAULT_WIDTH;
    desc.height = WIN_DEFAULT_HEIGHT;

    Window* window = new Window(desc);
    WPARAM wParam = window->Run();
    SAFE_DELETE(window);

    return (int)wParam;
}