#include "vrpch.h"
#include "imguiLayer.h"
#include "Variant/Application.h"

//keyTyped event not working should debug!!!!!!!!!!!!!!!!!!!!!!!!!!!

namespace Variant {
	bool imguiLayer::OnKeyPressedEvent(keyPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.getKeyCode()] = true;
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}
	bool imguiLayer::OnKeyReleasedEvent(keyReleaseEvent& event)
	{

		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.getKeyCode()] = false;
		return false;
	}
	bool imguiLayer::OnKeyTypedEvent(keyTypedEvent& event)
	{
		std::cout << "this is ok" << std::endl;
		ImGuiIO& io = ImGui::GetIO();
		int keycode = event.getKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);
		return false;
	}
	bool imguiLayer::OnMousePressedEvent(mouseClickEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = true;
		return false;
	}
	bool imguiLayer::OnMouseReleasedEvent(mouseReleaseEvent& event)
	{

		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = false;
		return false;
	}
	bool imguiLayer::OnMouseScrollEvent(mouseScrollEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += event.GetXOffset();
		io.MouseWheel += event.GetYOffset();
		return false;
	}
	bool imguiLayer::OnWindowResizeEvent(WindowResizeEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		return false;
	}
	bool imguiLayer::OnMouseMovedEvent(mousePosEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.GetX(), event.GetY());
		return false;
	}
	void imguiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		GLFWwindow* window = Application::Get().GetWindow().GetWindow();
		ImGui_ImplOpenGL3_Init("#version 410");
	}
	void imguiLayer::OnDetach()
	{
		
	}
	void imguiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().getwidth(),app.GetWindow().getheight());
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void imguiLayer::OnImGuiRender()
	{

	}
	void imguiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<keyPressedEvent>(std::bind(&imguiLayer::OnKeyPressedEvent,this, std::placeholders::_1));
		dispatcher.dispatch<keyTypedEvent>(std::bind(&imguiLayer::OnKeyTypedEvent, this, std::placeholders::_1));
		dispatcher.dispatch<keyReleaseEvent>(std::bind(&imguiLayer::OnKeyReleasedEvent, this, std::placeholders::_1));
		dispatcher.dispatch<mouseClickEvent>(std::bind(&imguiLayer::OnMousePressedEvent, this, std::placeholders::_1));
		dispatcher.dispatch<mouseScrollEvent>(std::bind(&imguiLayer::OnMouseScrollEvent, this, std::placeholders::_1));
		dispatcher.dispatch<mouseReleaseEvent>(std::bind(&imguiLayer::OnMouseReleasedEvent, this, std::placeholders::_1));
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&imguiLayer::OnWindowResizeEvent, this, std::placeholders::_1));
		dispatcher.dispatch<mousePosEvent>(std::bind(&imguiLayer::OnMouseMovedEvent, this, std::placeholders::_1));
	}
}