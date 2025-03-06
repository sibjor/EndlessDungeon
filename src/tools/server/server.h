#include "perspective.h"

#define SERVER_ONLY 1
#define CLIENT_ONLY 0

#define PORT 8080

struct Terminal {
    char* command;
    char* output;
    char currentPath;
};

struct Metadata {
    char* dateTime;
    char* assetsDir;
    char* spritesheetPath;
    char* slicedSpritesheetPath;
    char* wasmDir;
    char* clientDir;
    char* serverDir;
    char* metadataPath;
    int port;
};

void initTerminal();
void runTerminalCommand();
void initServer();
void runServer();
void initAssets();
void hostGame();

