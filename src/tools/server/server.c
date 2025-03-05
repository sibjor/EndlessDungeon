#include "server.h"
#include <stddef.h>

struct Metadata{
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
/*
    initServer():

    Don't open any ports
    - Just start the server
    Check metadata for output directories and files of assets
    Check if metadata is correct
    If not, return error
    If correct, return TRUE
*/

struct Metadata* metadata;

void initServer(){
    getMetadata();
    if(metadata == NULL){
        setMetadata();
    }
    initAssets();
    buildWASM();
    hostGame();
}
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
void runServer(){
    struct Metadata* metadata;
}
/*
    getMetadata():

    Check metadata for output directories and files of assets
    Check if metadata is correct
    If not, return error
    If correct, return TRUE
*/
void getMetadata(){
    
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
void initAssets(){

}
/*
    buildWASM():

    Check metadata for output directories and files of assets and WASM
    Check if metadata and the above files are correct
    If not, return error
    If correct, build the WASM file with emscripten in a shell command
    If successful, return TRUE
    If error, return error
*/
void buildWASM(){

}
/*
    setMetadata()

    If shouldCreateNew is TRUE:
    Create the metadata.json file
    Add the new path to metadata
    Remove the old path from metadata
    If successful, return TRUE
    If error, return error
*/
void setMetadata(){
    metadata = malloc(sizeof(struct Metadata)); // Allocate memory for struct Metadata
}
/*
    hostGame():

    If previous functions are successful:
    
    Open ports
    Host the web_build directory
    If successful, return TRUE
    If error, return error
*/
void hostGame(){

}