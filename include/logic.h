// Copyright 2025 Justin Nacu
// logic.h
#ifndef LOGIC_H
#define LOGIC_H

#include <string>
#include <vector>
#include <filesystem>

void DoSomething();

void SaveFile(const char* path);

std::vector<std::string> getDirFilePaths(std::filesystem::path dirPath);

std::string OpenDirectoryDialog();

void getSegments(std::vector<std::string>& allFramesPaths,
                 std::vector<std::vector<std::string>>& allSegments,
                 int& segmentSize);
#endif
