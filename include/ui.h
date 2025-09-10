// Copyright 2025 Justin Nacu
#ifndef UI_H
#define UI_H

#include <glad/glad.h>
#include <string>
#include <vector>

// Example usage inside your render loop
struct ImageBrowser
{
    bool showWindow = true;
    std::vector<std::string> imagePaths{};
    int selectedIndex = -1;
};

struct ImageViewer
{
    std::string imagePath;        // requested image
    std::string loadedImagePath;  // last successfully loaded image
    GLuint imageTexture = 0;      // OpenGL texture handle
    int imageWidth = 0;
    int imageHeight = 0;
};

// --- State structs ---
struct FileDialogState
{
    bool isOpen = false;
    std::string selectedPath;
};

struct SettingsState
{
    bool showWindow = false;
    float volume = 0.5f;
    bool darkMode = false;
};

struct DebugState
{
    bool showProfiler = false;
    bool showLogs = false;
};

struct UIState
{
    FileDialogState fileDialog;
    SettingsState settings;
    DebugState debug;
    ImageViewer imageViewer;
    ImageBrowser imageBrowser;
};

// --- Rendering functions ---
void RenderFileDialog(FileDialogState& state);
void RenderSettings(SettingsState& state);
void RenderDebug(DebugState& state);

// Main entry for drawing the UI
void RenderUI(UIState& uiState);

#endif
