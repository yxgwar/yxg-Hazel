#pragma once
#include "Hazel.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Hazel/Render/EditorCamera.h"

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
		bool OnKeyPressed(KeyPressedEvent& e);
		void NewScene();
		void OpenScene();
		void SaveSceneAs();
		//OrthographicCameraController m_CameraController;

		Ref<FrameBuffer> m_FrameBuffer;
		Ref<Shader> m_Shader;
		Ref<Texture2D> m_Texture;
		Ref<VertexArray> m_SquareVA;

		bool m_ViewportFocused = false, m_ViewportHovered = false;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];
		glm::vec4 m_SquareColor = { 0.2f, 0.2f, 0.8f, 1.0f };

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;

		EditorCamera m_EditorCamera;

		int m_GizmoType = -1;

		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}