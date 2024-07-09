#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		void Run();
	};

	//to be define in client
	Application* CreateApplication();
}
