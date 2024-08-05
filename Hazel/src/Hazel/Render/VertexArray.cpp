#include <hzpch.h>
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGlVertexArray.h"

namespace Hazel {
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "Not Supported!");
			return nullptr;
		case RendererAPI::API::OpenGl:
			return std::make_shared<OpenGlVertexArray>();
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}