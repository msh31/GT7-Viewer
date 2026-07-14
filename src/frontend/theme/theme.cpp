/*
 *  Also stolen from SaveManager ->
 * https://git.marco007.dev/marco/SaveManager/src/branch/main/src/frontend/ui/themes/themes.cpp
 */

#include "theme.hpp"

void ThemeManager::apply_style( ) {
    style                        = ImGui::GetStyle( );
    style.WindowPadding          = { 10.f, 10.f };
    style.PopupRounding          = 4.f;
    style.FramePadding           = { 8.f, 4.f };
    style.ItemSpacing            = { 10.f, 4.f };
    style.ItemInnerSpacing       = { 6.f, 6.f };
    style.TouchExtraPadding      = { 0.f, 0.f };
    style.IndentSpacing          = 21.f;
    style.ScrollbarSize          = 15.f;
    style.GrabMinSize            = 8.f;
    style.WindowBorderSize       = 1.f;
    style.ChildBorderSize        = 2.f;
    style.PopupBorderSize        = 1.f;
    style.FrameBorderSize        = 0.f;
    style.TabBorderSize          = 0.f;
    style.WindowRounding         = 0.f;
    style.ChildRounding          = 4.f;
    style.FrameRounding          = 4.f;
    style.ScrollbarRounding      = 4.f;
    style.GrabRounding           = 0.f;
    style.TabRounding            = 4.f;
    style.WindowTitleAlign       = { 0.5f, 0.5f };
    style.ButtonTextAlign        = { 0.5f, 0.5f };
    style.DisplaySafeAreaPadding = { 3.f, 3.f };

    ImGui::GetStyle( ) = style;
}

void ThemeManager::apply_colors( ThemeType theme ) {
    ThemeType selectedTheme = theme;

    auto& colors = ImGui::GetStyle( ).Colors;

    const auto gt7_red     = ImVec4( 0.90f, 0.00f, 0.04f, 1.00f );
    const auto gt7_red_dim = ImVec4( 0.55f, 0.05f, 0.08f, 1.00f );
    const auto gt7_red_hov = ImVec4( 1.00f, 0.05f, 0.08f, 1.00f );
    const auto gt7_red_sel = ImVec4( 0.90f, 0.00f, 0.04f, 0.35f );

    switch ( selectedTheme ) {
    case ThemeType::Dark:
        colors[ImGuiCol_Text] = ImVec4( 0.95f, 0.95f, 0.95f, 1.00f );
        colors[ImGuiCol_TextDisabled] = ImVec4( 0.40f, 0.40f, 0.40f, 1.00f );
        colors[ImGuiCol_WindowBg] = ImVec4( 0.06f, 0.06f, 0.06f, 1.00f );
        colors[ImGuiCol_ChildBg] = ImVec4( 0.09f, 0.09f, 0.09f, 1.00f );
        colors[ImGuiCol_PopupBg] = ImVec4( 0.08f, 0.08f, 0.08f, 0.94f );
        colors[ImGuiCol_Border] = ImVec4( 0.20f, 0.20f, 0.20f, 0.50f );
        colors[ImGuiCol_BorderShadow] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
        colors[ImGuiCol_FrameBg] = ImVec4( 0.22f, 0.22f, 0.22f, 0.60f );
        colors[ImGuiCol_FrameBgHovered] = ImVec4( 0.28f, 0.28f, 0.28f, 0.78f );
        colors[ImGuiCol_FrameBgActive] = ImVec4( 0.32f, 0.32f, 0.32f, 0.70f );
        colors[ImGuiCol_TitleBg] = ImVec4( 0.04f, 0.04f, 0.04f, 1.00f );
        colors[ImGuiCol_TitleBgActive] = ImVec4( 0.08f, 0.08f, 0.08f, 1.00f );
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4( 0.02f, 0.02f, 0.02f, 0.60f );
        colors[ImGuiCol_MenuBarBg] = ImVec4( 0.07f, 0.07f, 0.07f, 1.00f );
        colors[ImGuiCol_ScrollbarBg] = ImVec4( 0.02f, 0.02f, 0.02f, 0.53f );
        colors[ImGuiCol_ScrollbarGrab] = ImVec4( 0.25f, 0.25f, 0.25f, 1.00f );
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4( 0.35f, 0.35f, 0.35f, 1.00f );
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4( gt7_red );
        colors[ImGuiCol_CheckMark] = ImVec4( gt7_red );
        colors[ImGuiCol_SliderGrab] = ImVec4( gt7_red_dim );
        colors[ImGuiCol_SliderGrabActive] = ImVec4( gt7_red );
        colors[ImGuiCol_Button] = ImVec4( 0.15f, 0.15f, 0.15f, 0.74f );
        colors[ImGuiCol_ButtonHovered] = ImVec4( gt7_red_dim );
        colors[ImGuiCol_ButtonActive] = ImVec4( gt7_red );
        colors[ImGuiCol_Header] = ImVec4( 0.12f, 0.12f, 0.12f, 0.31f );
        colors[ImGuiCol_HeaderHovered] = ImVec4( gt7_red_dim );
        colors[ImGuiCol_HeaderActive] = ImVec4( gt7_red );
        colors[ImGuiCol_Separator] = ImVec4( 0.20f, 0.20f, 0.20f, 0.50f );
        colors[ImGuiCol_SeparatorHovered] = ImVec4( gt7_red_dim );
        colors[ImGuiCol_SeparatorActive] = ImVec4( gt7_red );
        colors[ImGuiCol_ResizeGrip] = ImVec4( 0.20f, 0.20f, 0.20f, 1.00f );
        colors[ImGuiCol_ResizeGripHovered] = ImVec4( gt7_red_dim );
        colors[ImGuiCol_ResizeGripActive] = ImVec4( gt7_red );
        colors[ImGuiCol_Tab] = ImVec4( 0.10f, 0.10f, 0.10f, 0.86f );
        colors[ImGuiCol_TabHovered] = ImVec4( gt7_red_dim );
        colors[ImGuiCol_TabActive] = ImVec4( gt7_red );
        colors[ImGuiCol_TabUnfocused] = ImVec4( 0.06f, 0.06f, 0.06f, 0.97f );
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4( 0.30f, 0.05f, 0.06f, 1.00f );
        colors[ImGuiCol_TabSelectedOverline] = ImVec4( gt7_red );
        colors[ImGuiCol_PlotLines] = ImVec4( 0.50f, 0.50f, 0.50f, 1.00f );
        colors[ImGuiCol_PlotLinesHovered] = ImVec4( gt7_red );
        colors[ImGuiCol_PlotHistogram] = ImVec4( gt7_red );
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4( gt7_red_hov );
        colors[ImGuiCol_TextSelectedBg] = ImVec4( gt7_red_sel );
        colors[ImGuiCol_DragDropTarget] = ImVec4( gt7_red );
        colors[ImGuiCol_NavHighlight] = ImVec4( gt7_red );
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4( gt7_red );
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4( 0.00f, 0.00f, 0.00f, 0.25f );
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4( 0.00f, 0.00f, 0.00f, 0.40f );
        break;
    case ThemeType::Light:
        colors[ImGuiCol_Text] = ImVec4( 0.08f, 0.08f, 0.08f, 1.00f );
        colors[ImGuiCol_TextDisabled] = ImVec4( 0.50f, 0.50f, 0.50f, 1.00f );
        colors[ImGuiCol_WindowBg] = ImVec4( 0.96f, 0.95f, 0.94f, 1.00f );
        colors[ImGuiCol_ChildBg] = ImVec4( 0.98f, 0.97f, 0.96f, 1.00f );
        colors[ImGuiCol_PopupBg] = ImVec4( 1.00f, 1.00f, 1.00f, 0.98f );
        colors[ImGuiCol_Border] = ImVec4( 0.30f, 0.30f, 0.30f, 0.35f );
        colors[ImGuiCol_BorderShadow] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
        colors[ImGuiCol_FrameBg] = ImVec4( 0.85f, 0.85f, 0.85f, 0.70f );
        colors[ImGuiCol_FrameBgHovered] = ImVec4( gt7_red_sel );
        colors[ImGuiCol_FrameBgActive] = ImVec4( gt7_red_sel );
        colors[ImGuiCol_TitleBg] = ImVec4( 0.85f, 0.84f, 0.83f, 1.00f );
        colors[ImGuiCol_TitleBgActive] = ImVec4( 0.90f, 0.00f, 0.04f, 0.08f );
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4( 0.85f, 0.84f, 0.83f, 0.51f );
        colors[ImGuiCol_MenuBarBg] = ImVec4( 0.88f, 0.87f, 0.86f, 1.00f );
        colors[ImGuiCol_ScrollbarBg] = ImVec4( 0.85f, 0.84f, 0.83f, 0.53f );
        colors[ImGuiCol_ScrollbarGrab] = ImVec4( 0.55f, 0.55f, 0.55f, 1.00f );
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4( 0.45f, 0.45f, 0.45f, 1.00f );
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4( gt7_red );
        colors[ImGuiCol_CheckMark] = ImVec4( gt7_red );
        colors[ImGuiCol_SliderGrab] = ImVec4( gt7_red_dim );
        colors[ImGuiCol_SliderGrabActive] = ImVec4( gt7_red );
        colors[ImGuiCol_Button] = ImVec4( 0.80f, 0.80f, 0.80f, 0.74f );
        colors[ImGuiCol_ButtonHovered] = ImVec4( gt7_red_dim );
        colors[ImGuiCol_ButtonActive] = ImVec4( gt7_red );
        colors[ImGuiCol_Header] = ImVec4( gt7_red_sel );
        colors[ImGuiCol_HeaderHovered] = ImVec4( gt7_red_dim );
        colors[ImGuiCol_HeaderActive] = ImVec4( gt7_red );
        colors[ImGuiCol_Separator] = ImVec4( 0.40f, 0.40f, 0.40f, 0.40f );
        colors[ImGuiCol_SeparatorHovered] = ImVec4( gt7_red_dim );
        colors[ImGuiCol_SeparatorActive] = ImVec4( gt7_red );
        colors[ImGuiCol_ResizeGrip] = ImVec4( 0.45f, 0.45f, 0.45f, 1.00f );
        colors[ImGuiCol_ResizeGripHovered] = ImVec4( gt7_red_dim );
        colors[ImGuiCol_ResizeGripActive] = ImVec4( gt7_red );
        colors[ImGuiCol_Tab] = ImVec4( 0.82f, 0.82f, 0.82f, 0.86f );
        colors[ImGuiCol_TabHovered] = ImVec4( gt7_red_dim );
        colors[ImGuiCol_TabActive] = ImVec4( gt7_red );
        colors[ImGuiCol_TabUnfocused] = ImVec4( 0.88f, 0.88f, 0.88f, 0.97f );
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4( 0.55f, 0.05f, 0.08f, 1.00f );
        colors[ImGuiCol_TabSelectedOverline] = ImVec4( gt7_red );
        colors[ImGuiCol_PlotLines] = ImVec4( 0.40f, 0.40f, 0.40f, 1.00f );
        colors[ImGuiCol_PlotLinesHovered] = ImVec4( gt7_red );
        colors[ImGuiCol_PlotHistogram] = ImVec4( gt7_red );
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4( gt7_red_hov );
        colors[ImGuiCol_TextSelectedBg] = ImVec4( gt7_red_sel );
        colors[ImGuiCol_DragDropTarget] = ImVec4( gt7_red );
        colors[ImGuiCol_NavHighlight] = ImVec4( gt7_red );
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4( gt7_red );
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4( 0.90f, 0.90f, 0.90f, 0.20f );
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4( 0.90f, 0.90f, 0.90f, 0.35f );
        break;
    case ThemeType::Custom:
        // TODO: handle this, maybe open upp some customizer menu. future....
        break;
    }
}
