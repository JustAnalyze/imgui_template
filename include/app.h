// Copyright 2025 Justin Nacu
#ifndef IMNOTATOR_APP_H
#define IMNOTATOR_APP_H


#include <GLFW/glfw3.h>
#include "ui_state.h"

// The "App" handles window + ImGui lifecycle
class App
{
 public:
    App(int width, int height, const char* title);
    ~App();

    void Run(UIState uiState);  // main loop

 private:
    GLFWwindow* window;

    void InitImGui();
    void ShutdownImGui();
};

#endif  // APP_H
