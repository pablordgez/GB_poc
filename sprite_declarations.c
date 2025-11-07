// This file should eventually be created by a script
#include "sprite_declarations.h"
#include "metasprite1.h"
#include "smile.h"

BANKREF_EXTERN(metasprite1)
BANKREF_EXTERN(smile)

const AssetEntry sprites[] = {
    [ASSET_METASPRITE1] = { BANK(metasprite1), metasprite_1 },
    [ASSET_SMILE] = { BANK(smile), smile_sprite }
};