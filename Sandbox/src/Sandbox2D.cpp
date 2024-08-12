#include "Sandbox2D.h"
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(2560.0f / 1440.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_Texture = Hazel::Texture2D::Create("assets/textures/2.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hazel::RenderCommand::Clear();

	static float rotation = 0.0f;
	rotation += ts * 20;

	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Hazel::Renderer2D::DrawRotatedQuad({ -0.5f, 0.0f }, { 0.5f, 0.5f }, rotation, { 0.2f,0.2f,0.8f,1.0f });
	//Hazel::Renderer2D::DrawQuad({ -0.5f, 0.0f }, { 0.5f, 0.5f }, { 0.2f,0.2f,0.8f,1.0f });
	Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f,0.2f,0.2f,1.0f });
	Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture, 10.0f);
	Hazel::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}
