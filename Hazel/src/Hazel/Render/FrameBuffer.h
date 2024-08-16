#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel {
	struct FrameBufferSpecification {
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class FrameBuffer {
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		//virtual FrameBufferSpecification& GetSpecfication() = 0;
		virtual const FrameBufferSpecification& GetSpecfication() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);
	};
}