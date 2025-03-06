#include "file_utils.h"
#include "dir_utils.h"

void getMetadata(){
    navigateToProjectRoot();
    if (METADATA_FILE == FALSE){
        setMetadata();
    }
    else{
        return "metadata.json";
    }
}

void setMetadata(){
    navigateToProjectRoot();
    if(currentPath == TRUE)
    createPath("metadata.json");
    return "metadata.json";
}