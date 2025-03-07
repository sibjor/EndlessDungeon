#include "path_utils.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

bool is_project_root(const fs::path& path) {
    return fs::exists(path / ".git");
}

void FindPath(std::string& path) {
    fs::path current_path = path;

    while (!is_project_root(current_path)) {
        if (current_path.has_parent_path()) {
            current_path = current_path.parent_path();
        } else {
            // If no parent path is found, we are at the root of the filesystem
            break;
        }
    }

    // At this point, current_path should be the project root
    // Search all directories in project root for the specified path
    path = current_path.string();
}