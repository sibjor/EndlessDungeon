#include "perspective.h"

#define SERVER_ONLY 1
#define CLIENT_ONLY 0

#define ASSETS_DIR "assets"
#define WEB_BUID_DIR "build-wasm"
#define METADATA_FILE "metadata.json"
#define PORT 8080

#define TRUE 1
#define FALSE 0

struct Metadata {
    char* dateTime;
    char* assetsDir;
    char* spritesheetPath;
    char* slicedSpritesheetPath;
    char* wasmDir;
    char* clientDir;
    char* serverDir;
    char* metadataPath;
    char* metadataFileName;
    int port;
};

void initServer();
void runServer();
void initAssets();
void buildWASM();
void getMetadata();
void setMetadata();
void hostGame();

