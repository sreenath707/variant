#include "vrpch.h"
#include "OrthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Variant {
    OrthographicCamera::OrthographicCamera(float left, float right, float down, float up)
        :m_projectionMatrix(glm::ortho(left, right, down, up)),m_viewMatrix(1.0)
    {
        m_ViewProjection = m_projectionMatrix * m_viewMatrix;
    }


    void OrthographicCamera::setPosition(glm::vec3 position)
    {
        m_position = position;
        RecalculateMatrix();
    }


    void OrthographicCamera::RecalculateMatrix()
    {
        glm::mat4 transform =  glm::rotate(glm::mat4(1.0), glm::radians(m_rotation), glm::vec3(0.0, 0.0, 1.0))
                                    * glm::translate(glm::mat4(1.0), m_position);
        m_viewMatrix = glm::inverse(transform);
        m_ViewProjection = m_projectionMatrix * m_viewMatrix;
    }

    void OrthographicCamera::setProjectionMatrix(float left, float right, float down, float up) 
    { 
        m_projectionMatrix = glm::ortho(left, right, down, up);
        m_ViewProjection = m_projectionMatrix * m_viewMatrix;
    }

}
