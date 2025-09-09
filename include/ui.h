// Copyright 2025 Justin Nacu
#ifndef UI_H
#define UI_H

#include <glad/glad.h>
#include <string>

// Example usage inside your render loop
struct ImageWindow
{
    GLuint imageTexture = 0;
    std::string imagePath = "";
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
    bool showWindow = true;
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
    ImageWindow imageLoader;
};

// --- Rendering functions ---
void RenderFileDialog(FileDialogState& state);
void RenderSettings(SettingsState& state);
void RenderDebug(DebugState& state);

// Main entry for drawing the UI
void RenderUI(UIState& uiState);

#endif
