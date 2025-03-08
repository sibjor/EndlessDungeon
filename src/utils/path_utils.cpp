#include "path_utils.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

// Directory functions
void ListDirectories(const char* directory) {
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_directory()) {
            std::cout << entry.path().string() << std::endl;
        }
    }
}

void CreateDirectory(const char* directory) {
    fs::create_directories(directory);
}

void RemoveDirectory(const char* directory) {
    fs::remove_all(directory);
}

void RenameDirectory(const char* old_directory, const char* new_directory) {
    fs::rename(old_directory, new_directory);
}

void CopyDirectory(const char* src_directory, const char* dst_directory) {
    fs::copy(src_directory, dst_directory, fs::copy_options::recursive);
}

void MoveDirectory(const char* src_directory, const char* dst_directory) {
    fs::rename(src_directory, dst_directory);
}

void GetDirectoryInfo(const char* directory) {
    // Implementation for getting directory info
}

void GetDirectorySize(const char* directory) {
    // Implementation for getting directory size
}

// File functions
void ListFiles(const char* directory) {
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::cout << entry.path().string() << std::endl;
        }
    }
}

void CreateFile(const char* file) {
    std::ofstream outfile(file);
    outfile.close();
}

void RemoveFile(const char* file) {
    fs::remove(file);
}

void RenameFile(const char* old_file, const char* new_file) {
    fs::rename(old_file, new_file);
}

void CopyFile(const char* src_file, const char* dst_file) {
    fs::copy(src_file, dst_file);
}

void MoveFile(const char* src_file, const char* dst_file) {
    fs::rename(src_file, dst_file);
}

void GetFileInfo(const char* file) {
    // Implementation for getting file info
}

void GetFileSize(const char* file) {
    // Implementation for getting file size
}

// Directory + File functions
void ListPaths(const char* path) {
    for (const auto& entry : fs::directory_iterator(path)) {
        std::cout << entry.path().string() << std::endl;
    }
}

void CreatePath(const char* path) {
    if (fs::path(path).has_extension()) {
        CreateFile(path);
    } else {
        CreateDirectory(path);
    }
}

void RemovePath(const char* path) {
    fs::remove_all(path);
}

void RenamePath(const char* old_path, const char* new_path) {
    fs::rename(old_path, new_path);
}

void CopyPath(const char* src_path, const char* dst_path) {
    if (fs::is_directory(src_path)) {
        CopyDirectory(src_path, dst_path);
    } else {
        CopyFile(src_path, dst_path);
    }
}

void MovePath(const char* src_path, const char* dst_path) {
    fs::rename(src_path, dst_path);
}

void GetPathInfo(const char* path) {
    // Implementation for getting path info
}

void GetPathSize(const char* path) {
    // Implementation for getting path size
}