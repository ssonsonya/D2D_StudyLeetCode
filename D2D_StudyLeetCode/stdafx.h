#pragma once
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN  

///////////////////////////////////////////////////////
/// Standard Application Framework Extension Header ///
///////////////////////////////////////////////////////

// Windows Header
#include <windows.h>

// C Runtime Header
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cassert>

// C++ Runtime Header
#include <string>

using namespace std;

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