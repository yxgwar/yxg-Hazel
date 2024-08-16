#pragma once

#include "Hazel/Render/FrameBuffer.h"

namespace Hazel {
	class OpenGLFrameBuffer : public FrameBuffer {
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();

		void Bind() override;
		void Unbind() override;
		inline uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		inline const FrameBufferSpecification& GetSpecfication() const override { return m_Specification; }
	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthAttachment;
		FrameBufferSpecification m_Specification;
	};
}