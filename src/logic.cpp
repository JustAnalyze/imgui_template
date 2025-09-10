// Copyright 2025 Justin Nacu
// logic.cpp
#include <nfd.h>

#include <iostream>
#include <algorithm>
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

int extractFrameNumber(const std::string& filename)
{
    auto pos = filename.find_last_of('_');
    if (pos == std::string::npos)
        return -1;

    auto dot = filename.find_last_of('.');
    std::string numStr = filename.substr(pos + 1, dot - pos - 1);

    return std::stoi(numStr);
}

void sortFilePaths(std::vector<std::string>& paths)
{
    std::sort(paths.begin(), paths.end(),
              [](const std::string& a, const std::string& b)
              { return extractFrameNumber(a) < extractFrameNumber(b); });
}

// Groups frame paths in to segments depending on segmentSize and stores it in
// the SegmentWindowState.currentSegmentFrames
void getSegments(SegmentWindow& segmentWindow)  // allow flexible size
{
    sortFilePaths(segmentWindow.allFramesPaths);

    std::vector<std::string> segment;
    segment.reserve(segmentWindow.segmentSize);  // avoid reallocations

    for (size_t i = 0; i < segmentWindow.allFramesPaths.size(); ++i)
    {
        segment.push_back(segmentWindow.allFramesPaths[i]);

        bool segmentSizeMet{ (i + 1) % segmentWindow.segmentSize == 0 };
        if (segmentSizeMet)
        {
            segmentWindow.allSegments.push_back(segment);
            segment.clear();
        }
    }

    // push remaining frames if not empty
    if (!segment.empty())
    {
        segmentWindow.allSegments.push_back(segment);
    }
}

void DoSomething() { std::cout << "Action triggered!\n"; }

void SaveFile(const char* path)
{
    std::cout << "Saving file to: " << path << "\n";
    // real save code here
}

// int main() { std::vector<std::string> filePaths = getDirFilePaths("demo"); }
