#include "file_utils.h"
#include <filesystem>
#include <iostream>

std::filesystem::path findProjectRoot(const std::string& startDir, const std::string& projectName) {
    std::filesystem::path currentPath = std::filesystem::absolute(startDir);
    while (currentPath.has_parent_path()) {
        if (currentPath.filename() == projectName) {
            return currentPath;
        }
        currentPath = currentPath.parent_path();
    }
    return "";
}

std::string findAssetFile(const std::string& projectName, const std::string& assetDir, const std::string& fileName) {
    std::filesystem::path projectRoot = findProjectRoot(std::filesystem::current_path().string(), projectName);
    if (projectRoot.empty()) {
        std::cerr << "Error: Project root directory not found." << std::endl;
        return "";
    }

    std::filesystem::path assetPath = projectRoot / assetDir;
    if (!std::filesystem::exists(assetPath) || !std::filesystem::is_directory(assetPath)) {
        std::cerr << "Error: " << assetPath << " is not a directory or does not exist." << std::endl;
        return "";
    }

    for (const auto& entry : std::filesystem::recursive_directory_iterator(assetPath)) {
        if (entry.path().filename() == fileName) {
            return entry.path().string();
        }
    }
    return "";
}