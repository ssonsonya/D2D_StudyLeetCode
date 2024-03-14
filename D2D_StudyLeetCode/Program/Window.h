#pragma once
#include "stdafx.h"

struct WinDesc
{
	wstring appName = L"";
	HINSTANCE instance = nullptr;
	HWND handle = nullptr;
	float width = 0.0f;
	float height = 0.0f;
};

/// <summary>
/// Decides Program window creation. 
/// Generated and called from Main.cpp with init value of WinDesc given as an argument
/// </summary>
class Window
{
public:
	Window(WinDesc desc);
	~Window();

public:
	ATOM MyRegisterClass(WinDesc desc);
	WPARAM Run();

private:
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

private:
	WinDesc m_desc;

	static bool m_isWindowCreated;
};