#include <hzpch.h>
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel {
	VertexBuffer* VertexBuffer::Create(float* vertics, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			HZ_CORE_ASSERT(false, "Not Supported!");
			return nullptr;
		case RendererAPI::OpenGl:
			return new OpenGLVertexBuffer(vertics, size);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			HZ_CORE_ASSERT(false, "Not Supported!");
			return nullptr;
		case RendererAPI::OpenGl:
			return new OpenGLIndexBuffer(indices, size);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void BufferLayout::CalculateOffestsAndStride()
	{
		uint32_t offest = 0;
		m_Stride = 0;
		for (auto& element : m_Elements) {
			element.Offest = offest;
			offest += element.Size;
			m_Stride += element.Size;
		}
	}
}