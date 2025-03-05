#ifndef DIR_UTILS_H
#define DIR_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#endif

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

char* recentPath;
char* currentPath;
char* projectRoot;

void setProjectRoot(const char* path);
char* getProjectRoot(){return projectRoot;};
void navigateTo(const char* path);
void navigateToRoot();
void navigateToParent(int levels);
void navigateBack();
void createDirectory(const char* path);

#endif