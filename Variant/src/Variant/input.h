#pragma once
#include "core.h"


namespace Variant {
	class VR_API input
	{
	private:
		static input* s_instance;
	public:
		static bool isKeyPressed(int keycode) { return s_instance->isKeyPressedImpl(keycode); }
		static bool isMouseButtonPressed(int button) { return s_instance->isMouseButtonPressedImpl(button); }
		static float getMouseXPos() { return s_instance->getMouseXPosImpl(); }
		static float getMouseYPos() { return s_instance->getMouseYPosImpl(); }

	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual float getMouseXPosImpl() = 0;
		virtual float getMouseYPosImpl() = 0;



	};
}