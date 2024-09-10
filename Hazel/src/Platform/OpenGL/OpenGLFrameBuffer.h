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
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		inline uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { HZ_CORE_ASSERT(index < m_ColorAttachments.size(), "");  return m_ColorAttachments[index]; }
		inline const FrameBufferSpecification& GetSpecfication() const override { return m_Specification; }
	private:
		uint32_t m_RendererID = 0;
		FrameBufferSpecification m_Specification;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecs;
		FramebufferTextureSpecification m_DepthAttachmentSpec = FramebufferTextureFormat::None;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
	};
}