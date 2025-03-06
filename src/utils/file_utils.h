#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#define METADATA_FILE "metadata.json"

#include "perspective.h"
/*
    getMetadata():

    Check if metadata.json exists

*/
void getMetadata();
/*
    setMetadata()

    If shouldCreateNew is TRUE:
    Create the metadata.json file
    Add the new path to metadata
    Remove the old path from metadata
    If successful, return TRUE
    If error, return error
*/
void setMetadata();

#endif 