// Copyright 2025 Justin Nacu
// ui.cpp
#include <imgui.h>
#include <iostream>
#include <vector>

#include "ui.h"
#include "logic.h"
#include "image_loader.h"

void RenderFileDialog(FileDialogState& state)
{
    if (!state.isOpen)
        return;

    ImGui::Begin("File Dialog", &state.isOpen);
    ImGui::Text("Select a file...");
    if (ImGui::Button("Choose Example.txt"))
    {
        state.selectedPath = "Example.txt";
        state.isOpen = false;  // close after selection
    }
    ImGui::End();
}

void RenderSettings(SettingsState& state)
{
    if (!state.showWindow)
        return;

    ImGui::Begin("Settings", &state.showWindow);
    ImGui::SliderFloat("Volume", &state.volume, 0.0f, 1.0f);
    ImGui::Checkbox("Dark Mode", &state.darkMode);
    ImGui::End();
}

void RenderDebug(DebugState& state)
{
    if (!state.showProfiler && !state.showLogs)
        return;

    if (state.showProfiler)
    {
        ImGui::Begin("Profiler", &state.showProfiler);
        ImGui::Text("Frame time: %.3f ms", 16.67f);
        ImGui::End();
    }

    if (state.showLogs)
    {
        ImGui::Begin("Logs", &state.showLogs);
        ImGui::TextWrapped("This is a debug log entry...");
        ImGui::End();
    }
}

void RenderImageWindow(ImageWindow& state)
{
    if (!LoadTextureFromFile(state.imagePath.c_str(), &state.imageTexture,
                             &state.imageWidth, &state.imageHeight))
    {
        std::cerr << "Failed to load texture!" << std::endl;
    }

    ImGui::Begin("Image Window");
    if (state.imageTexture)
    {
        ImGui::Image(
            reinterpret_cast<void*>(static_cast<intptr_t>(state.imageTexture)),
            ImVec2(state.imageWidth, state.imageHeight));
    }
    ImGui::End();
}

// Child of Dockspace
void RenderMainMenu(UIState& uiState)
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open Directory"))
                uiState.fileDialog.isOpen = true;
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Settings", nullptr, &uiState.settings.showWindow);
            ImGui::MenuItem("Profiler", nullptr, &uiState.debug.showProfiler);
            ImGui::MenuItem("Logs", nullptr, &uiState.debug.showLogs);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void RenderDockspace(UIState& uiState)
{
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // Fullscreen window settings
    ImGuiWindowFlags window_flags
        = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
                    | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus
                    | ImGuiWindowFlags_NoNavFocus;

    // Get main viewport (covers the whole GLFW window)
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    // Padding = 0 so content fills entire window
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("MainDockspace", nullptr, window_flags);

    ImGui::PopStyleVar();

    // Make it full screen dockspace
    ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    // Top bar main menu
    RenderMainMenu(uiState);

    ImGui::End();
}

void RenderImageBrowser()
{
    ImGui::Begin("Image Browser");
    if (ImGui::Selectable("example selectable"))
    {
        std::cout << "I AM SELECTED!!!\n";
    }
    ImGui::End();
}

void RenderUI(UIState& uiState)
{
    RenderDockspace(uiState);

    // Render windows based on state
    RenderImageBrowser();
    RenderImageWindow(uiState.imageLoader);
    RenderFileDialog(uiState.fileDialog);
    RenderSettings(uiState.settings);
    RenderDebug(uiState.debug);
}
