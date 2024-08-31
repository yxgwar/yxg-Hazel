#pragma once

#include "Hazel/Scene/Scene.h"
#include "Hazel/Core/Core.h"
#include "Hazel/Scene/Entity.h"

namespace Hazel {
	class SceneHierarchyPanel {
		friend class Scene;
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);
		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);

		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}