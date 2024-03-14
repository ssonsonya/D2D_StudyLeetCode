#include "stdafx.h"
#include "Window.h"

// Window Validation Check
bool Window::m_isWindowCreated = false;

Window::Window(WinDesc initDesc)
{
    m_desc = initDesc;

    WORD wHr = MyRegisterClass(m_desc);
    assert(wHr != 0);

    m_desc.handle = CreateWindowExW
    (
        WS_EX_APPWINDOW,
        m_desc.appName.c_str(),
        m_desc.appName.c_str(),
        WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        nullptr,
        (HMENU)nullptr,
        m_desc.instance,
        nullptr
    );

    RECT rect = { 0, 0, (LONG)m_desc.width, (LONG)m_desc.height };

    UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)m_desc.width) / 2;
    UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)m_desc.height) / 2;

    AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, 0);

    MoveWindow(m_desc.handle, centerX, centerY, rect.right - rect.left, rect.bottom - rect.top, true);

    ShowWindow(m_desc.handle, SW_SHOWNORMAL);

    UpdateWindow(m_desc.handle);

    ShowCursor(true);
}

Window::~Window()
{
    DestroyWindow(m_desc.handle);
    UnregisterClassW(m_desc.appName.c_str(), m_desc.instance);
}

ATOM Window::MyRegisterClass(WinDesc desc)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEXW);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
    wcex.lpfnWndProc = WndProc;

    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;

    wcex.hInstance = desc.instance;
    wcex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = desc.appName.c_str();
    wcex.hIconSm = wcex.hIcon;

    return RegisterClassExW(&wcex);
}

WPARAM Window::Run()
{
    m_isWindowCreated = true;

    MSG msg = { 0 };
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            GRAPHICS->Begin();
            GRAPHICS->End();
        }
    }

    return msg.wParam;
}

LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    ZeroMemory(&ps, sizeof(ps));

    switch (message)
    {
    case WM_CREATE:
        g_handle = handle;
        break;
    case WM_SIZE:
        g_winWidth = LOWORD(lParam);
        g_winHeight = HIWORD(lParam);
        GRAPHICS->Resize(g_winWidth, g_winHeight);
        break;
    case WM_CLOSE:
    case WM_DESTROY:
        PostQuitMessage(0);

        return 0;
    }

    return DefWindowProc(handle, message, wParam, lParam);
}
