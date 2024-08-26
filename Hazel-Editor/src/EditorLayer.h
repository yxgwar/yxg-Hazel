#pragma once
#include "Hazel.h"

namespace Hazel {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		OrthographicCameraController m_CameraController;

		Ref<FrameBuffer> m_FrameBuffer;
		Ref<Shader> m_Shader;
		Ref<Texture2D> m_Texture;
		Ref<VertexArray> m_SquareVA;

		bool m_ViewportFocused = false, m_ViewportHovered = false;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec4 m_SquareColor = { 0.2f, 0.2f, 0.8f, 1.0f };

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
	};

}