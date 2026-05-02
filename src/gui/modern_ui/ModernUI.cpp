#include "views/view.hpp"
#include "fonts/fonts.hpp"
#include "logger/logger.hpp"
// ModernUI.cpp - Fixed single-window renderer for Lumina V
#include <imgui.h>
#include <cmath>
#include <chrono>

namespace modern_ui
{
        static constexpr float WIN_ROUNDING = 8.0f;

        static void DrawGradientBar(ImDrawList* dl, ImVec2 p, ImVec2 sz)
        {
                static auto t0 = std::chrono::steady_clock::now();
                float t        = std::chrono::duration<float>(std::chrono::steady_clock::now() - t0).count();
                float shift    = std::fmod(t * 0.4f, 6.28f);

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
                // Fixed size, centered
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

                // PopStyleColor is called immediately after Begin regardless of outcome
                bool window_open = ImGui::Begin("##LuminaMain", nullptr, wflags);
                ImGui::PopStyleColor();

                if (!window_open)
                {
                        ImGui::End();
                        ImGui::PopStyleVar(3);
                        return;
                }

                ImDrawList* dl = ImGui::GetWindowDrawList();
                ImVec2 wPos    = ImGui::GetWindowPos();
                ImVec2 wSize   = ImGui::GetWindowSize();

                // Debug: log active element count once per 300 frames
                static int s_frame_counter = 0;
                if (++s_frame_counter >= 300)
                {
                        s_frame_counter = 0;
                        LOG(VERBOSE) << "[UI] ModernUI rendering — window size: "
                                     << wSize.x << "x" << wSize.y
                                     << " | active elements: " << ImGui::GetCurrentWindow()->DC.ItemWidth;
                }

                // Animated gradient bar (4 px, full width)
                DrawGradientBar(dl, wPos, ImVec2(wSize.x, 4.0f));

                // Single tab bar with human-readable labels
                if (ImGui::BeginTabBar("##LuminaMainTabs"))
                {
                        if (ImGui::BeginTabItem(ICON_FA_USER " Self"))
                        {
                                big::view::self();
                                ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem(ICON_FA_USERS " Players"))
                        {
                                big::view::players();
                                ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem(ICON_FA_CAR " Vehicle"))
                        {
                                big::view::vehicle();
                                ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem(ICON_FA_GLOBE " World"))
                        {
                                big::view::world();
                                ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem(ICON_FA_COG " Settings"))
                        {
                                big::view::settings();
                                ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem(ICON_FA_SHIELD_ALT " Protections"))
                        {
                                big::view::protection_settings();
                                ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem(ICON_FA_BOLT " Fun Vehicle"))
                        {
                                big::view::fun_vehicle();
                                ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem(ICON_FA_GUN " Weapons"))
                        {
                                big::view::weapons();
                                ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem(ICON_FA_NETWORK_WIRED " Network"))
                        {
                                big::view::network();
                                ImGui::EndTabItem();
                        }
                        ImGui::EndTabBar();
                }

                ImGui::End();
                ImGui::PopStyleVar(3);
        }
}
