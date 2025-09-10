// Copyright 2025 Justin Nacu
// ui.cpp
#include <imgui.h>
#include <iostream>
#include <string>
#include <vector>

#include "ui.h"
#include "logic.h"
#include "image_loader.h"

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

void RenderImageViewer(ImageViewer& state)
{
    if (state.imagePath.empty())
        return;  // nothing to show

    // Load texture only if a new image was selected
    if (state.imagePath != state.loadedImagePath)
    {
        // free old texture if it exists
        if (state.imageTexture)
        {
            glDeleteTextures(1, &state.imageTexture);
            state.imageTexture = 0;
        }
        // try to load new texture
        if (LoadTextureFromFile(state.imagePath.c_str(), &state.imageTexture,
                                &state.imageWidth, &state.imageHeight))
        {
            state.loadedImagePath = state.imagePath;  // mark as loaded
        }
        else
        {
            std::cerr << "Failed to load texture: " << state.imagePath
                      << std::endl;
            state.loadedImagePath.clear();
        }
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
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Open Directory"))
        {
            std::string dir = OpenDirectoryDialog();
            if (!dir.empty())
            {
                uiState.fileDialog.selectedPath = dir;
                uiState.imageBrowser.imagePaths = getDirFilePaths(dir);
            }
        }
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

void RenderImageBrowser(ImageBrowser& ImageBrowserState,
                        ImageViewer& imageWindowState)
{
    ImGui::Begin("Image Browser", &ImageBrowserState.showWindow);
    for (const std::string& filePath : ImageBrowserState.imagePaths)
    {
        std::filesystem::path filePath_fsp(filePath);
        if (ImGui::Selectable(filePath_fsp.filename().c_str()))
        {
            std::cout << "Selected: " << filePath << '\n';
            imageWindowState.imagePath = filePath;
        }
    }
    ImGui::End();
}

void RenderUI(UIState& uiState)
{
    RenderDockspace(uiState);

    // Render windows based on state
    RenderImageBrowser(uiState.imageBrowser, uiState.imageViewer);
    RenderImageViewer(uiState.imageViewer);
    RenderSettings(uiState.settings);
    RenderDebug(uiState.debug);
}
