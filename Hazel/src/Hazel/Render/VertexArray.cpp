#include <hzpch.h>
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGlVertexArray.h"

namespace Hazel {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			HZ_CORE_ASSERT(false, "Not Supported!");
			return nullptr;
		case RendererAPI::OpenGl:
			return new OpenGlVertexArray();
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}