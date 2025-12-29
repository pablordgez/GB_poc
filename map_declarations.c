#include "map_declarations.h"
#define _MAP(name, data, width, height) \
BANKREF_EXTERN(name)
MAPS
#undef _MAP
#define _MAP(name, data, width, height) \
    [_##name] = { BANK(name), data },
const AssetEntry map_assets [] = {
    MAPS
};
#undef _MAP

#define _MAP(name, data, width, height) \
    Map name;
MAPS
#undef _MAP

#define _MAP(name, data, width, height) \
[_##name] = &name,
Map* maps[] = {
    MAPS
};
#undef _MAP


#define _MAP(name, data, width, height) \
    init_map(maps[_##name], width, height, data, _##name);
void map_initialization(void){
    MAPS
}
#undef _MAP