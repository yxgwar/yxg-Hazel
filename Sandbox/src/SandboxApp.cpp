#include <Hazel.h>
#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

#include "Sandbox2D.h"

#include "Hazel/Core/EntryPoint.h"

class ExampleLayer : public Hazel::Layer {
public:
	ExampleLayer()
		: Layer("Example"), 
		m_CameraController(2560.0f/ 1440.0f)
	{
		m_VertexArray = Hazel::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		Hazel::Ref<Hazel::VertexBuffer> vertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));

		Hazel::BufferLayout layout = {
			{Hazel::ShaderDataType::Float3, "a_Position"},
			{Hazel::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };

		Hazel::Ref<Hazel::IndexBuffer> indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Hazel::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Hazel::Ref<Hazel::VertexBuffer> squareVB = Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		squareVB->SetLayout({
			{Hazel::ShaderDataType::Float3, "a_Position"},
			{Hazel::ShaderDataType::Float2, "a_TexCoord"}
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0,1,2,2,3,0 };

		Hazel::Ref<Hazel::IndexBuffer> squareIB = Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 460 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Hazel::Shader::Create("VertexTriangle", vertexSrc, fragmentSrc);

		std::string vertexSrc2 = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 460 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec4 u_Color;
			
			void main()
			{
				color = u_Color;
			}
		)";

		m_Shader2 = Hazel::Shader::Create("FlatColor", vertexSrc2, fragmentSrc2);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Hazel::Texture2D::Create("assets/textures/2.png");
		m_TextureAlpha = Hazel::Texture2D::Create("assets/textures/1.png");

		std::dynamic_pointer_cast<Hazel::OpenGlShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGlShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Hazel::Timestep ts) override {
		//HZ_TRACE("Delta time: {0}s", ts.GetSeconds());
		m_CameraController.OnUpdate(ts);

		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();

		Hazel::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8f, 0.2f, 0.2f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.2f, 0.8f, 1.0f);

		std::dynamic_pointer_cast<Hazel::OpenGlShader>(m_Shader2)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGlShader>(m_Shader2)->UploadUniformFloat4("u_Color", m_SquareColor);

		for (int x = 0; x < 20; x++)
		{
			for (int y = 0; y < 20; y++)
			{
				glm::vec3 pos = glm::vec3(0.11f * x, 0.11f * y, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Hazel::Renderer::Submit(m_SquareVA, m_Shader2, transform);
			}
		}
		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Hazel::Renderer::Submit(m_SquareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_TextureAlpha->Bind();
		Hazel::Renderer::Submit(m_SquareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Hazel::Renderer::Submit(m_VertexArray, m_Shader);

		Hazel::Renderer::EndScene();
	}

	void OnImGuiRender() override{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Hazel::Event& e) override {
		m_CameraController.OnEvent(e);
	}
private:
	Hazel::ShaderLibrary m_ShaderLibrary;

	Hazel::Ref<Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;

	Hazel::Ref<Hazel::Shader> m_Shader2;
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;

	Hazel::Ref<Hazel::Texture2D> m_Texture, m_TextureAlpha;

	Hazel::OrthographicCameraController m_CameraController;

	glm::vec4 m_SquareColor = { 0.2f, 0.2f, 0.8f, 1.0f };
};

class Sandbox : public Hazel::Application {
public:
	Sandbox() {
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {

	}
};

Hazel::Application* Hazel::CreateApplication() {
	return new Sandbox();
}