#pragma once

#ifdef VR_DLL
#define VR_API __declspec(dllexport)
#else
#define VR_API _declspec(dllimport)
#endif
