#define PROJECT_ROOT_PATH "EndlessDungeon"
#define PROJECT_RAW_ASSETS_PATH PROJECT_ROOT_PATH "/assets"
#define PROJECT_DATA_PATH PROJECT_ROOT_PATH "/data"

// Directory functions
void ListDirectories(const char* directory);
void CreateDirectory(const char* directory);
void RemoveDirectory(const char* directory);
void RenameDirectory(const char* old_directory, const char* new_directory);
void CopyDirectory(const char* src_directory, const char* dst_directory);
void MoveDirectory(const char* src_directory, const char* dst_directory);
void GetDirectoryInfo(const char* directory);
void GetDirectorySize(const char* directory);

// File functions
void ListFiles(const char* directory);
void CreateFile(const char* file);
void RemoveFile(const char* file);
void RenameFile(const char* old_file, const char* new_file);
void CopyFile(const char* src_file, const char* dst_file);
void MoveFile(const char* src_file, const char* dst_file);
void GetFileInfo(const char* file);
void GetFileSize(const char* file);

// Directory + File functions
void ListPaths(const char* path);
void CreatePath(const char* path);
void RemovePath(const char* path);
void RenamePath(const char* old_path, const char* new_path);
void CopyPath(const char* src_path, const char* dst_path);
void MovePath(const char* src_path, const char* dst_path);
void GetPathInfo(const char* path);
void GetPathSize(const char* path);