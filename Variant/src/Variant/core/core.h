#pragma once
#include<stdint.h>


#define VR_ASSERT(x,...) if(!(x))  __debugbreak();

#define BIT(x) (1<<x)

typedef uint16_t keycode;