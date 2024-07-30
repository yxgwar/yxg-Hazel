#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Hazel/LayerStack.h"
#include "Window.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/Core/Timestep.h"

#include "Hazel/Render/Shader.h"
#include "Hazel/Render/Buffer.h"
#include "Hazel/Render/VertexArray.h"
#include "Hazel/Render/OrthographicCamera.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	//to be define in client
	Application* CreateApplication();
}
