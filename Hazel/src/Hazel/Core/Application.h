#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Core/LayerStack.h"
#include "Hazel/Core/Window.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/Core/Timestep.h"

#include "Hazel/Render/Shader.h"
#include "Hazel/Render/Buffer.h"
#include "Hazel/Render/VertexArray.h"
#include "Hazel/Render/OrthographicCamera.h"

namespace Hazel {
	class Application
	{
	public:
		Application(const std::string& name = "Hazel App");
		virtual ~Application();
		void Run();
		void Close();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	//to be define in client
	Application* CreateApplication();
}
