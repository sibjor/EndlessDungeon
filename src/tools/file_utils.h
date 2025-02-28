#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <filesystem>

std::filesystem::path findProjectRoot(const std::string& startDir, const std::string& projectName);
std::string findAssetFile(const std::string& projectName, const std::string& assetDir, const std::string& fileName);

#endif 