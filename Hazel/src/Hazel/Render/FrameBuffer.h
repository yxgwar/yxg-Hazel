#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel {
	enum class FramebufferTextureFormat
	{
		None = 0,
		//Color
		RGBA8,
		RED_INTEGER,
		//Depth/stencil
		DEPTH24STENCIL8,
		//Default
		Depth = DEPTH24STENCIL8
	};

	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format)
			:TextureFormat(format) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
			:Attachments(attachments) {}

		std::vector<FramebufferTextureSpecification> Attachments;
	};

	struct FrameBufferSpecification {
		uint32_t Width, Height;
		uint32_t Samples = 1;
		FramebufferAttachmentSpecification Attachments;
		bool SwapChainTarget = false;
	};

	class FrameBuffer {
	public:
		virtual ~FrameBuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;

		//virtual FrameBufferSpecification& GetSpecfication() = 0;
		virtual const FrameBufferSpecification& GetSpecfication() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);
	};
}