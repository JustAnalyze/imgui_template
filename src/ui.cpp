// Copyright 2025 Justin Nacu
// ui.cpp
#include "imgui.h"

#include "ui.h"
#include "logic.h"

void RenderUI()
{
    ImGui::Begin("Controls");

    if (ImGui::Button("Do Something"))
    {
        DoSomething();  // call into logic.cpp
    }

    if (ImGui::Button("Save"))
    {
        SaveFile("output.txt");
    }

    ImGui::End();
}
