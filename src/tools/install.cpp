#include "path_utils.h"
#include "metadata.h"

void InitProjectsDirectory(const char* path){
    CreateDirectory(path);
    InitMetadata("data");
};
