#pragma once
#include "Variant/core/deltaTime.h";
#include "Variant/Renderer/OrthographicCamera.h";
#include "Variant/Events/Event.h";
#include <glm/glm.hpp>

namespace Variant {
	class OrthographicCameraController
	{
	private:
		float m_aspectRatio = 16.0f / 9.0f;
		float m_zoomlevel=1;
		glm::vec3 m_cameraPosition = { 0.0,0.0,0.0 };
		float m_cameraRotation = 0;
		OrthographicCamera m_camera;
		float m_translationSpeed = 1.0f;
		float m_roationSpeed = 1.0f;
		bool m_isRotation;

	public:
		
		OrthographicCameraController(float aspectRatio, bool isRotation = false);
		void OnUpdate(deltaTime dt);
		inline OrthographicCamera getCamera()const { return m_camera; }
		void OnEvent(Event& e);
		bool OnMouseScrolled(mouseScrollEvent& e);
		void SetAspectRatio(float aspcetRatio);
	};
}
