#include "vrpch.h"
#include "Variant/core/input.h"
#include "Variant/core/keyCodes.h"
#include "Variant/Events/mouseEvent.h";
#include "OrthographicCameraController.h"

namespace Variant {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio,bool isRotation )
		:m_aspectRatio(aspectRatio),m_camera(-m_zoomlevel, m_zoomlevel, -m_zoomlevel / m_aspectRatio, m_zoomlevel / m_aspectRatio),m_isRotation(isRotation)
	{
		
	}

	void OrthographicCameraController::OnUpdate(deltaTime dt)
	{
		if (input::isKeyPressed(VR_KEY_A))
			m_cameraPosition.x -= 5.0f * float(dt);
		else if (input::isKeyPressed(VR_KEY_D))
			m_cameraPosition.x += 5.0f * float(dt);

		if (input::isKeyPressed(VR_KEY_W))
			m_cameraPosition.y += 5.0f * float(dt);
		else if (input::isKeyPressed(VR_KEY_S))
			m_cameraPosition.y -= 5.0f * float(dt);

		m_camera.setPosition(m_cameraPosition);

		if (m_isRotation)
		{
			if (input::isKeyPressed(VR_KEY_E))
				m_cameraRotation += 245 * float(dt);
			else if (input::isKeyPressed(VR_KEY_Q))
				m_cameraRotation -= 245 * float(dt);

			m_camera.setRotation(m_cameraRotation);
		}
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<mouseScrollEvent>(std::bind(&OrthographicCameraController::OnMouseScrolled, this, std::placeholders::_1));
	}

	bool OrthographicCameraController::OnMouseScrolled(mouseScrollEvent& e)
	{
		m_zoomlevel -= e.GetYOffset()*0.1;	
		m_zoomlevel = std::max(m_zoomlevel, 0.25f);
		m_camera.setProjectionMatrix(-m_zoomlevel, m_zoomlevel, -m_zoomlevel/m_aspectRatio , m_zoomlevel/m_aspectRatio);
		return true;
	}
	void OrthographicCameraController::SetAspectRatio(float aspcetRatio)
	{
		m_aspectRatio = aspcetRatio;
		m_camera.setProjectionMatrix(-m_zoomlevel, m_zoomlevel, -m_zoomlevel / m_aspectRatio, m_zoomlevel / m_aspectRatio);
	}
}

