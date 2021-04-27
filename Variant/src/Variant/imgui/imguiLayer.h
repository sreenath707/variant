#pragma once
#include "Variant/layer.h"
#include "imgui.h"
#include "Variant/opengl/imgui_impl_opengl3.h"

namespace Variant{
	class VR_API imguiLayer :public layer
	{
	public:
		imguiLayer()
			:layer("imguiLayer"){}

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnImGuiRender();
		virtual void OnEvent(Event& event);
	};
}
