#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <iostream>
#include <filesystem>

std::string findAssetFile(const std::string& projectName, const std::string& assetDir, const std::string& fileName);

#endif 