// Copyright 2025 Justin Nacu
// ui.cpp
#include <glad/glad.h>

#include <imgui.h>
#include <iostream>
#include <string>
#include <string_view>
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

    ImGui::Begin("Image Window");
    if (state.imageTexture)
    {
        ImGui::Image(
            reinterpret_cast<void*>(static_cast<intptr_t>(state.imageTexture)),
            ImVec2(state.imageWidth, state.imageHeight));
    }
    ImGui::End();
}

// MAIN MENU CODE STARTS HERE (MAIN MENU IS USED IN INSIDE RenderDockspace)
static void RenderFileMenu(UIState& uiState)
{
    if (ImGui::MenuItem("Open Directory"))
    {
        if (auto dir = OpenDirectoryDialog(); !dir.empty())
            HandleOpenDirectory(uiState, dir);
    }
}

static void RenderViewMenu(UIState& uiState)
{
    ImGui::MenuItem("Settings", nullptr, &uiState.settings.showWindow);
    ImGui::MenuItem("Profiler", nullptr, &uiState.debug.showProfiler);
    ImGui::MenuItem("Logs", nullptr, &uiState.debug.showLogs);
}

void RenderMainMenu(UIState& uiState)
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            RenderFileMenu(uiState);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            RenderViewMenu(uiState);
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

void RenderSegmentWindow(SegmentWindow& SegmentWindowState,
                         ImageViewer& imageWindowState)
{
    ImGui::Begin("Segment Window", &SegmentWindowState.showWindow);

    for (size_t i = 0; i < SegmentWindowState.allSegments.size(); ++i)
    {
        const std::string segmentName = "segment" + std::to_string(i);

        // If the current idx is same as the previous
        // selected idx highlight the selectable
        bool selectedIdxIsSameAsCurrentIdx{
            SegmentWindowState.selectedSegmentIdx == static_cast<int>(i)
        };
        if (ImGui::Selectable(segmentName.c_str(),
                              selectedIdxIsSameAsCurrentIdx))
        {
            SegmentWindowState.selectedSegmentIdx = i;

            SegmentWindowState.currentSegmentFrames
                = SegmentWindowState.allSegments[i];

            std::cout << "Selected index: " << i << " -> " << segmentName
                      << '\n'
                      << "frames: \n";

            for (std::string_view frame :
                 SegmentWindowState.currentSegmentFrames)
            {
                std::cout << frame << '\n';
            }
            // TODO: Rename imageWindowState to displayWindowState and find a
            // way to display frames in loop
        }
    }
    ImGui::End();
}

void RenderUI(UIState& uiState)
{
    RenderDockspace(uiState);

    // Update logic/state before drawing
    UpdateImageViewerTexture(uiState.imageViewer);

    // Render windows based on state
    RenderSegmentWindow(uiState.segmentWindow, uiState.imageViewer);
    RenderImageViewer(uiState.imageViewer);
    RenderSettings(uiState.settings);
    RenderDebug(uiState.debug);
}
