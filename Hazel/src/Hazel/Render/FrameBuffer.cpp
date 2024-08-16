#include <hzpch.h>
#include "FrameBuffer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"
#include "Hazel/Render/Renderer.h"

namespace Hazel {
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "Not Supported!");
			return nullptr;
		case RendererAPI::API::OpenGl:
			return std::make_shared<OpenGLFrameBuffer>(spec);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}