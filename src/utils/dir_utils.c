#include "dir_utils.h"
#include <limits.h>

char* recentPath;
char* currentPath;
char* outputPath;

char* findProjectRoot(){
    // Finds the directory containing the top .git folder
};
void navigateTo(const char* path);
void navigateToProjectRoot();
void navigateToParent(int levels);
void navigateBack();
void getOutputDir(const char* path);
void setOutputDir(const char* path);
void createPath(const char* path);