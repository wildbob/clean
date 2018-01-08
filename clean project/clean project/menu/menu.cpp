#pragma once
#include "..\core.hpp"
#include "menu.hpp"
#include "..\imgui/imgui_internal.h"
#include "..\imgui\dx9\imgui_dx9.h"
#include "..\hooks\menu hooks.hpp"

namespace sdk
{
	namespace menu
	{
		bool c_menu::initialized = false;
		bool c_menu::m_pressedkeys[256] = {};
		void c_menu::initialize_gui(IDirect3DDevice9* pDevice)
		{
			ImGui_ImplDX9_Init(sdk::hooks::m_window, pDevice);

			ImVec4 bg = ImVec4(1.f, 1.f, 1.f, 0.008f);
			ImVec4 hovered = ImVec4(1.f, 1.f, 1.f, 0.04f);
			ImVec4 active = ImVec4(1.f, 1.f, 1.f, 0.07f);
			ImVec4 accent = ImVec4(26.f / 255.f, 204.f / 255.f, 70.f / 255.f, 1.f);

			ImGuiIO& io = ImGui::GetIO();

			io.Fonts->Clear();
			io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 16.0f);
			io.Fonts->Build();


			ImGuiStyle& style = ImGui::GetStyle();
			static int hue = 140;

			ImVec4 col_text = ImColor::HSV(hue / 255.f, 20.f / 255.f, 235.f / 255.f);
			ImVec4 col_main = ImColor(9, 82, 128);
			ImVec4 col_back = ImColor(31, 44, 54);
			ImVec4 col_area = ImColor(4, 32, 41);

			style.Colors[ImGuiCol_Text] = ImVec4(0.98f, 0.98f, 0.98f, 1.00f);
			style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
			style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
			style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 0.95f);
			style.Colors[ImGuiCol_Border] = ImVec4(0.27f, 0.27f, .27f, 1.00f);
			style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style.Colors[ImGuiCol_FrameBg] = ImVec4(0.09f, .09f, .09f, 1.f);
			style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.13f, 0.13f, 0.13f, 1.f);
			style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.11f, 0.11f, 0.11f, 1.f);
			style.Colors[ImGuiCol_TitleBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
			style.Colors[ImGuiCol_TitleBgCollapsed] = accent;
			style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
			style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
			style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
			style.Colors[ImGuiCol_ScrollbarGrab] = accent; //main half
			style.Colors[ImGuiCol_Separator] = accent;
			style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.50f, 0.50f, 0.50f, 0.70f); //main half
			style.Colors[ImGuiCol_ScrollbarGrabActive] = accent;
			style.Colors[ImGuiCol_ComboBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
			style.Colors[ImGuiCol_CheckMark] = accent;
			style.Colors[ImGuiCol_SliderGrab] = accent; //main half
			style.Colors[ImGuiCol_SliderGrabActive] = accent;
			style.Colors[ImGuiCol_Button] = ImVec4(0.12f, 0.12f, 0.12f, 1.f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.12f, 0.12f, 0.12f, 1.f);
			style.Colors[ImGuiCol_ButtonActive] = accent;
			style.Colors[ImGuiCol_Header] = accent;
			style.Colors[ImGuiCol_HeaderHovered] = ImVec4(.50f, 0.50f, 0.50f, .3f); // combobox hover
			style.Colors[ImGuiCol_HeaderActive] = accent;
			style.Colors[ImGuiCol_ResizeGrip] = ImVec4(col_main.x, col_main.y, col_main.z, 0.20f);
			style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
			style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
			style.Colors[ImGuiCol_CloseButton] = ImVec4(col_text.x, col_text.y, col_text.z, 0.f);
			style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(col_text.x, col_text.y, col_text.z, 0);
			style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(col_text.x, col_text.y, col_text.z, 0);
			style.Colors[ImGuiCol_PlotLines] = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
			style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
			style.Colors[ImGuiCol_PlotHistogram] = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
			style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
			style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(col_main.x, col_main.y, col_main.z, 0.43f);
			style.Colors[ImGuiCol_PopupBg] = ImVec4(col_main.x, col_main.y, col_main.z, 0.92f);
			style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);


			style.WindowRounding = 0.f;
			style.WindowPadding = ImVec2(8, 8);
			style.FramePadding = ImVec2(5, 2);
			style.ItemInnerSpacing = ImVec2(4, 4);
			style.DisplayWindowPadding = ImVec2(805, 472);
			style.DisplaySafeAreaPadding = ImVec2(4, 4);
			style.FrameRounding = 0.f;
			style.ScrollbarSize = 2.f;
			style.ScrollbarRounding = 0.f;
			style.GrabRounding = 0.f;
			style.GrabMinSize = 8.f;
			style.AntiAliasedShapes = true;
			style.ChildWindowRounding = 0.f;

			c_menu::initialized = true;
		}
		void c_menu::draw()
		{
			if (!c_menu::initialized)
				return;

			ImGui_ImplDX9_NewFrame();
			ImGui::GetIO().MouseDrawCursor = csgo.m_settings()->m_menuopen;

			if (csgo.m_settings()->m_menuopen)
			{
				int pX, pY;
				csgo.m_input_system()->get_cursor_position(&pX, &pY);
				ImGuiIO& io = ImGui::GetIO();
				io.MousePos.x = (float)(pX);
				io.MousePos.y = (float)(pY);
				//ImGui::PushItemWidth(162.5);

				static char szCurrtooltip[128] = "";

				ImGui::Begin("fate", &csgo.m_settings()->m_menuopen, ImVec2(803, 458), 1.0f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
				{

				}
				ImGui::End();
			}
			ImGui::Render();
		}
	}
}