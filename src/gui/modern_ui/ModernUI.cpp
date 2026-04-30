// ModernUI.cpp - Adapted from Lumina (Enhanced) Modern Theme for use in Lumina V (YimMenu Legacy)
#include <imgui.h>
#include <cmath>
#include <chrono>

namespace modern_ui
{
	static constexpr float SIDEBAR_W   = 60.0f;
	static constexpr float CAT_BAR_H   = 42.0f;
	static constexpr float WIN_ROUNDING = 8.0f;

	static void DrawGradientBar(ImDrawList* dl, ImVec2 p, ImVec2 sz)
	{
		static auto t0 = std::chrono::steady_clock::now();
		float t = std::chrono::duration<float>(std::chrono::steady_clock::now() - t0).count();
		float shift = std::fmod(t * 0.4f, 6.28f);

		ImU32 colL = ImGui::GetColorU32(ImVec4(
			0.10f + 0.15f * std::sin(shift),
			0.05f,
			0.30f + 0.20f * std::cos(shift), 1.0f));
		ImU32 colR = ImGui::GetColorU32(ImVec4(
			0.40f + 0.10f * std::cos(shift),
			0.10f,
			0.60f + 0.10f * std::sin(shift), 1.0f));

		dl->AddRectFilledMultiColor(p, ImVec2(p.x + sz.x, p.y + sz.y), colL, colR, colR, colL);
	}

	void RenderModernTheme(float scrW, float scrH)
	{
		// Window sizing — Cherax style: fixed size, centered
		float winW = std::min(scrW * 0.50f, 780.0f);
		float winH = std::min(scrH * 0.55f, 520.0f);

		ImGui::SetNextWindowSize(ImVec2(winW, winH), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(
			ImVec2((scrW - winW) * 0.5f, (scrH - winH) * 0.5f),
			ImGuiCond_FirstUseEver);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, WIN_ROUNDING);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.07f, 0.06f, 0.10f, 0.97f));

		ImGuiWindowFlags wflags =
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse;

		if (!ImGui::Begin("##LuminaMain", nullptr, wflags))
		{
			ImGui::End();
			ImGui::PopStyleColor();
			ImGui::PopStyleVar(3);
			return;
		}

		ImGui::PopStyleColor();
		ImGui::PopStyleVar(3);

		ImDrawList* dl = ImGui::GetWindowDrawList();
		ImVec2 wPos  = ImGui::GetWindowPos();
		ImVec2 wSize = ImGui::GetWindowSize();

		// Animated gradient bar (4px, full width)
		DrawGradientBar(dl, wPos, ImVec2(wSize.x, 4.0f));

		// ... (continue with header, sidebar, and content area as in original Modern.cpp)
	}
}
