#pragma once

#include "Hazel/Render/Shader.h"
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Hazel {
	class OpenGlShader: public Shader {
	public:
		OpenGlShader(const std::string& filepath);
		OpenGlShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGlShader();

		void Bind() const override;
		void UnBind() const override;

		inline const std::string& GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string& name, int values);

		void UploadUniformFloat(const std::string& name, float values);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSource);

		uint32_t m_RendererID;
		std::string m_Name;
	};
}