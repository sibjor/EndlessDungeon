#include "server.h"


/*
    initServer():

    Don't open any ports
    Just start the server
    Check metadata for output directories and files of assets
    Check if metadata is correct
    If not, return error
    If correct, return TRUE
*/ 
void initServer(){

}
/*
    getMetadata():

    Check metadata for output directories and files of assets
    Check if metadata is correct
    If not, return error
    If correct, return TRUE
*/
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

}
void GetMetadata(){
    
}
/*
    initAssets():

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
    Add the new path to metadata
    Remove the old path from metadata
    If successful, return TRUE
    If error, return error
*/
void setMetadata(){

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