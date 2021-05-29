#pragma once
#include "Variant/layer.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "Variant/Events/keyEvent.h"
#include "Variant/Events/mouseEvent.h"
#include "Variant/Events/ApplicationEvent.h"

namespace Variant{
	class  imguiLayer :public layer
	{
	public:
		imguiLayer();

		 void OnAttach()override;
		 void OnDetach()override;
		 void OnEvent(Event& event)override;
		 void OnImGuiRender()override;
		 void Begin();
		 void End();
	};
}
