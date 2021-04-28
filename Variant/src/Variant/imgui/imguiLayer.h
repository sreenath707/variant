#pragma once
#include "Variant/layer.h"
#include "imgui.h"
#include "Variant/opengl/imgui_impl_opengl3.h"
#include "Variant/Events/keyEvent.h"
#include "Variant/Events/mouseEvent.h"
#include "Variant/Events/ApplicationEvent.h"

namespace Variant{
	class VR_API imguiLayer :public layer
	{
		bool OnKeyPressedEvent(keyPressedEvent& event);
		bool OnKeyReleasedEvent(keyReleaseEvent& event);
		bool OnKeyTypedEvent(keyTypedEvent& event);
		bool OnMousePressedEvent(mouseClickEvent& event);
		bool OnMouseReleasedEvent(mouseReleaseEvent& event);
		bool OnMouseScrollEvent(mouseScrollEvent& event);
		bool OnWindowResizeEvent(WindowResizeEvent& event);
		bool OnMouseMovedEvent(mousePosEvent& event);

	public:
		imguiLayer()
			:layer("imguiLayer"){}

		 void OnAttach()override;
		 void OnDetach()override;
		 void OnUpdate()override;
		 void OnImGuiRender()override;
		 void OnEvent(Event& event)override;
	};
}
