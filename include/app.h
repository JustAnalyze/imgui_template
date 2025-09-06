// Copyright 2025 Justin Nacu
#ifndef APP_H
#define APP_H

#include <GLFW/glfw3.h>

// The "App" handles window + ImGui lifecycle
class App
{
 public:
    App(int width, int height, const char* title);
    ~App();

    void Run();  // main loop

 private:
    GLFWwindow* window;

    void InitImGui();
    void ShutdownImGui();
};

#endif
