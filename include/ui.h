// Copyright 2025 Justin Nacu
#ifndef IMNOTATOR_UI_H
#define IMNOTATOR_UI_H

#include "ui_state.h"

// --- Rendering functions ---
void RenderFileDialog(FileDialogState& state);
void RenderSettings(SettingsState& state);
void RenderDebug(DebugState& state);

// Main entry for drawing the UI
void RenderUI(UIState& uiState);

#endif
