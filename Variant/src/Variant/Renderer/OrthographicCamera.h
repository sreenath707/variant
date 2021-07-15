#pragma once
#include<glm/glm.hpp>
#include<glm/mat4x4.hpp>


namespace Variant {
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float up, float down);
		void setPosition(glm::vec3 position);
		inline void setRotation(float rotation) { m_rotation = rotation; RecalculateMatrix(); }


		inline glm::vec3 getPosition() { return m_position; }
		inline glm::mat4 getProjectionView() { return m_ViewProjection; }

	private:
		void RecalculateMatrix();
	private:
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_ViewProjection;

		glm::vec3 m_position = {0.0,0.0,0.0};
		float m_rotation = 0.0f;
	};
}