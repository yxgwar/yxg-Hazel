#include "hzpch.h"
#include "OpenGlVertexArray.h"

#include <glad/glad.h>

namespace Hazel {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
		case Hazel::ShaderDataType::Float:
			return GL_FLOAT;
		case Hazel::ShaderDataType::Float2:
			return GL_FLOAT;
		case Hazel::ShaderDataType::Float3:
			return GL_FLOAT;
		case Hazel::ShaderDataType::Float4:
			return GL_FLOAT;
		case Hazel::ShaderDataType::Mat3:
			return GL_FLOAT;
		case Hazel::ShaderDataType::Mat4:
			return GL_FLOAT;
		case Hazel::ShaderDataType::Int:
			return GL_INT;
		case Hazel::ShaderDataType::Int2:
			return GL_INT;
		case Hazel::ShaderDataType::Int3:
			return GL_INT;
		case Hazel::ShaderDataType::Int4:
			return GL_INT;
		case Hazel::ShaderDataType::Bool:
			return GL_BOOL;
		default:
			HZ_CORE_ASSERT(false, "UnKnown ShaderDataType!");
			return 0;
		}
	}

	OpenGlVertexArray::OpenGlVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGlVertexArray::~OpenGlVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGlVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGlVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	void OpenGlVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offest);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}
	void OpenGlVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}