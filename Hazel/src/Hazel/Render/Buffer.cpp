#include <hzpch.h>
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel {
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "Not Supported!");
			return nullptr;
		case RendererAPI::API::OpenGl:
			return std::make_shared<OpenGLVertexBuffer>(size);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<VertexBuffer> VertexBuffer::Create(float* vertics, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "Not Supported!");
			return nullptr;
		case RendererAPI::API::OpenGl:
			return std::make_shared<OpenGLVertexBuffer>(vertics, size);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "Not Supported!");
			return nullptr;
		case RendererAPI::API::OpenGl:
			return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void BufferLayout::CalculateOffsetsAndStride()
	{
		uint32_t Offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements) {
			element.Offset = Offset;
			Offset += element.Size;
			m_Stride += element.Size;
		}
	}
}