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
		virtual void Resize(uint32_t width, uint32_t height) override;
		inline uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		inline const FrameBufferSpecification& GetSpecfication() const override { return m_Specification; }
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
		FrameBufferSpecification m_Specification;
	};
}