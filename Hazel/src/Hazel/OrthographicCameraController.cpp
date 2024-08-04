#include <hzpch.h>
#include "OrthographicCameraController.h"

#include "Hazel/Input.h"
#include "Hazel/KeyCodes.h"

namespace Hazel {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
			m_AspectRatio(aspectRatio), m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(HZ_KEY_A)) {
			m_CameraPosition.x -= m_CameraSpeed * ts;
		}
		else if (Input::IsKeyPressed(HZ_KEY_D)) {
			m_CameraPosition.x += m_CameraSpeed * ts;
		}
		if (Input::IsKeyPressed(HZ_KEY_W)) {
			m_CameraPosition.y += m_CameraSpeed * ts;
		}
		else if (Input::IsKeyPressed(HZ_KEY_S)) {
			m_CameraPosition.y -= m_CameraSpeed * ts;
		}

		if (m_Rotation) {
			if (Input::IsKeyPressed(HZ_KEY_Q)) {
				m_CameraRotation += m_CameraRotationSpeed * ts;
			}
			else if (Input::IsKeyPressed(HZ_KEY_E)) {
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			}
			m_Camera.SetRotation(m_CameraRotation);
		}
		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatch(e);
		dispatch.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatch.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}
	
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel = std::max(m_ZoomLevel - e.GetYOffest() * 0.5f, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		m_CameraSpeed = m_ZoomLevel;
		return false;
	}
	
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = static_cast<float>(e.GetWidth()) / e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}