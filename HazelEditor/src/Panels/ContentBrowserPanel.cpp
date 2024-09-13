#include <hzpch.h>
#include "ContentBrowserPanel.h"
#include <imgui/imgui.h>

namespace Hazel {
	static const std::filesystem::path s_AssetPath = "assets";

	ContentBrowserPanel::ContentBrowserPanel()
		:m_CurrentDirectory(s_AssetPath)
	{
	}

	void ContentBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("Content Browser");

		if (m_CurrentDirectory != std::filesystem::path(s_AssetPath))
		{
			if (ImGui::Button("<-"))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}

		for (auto& p : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			std::string path = p.path().string();
			auto relativePath = std::filesystem::relative(p.path(), s_AssetPath);
			std::string relativePathString = relativePath.filename().string();
			if (p.is_directory())
			{
				if (ImGui::Button(relativePathString.c_str()))
				{
					m_CurrentDirectory /= p.path().filename();
				}
			}
			else
			{
				if (ImGui::Button(relativePathString.c_str()))
				{
					
				}
			}
		}

		ImGui::End();
	}
}