#include <hzpch.h>
#include "Scene.h"
#include "Components.h"
#include "Entity.h"
#include "Hazel/Render/Renderer2D.h"
#include <glm/glm.hpp>
#include <box2d/id.h>
#include <box2d/types.h>
#include <box2d/box2d.h>

namespace Hazel {
	static b2BodyType RB2DTypeToBox2D(Rigidbody2DComponent::BodyType bodyType)
	{
		switch (bodyType)
		{
		case Hazel::Rigidbody2DComponent::BodyType::Static:
			return b2_staticBody;
		case Hazel::Rigidbody2DComponent::BodyType::Dynamic:
			return b2_dynamicBody;
		case Hazel::Rigidbody2DComponent::BodyType::Kinematic:
			return b2_kinematicBody;
		default:
			HZ_CORE_ASSERT(false, "");
			return b2_staticBody;
		}
	}

	Scene::Scene()
	{
		
	}
	
	Scene::~Scene()
	{
	}
	
	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>(name);
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnRuntimeStart()
	{
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = { 0.0f, -9.8f };
		worldDef.restitutionThreshold = 0.5f;
		//check if m_WorldId  can be use when go out of this scope
		m_WorldId = b2CreateWorld(&worldDef);
		
		auto view = m_Registry.view<Rigidbody2DComponent>();
		for (auto e : view)
		{
			Entity entity = { e, this };
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();

			b2BodyDef bodyDef = b2DefaultBodyDef();
			bodyDef.type = RB2DTypeToBox2D(rb2d.Type);
			bodyDef.position = { transform.Translation.x, transform.Translation.y };
			bodyDef.rotation = b2MakeRot(transform.GetEulerAngles().z);
			bodyDef.fixedRotation = rb2d.FixedRotation;

			b2BodyId groundId = b2CreateBody(m_WorldId, &bodyDef);
			rb2d.RuntimeBody = groundId;

			if (entity.HasComponent<BoxCollider2DComponent>())
			{
				auto& bc2d = entity.GetComponent<BoxCollider2DComponent>();
				b2Polygon box = b2MakeBox(bc2d.Size.x * transform.Scale.x, bc2d.Size.y * transform.Scale.y);

				b2ShapeDef shapeDef = b2DefaultShapeDef();
				shapeDef.density = bc2d.Density;
				shapeDef.friction = bc2d.Friction;
				shapeDef.restitution = bc2d.Restitution;
				b2CreatePolygonShape(groundId, &shapeDef, &box);
			}
		}
	}

	void Scene::OnRuntimeStop()
	{
		b2DestroyWorld(m_WorldId);
	}
	
	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera);
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			//Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
			Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
		}
		Renderer2D::EndScene();
	}

	void Scene::OnUpdateRuntime(Timestep ts)
	{
		//Scripts
		m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				if (!nsc.Instance) {
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Entity = Entity{ entity, this };
					nsc.Instance->OnCreate();
				}
				nsc.Instance->OnUpdate(ts);
			});

		//Physics
		{
			float timeStep = 1.0f / 60.0f;
			//int subStepCount = 4;
			int subStepCount = 4 * timeStep / ts.GetSeconds();
			//b2World_Step(m_WorldId, timeStep, subStepCount);
			b2World_Step(m_WorldId, ts, subStepCount);

			auto view = m_Registry.view<Rigidbody2DComponent>();
			for (auto e : view)
			{
				Entity entity = { e,this };
				auto& transform = entity.GetComponent<TransformComponent>();
				auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();

				auto& position = b2Body_GetPosition(rb2d.RuntimeBody);
				transform.Translation.x = position.x;
				transform.Translation.y = position.y;
				transform.SetZRotation(b2Rot_GetAngle(b2Body_GetRotation(rb2d.RuntimeBody)));
			}
		}

		//Render
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view) {
			auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
			if (camera.Primary) {
				mainCamera = &camera.Camera;
				cameraTransform = transform.GetTransform();
				break;
			}
		}

		if (mainCamera) {
			Renderer2D::BeginScene(mainCamera->GetProjection(), cameraTransform);
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
			}
			Renderer2D::EndScene();
		}

	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view) {
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio) {
				cameraComponent.Camera.SetViewportSize(width, height);
			}
		}
	}

	Entity Scene::GetPrimartCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.Primary)
				return Entity{ entity, this };
		}
		return {};
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<Rigidbody2DComponent>(Entity entity, Rigidbody2DComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<BoxCollider2DComponent>(Entity entity, BoxCollider2DComponent& component)
	{
	}
}