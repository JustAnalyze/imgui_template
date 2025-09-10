// Copyright 2025 Justin Nacu
// logic.h
#ifndef IMNOTATOR_LOGIC_H
#define IMNOTATOR_LOGIC_H

#include <string>
#include <vector>
#include <filesystem>

#include "ui_state.h"

void DoSomething();

void SaveFile(const char* path);

std::vector<std::string> getDirFilePaths(std::filesystem::path dirPath);

std::string OpenDirectoryDialog();

void HandleOpenDirectory(UIState& uiState, const std::string& dir);

void getSegments(SegmentWindow& segmentWindow);
//
#endif
