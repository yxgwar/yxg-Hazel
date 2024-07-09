#pragma once

#include "Event.h"

#include <sstream>

namespace Hazel {
	class HAZEL_API MouseMovedEvent :public Event {
	public:
		MouseMovedEvent(float x, float y)
			:m_MouseX(x), m_MouseY(y){}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX, m_MouseY;
	};

	class HAZEL_API MouseScrolledEvent :public Event {
	public:
		MouseScrolledEvent(float xOffest, float yOffest)
			:m_XOffest(xOffest), m_YOffest(yOffest) {}

		inline float GetXOffest() const { return m_XOffest; }
		inline float GetYOffest() const { return m_YOffest; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_XOffest << ", " << m_YOffest;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffest, m_YOffest;
	};

	class HAZEL_API MouseButtonEvent :public Event {
	public:
		inline int GetMouseButton() const { return m_Button; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button) :m_Button(button){}
		int m_Button;
	};

	class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}