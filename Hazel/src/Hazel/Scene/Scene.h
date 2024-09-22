#pragma once

#include <entt.hpp>
#include "Hazel/Core/Timestep.h"
#include "Hazel/Render/EditorCamera.h"
#include "Components.h"
#include <box2d/id.h>

namespace Hazel {
	class Entity;
	class Scene {
		friend class Entity;
		friend class SceneHierarchyPanel;
		friend class SceneSerializer;
	public:
		Scene();
		~Scene();

		static Ref<Scene> Copy(Ref<Scene> other);

		Entity CreateEntity(const std::string& name = "Entity");
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = "Entity");
		void DestroyEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();

		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnUpdateRuntime(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);

		void DuplicateEntity(Entity entity);

		Entity GetPrimartCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		b2WorldId m_WorldId;
	};
}