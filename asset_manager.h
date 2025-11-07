#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <stdint.h>
typedef struct {
    uint8_t bank;
    uint8_t* data;
} AssetEntry;
#endif /* ASSET_MANAGER_H */