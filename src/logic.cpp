// Copyright 2025 Justin Nacu
// logic.cpp
#include <nfd.h>

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

#include "logic.h"

std::vector<std::string> getDirFilePaths(std::filesystem::path dirPath)
{
    std::vector<std::string> imgPaths{};
    try
    {
        // Create a directory iterator for the specified path
        for (const auto& entry : std::filesystem::directory_iterator(dirPath))
        {
            if (entry.is_regular_file())
            {
                imgPaths.push_back(entry.path().string());
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return imgPaths;
}

// Open Directory Dialog using nativefiledialog package
std::string OpenDirectoryDialog()
{
    nfdchar_t* outPath = nullptr;
    nfdresult_t result = NFD_PickFolder(NULL, &outPath);

    if (result == NFD_OKAY)
    {
        std::string selectedPath(outPath);
        free(outPath);  // cleanup required
        return selectedPath;
    }
    else if (result == NFD_CANCEL)
    {
        return "";  // user cancelled
    }
    else
    {
        std::cerr << "NFD Error: " << NFD_GetError() << std::endl;
    }
    return "";
}

void DoSomething() { std::cout << "Action triggered!\n"; }

void SaveFile(const char* path)
{
    std::cout << "Saving file to: " << path << "\n";
    // real save code here
}

// int main() { std::vector<std::string> filePaths = getDirFilePaths("demo"); }
