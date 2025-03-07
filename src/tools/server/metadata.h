#include "path_utils.h"

struct Metadata
{
    char* metadataPath;
};

void setMetadata(struct Metadata *metadata)
{
    
    metadata->metadataPath = "metadata.json";
}