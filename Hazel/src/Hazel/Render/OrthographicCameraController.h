#pragma once

#include "Hazel/Render/OrthographicCamera.h"
#include "Hazel/Core/Timestep.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel {
	struct OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};

	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		inline OrthographicCamera& GetCamera() { return m_Camera; }
		inline const OrthographicCamera& GetCamera() const { return m_Camera; }

		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraSpeed = 1.0f;
		float m_CameraRotation = 0.0f;
		float m_CameraRotationSpeed = 90.0f;

		OrthographicCamera m_Camera;
		OrthographicCameraBounds m_Bounds;
	};
}