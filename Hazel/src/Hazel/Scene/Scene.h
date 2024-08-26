#pragma once

#include <entt.hpp>
#include "Hazel/Core/Timestep.h"

namespace Hazel {
	class Scene {
		friend class Entity;
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = "Entity");

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
	};
}