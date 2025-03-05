#include "perspective.h"
#include 

#define SERVER_ONLY 1
#define CLIENT_ONLY 0

#define ASSETS_DIR "assets"
#define WEB_BUID_DIR "web_build"

#define TRUE 1
#define FALSE 0

void initServer();
void runServer();
void initAssets();
void buildWASM();
void getMetadata();
void setMetadata();
void hostGame();

