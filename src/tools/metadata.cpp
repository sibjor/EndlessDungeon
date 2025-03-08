#include "metadata.h"
#include "path_utils.h"

void InitMetadata(char* path){
    CreateDirectory(path);
};

void ReadMetadata(char* path);

void WriteMetadata(char* path);

void UpdateMetadata(char* path);

void DeleteMetadata(char* path);

void DeleteAllMetadata(char* path);