#include <hzpch.h>
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGlShader.h"

namespace Hazel {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "Not Supported!");
			return nullptr;
		case RendererAPI::API::OpenGl:
			return new OpenGlShader(vertexSrc, fragmentSrc);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}