#pragma once

#include "Variant/input.h"
#include "Variant/Application.h"
#include "GLFW/glfw3.h"

namespace Variant {
	
	class windowsInput : public input
	{
	protected:
		virtual bool isKeyPressedImpl(int keycode)override;
		virtual bool isMouseButtonPressedImpl(int button)override;
		virtual float getMouseXPosImpl() override;
		virtual float getMouseYPosImpl()override;

	};
}
