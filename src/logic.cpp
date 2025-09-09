// Copyright 2025 Justin Nacu
// logic.cpp
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
            // Access information about the current directory entry
            std::cout << entry.path().filename()
                      << std::endl;  // Print filename
            // You can also check if it's a directory, file, etc.
            // if (entry.is_directory()) { ... }
            if (entry.is_regular_file())
            {
                imgPaths.pop_back();
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return imgPaths;
}

void DoSomething() { std::cout << "Action triggered!\n"; }

void SaveFile(const char* path)
{
    std::cout << "Saving file to: " << path << "\n";
    // real save code here
}
