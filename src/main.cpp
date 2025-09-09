// Copyright 2025 Justin Nacu
#include "app.h"
#include "ui.h"

int main()
{
    App app(1280, 720, "ImGui Example");

    UIState uiState;

    app.Run(uiState);

    return 0;
}
