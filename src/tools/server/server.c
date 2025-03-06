#include "server.h"
#include <stddef.h>

struct Terminal {
    char* status;
    char* command;
    char* output;
    char currentPath;
};

struct Metadata
{
    char *dateTime;
    char *assetsDir;
    char *spritesheetPath;
    char *slicedSpritesheetPath;
    char *wasmDir;
    char *clientDir;
    char *serverDir;
    char *metadataPath;
    int port;
};

void initTerminal(){
    struct Terminal *terminal = malloc(sizeof(struct Terminal));
    terminal->status = "Ready";
    terminal->command = "ls";
    terminal->output = " ";
    terminal->currentPath = " ";
}
/*
    initServer():

    Don't open any ports
    - Just start the server
    Check metadata for output directories and files of assets
    Check if metadata is correct
    If not, return error
    If correct, return TRUE
*/

struct Metadata *metadata;

/*
    runServer():

    Check if metadata is correct
    If not, update with setMetadata()
    Check if ports are open
    If not, open ports
    Check if build-wasm is hosted
    If not, host it
    If successful, return TRUE
    If error, return error
*/
void runServer()
{
    struct Metadata *metadata;
}
/*
    initAssets():

    Check if metadata.json exists
    If not, create it with setMetadata()
    Check metadata for output directories and files of assets
    Check if metadata is correct
    If not, return error
    If correct, return TRUE
*/
void initAssets()
{
}
/*
    hostGame():

    If previous functions are successful:

    Open ports
    Host the web_build directory
    If successful, return TRUE
    If error, return error
*/
void hostGame()
{
}