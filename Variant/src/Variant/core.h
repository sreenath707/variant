#pragma once
#include<stdint.h>

#ifdef VR_DLL
#define VR_API __declspec(dllexport)
#else
#define VR_API _declspec(dllimport)
#endif

#define VR_ASSERT(x,...) if(!(x))  __debugbreak();

#define BIT(x) (1<<x)

typedef uint16_t keycode;