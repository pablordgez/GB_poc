// This file should eventually be created by a script
#include "actor_declarations.h"


BANKREF_EXTERN(player)
BANKREF_EXTERN(smile_npc)

#define _ACTOR(name, data) \
    [ASSET_##name] = { BANK(name), data },
const AssetEntry actors [] = {
    ACTORS
};
#undef _ACTOR