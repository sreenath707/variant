#include "..\..\Variant\src\Variant\core\Application.h"
#include <variant.h>
#include <glm/glm.hpp>


class exampleLayer : public Variant::layer
{
private:

	Variant::OrthographicCameraController m_cameraController;
	std::shared_ptr<Variant::Texture> m_texture;
    std::shared_ptr<Variant::FrameBuffer> m_frameBuffer;
    float m_viewPortWidth = 1280;
    float m_viewPortHeight = 720;

public:

	exampleLayer()
		:layer("exampleLayer"), m_cameraController(16.0f / 9.0f, false)
	{
		Variant::Renderer2D::Init();
		m_texture.reset(new Variant::Texture("Assets/Textures/batman.jpg"));
        m_frameBuffer.reset(Variant::FrameBuffer::Create(m_viewPortWidth, m_viewPortWidth));
	}

	virtual void OnAttach()override
	{
		
	}
	void OnDetach()override
	{

	}
	void OnImGuiRender()override
	{

        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        bool dock_open = true;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dock_open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::Separator();

                if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
                if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
                if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
                if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
                if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
                ImGui::Separator();

                if (ImGui::MenuItem("Close", NULL, false, dock_open != NULL))
                    dock_open = false;
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }


        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });
        ImGui::Begin("ViewPort");
        ImVec2 size = ImGui::GetContentRegionAvail();
        if (size.x != m_viewPortWidth || size.y != m_viewPortHeight)
        {
            m_viewPortWidth = size.x;
            m_viewPortHeight = size.y;
            m_frameBuffer->reValidate(m_viewPortWidth, m_viewPortHeight);
            m_cameraController.SetAspectRatio(m_viewPortWidth / m_viewPortHeight);
        }
        unsigned int texture = m_frameBuffer->getColorBufferId();
        ImGui::Image((void*)texture, { m_viewPortWidth,m_viewPortHeight }, { 0,1 }, { 1,0 });
        ImGui::End();
        ImGui::PopStyleVar();

		bool show = true;
		ImGui::ShowDemoWindow(&show);
        ImGui::End();


	}
	void OnEvent(Variant::Event& event)
	{
		m_cameraController.OnEvent(event);
	}

    virtual void OnUpdate(Variant::deltaTime dt)
    {
        m_frameBuffer->Bind();
        m_cameraController.OnUpdate(dt);

        Variant::Renderer2D::BeginScene(m_cameraController.getCamera());
        Variant::RendererCommand::clearColor();
        Variant::RendererCommand::setColor({ 0.1,0.1,0.1,1.0 });
        Variant::Renderer2D::DrawQuad({ 0.0f,0.0f,0.0f }, { 0.5f,0.5f }, 0, { 1.0f,0.2f,0.3f,1.0f });
        Variant::Renderer2D::DrawTexture({ 0.7f,-0.2f,0.0f }, { 0.5f,0.5f }, 0, m_texture);
        Variant::Renderer2D::EndScene();
        m_frameBuffer->Unbind();
    }
};


class SandBox : public Variant::Application
{


public:
	SandBox()
	{
		pushLayer(new exampleLayer());
	}

	~SandBox()
	{

	}
};


Variant::Application* Variant::CreateApplication()
{
	return new SandBox();
}


