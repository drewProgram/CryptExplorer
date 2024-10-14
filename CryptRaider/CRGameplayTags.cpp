#include "CRGameplayTags.h"

namespace CRGameplayTags {
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Grabber_Grabbed, "Grabber.Grabbed", "Object grabbed");

    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Door_Dungeon, "Door.Dungeon", "Refers to Door from dungeon");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Door_Crypt_Mausoleum, "Door.Crypt.Mausoleum", "Refers to Door from mausoleum at crypt");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Door_Crypt_MainArea, "Door.Crypt.MainArea", "Refers to Door from main area at crypt");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Door_Crypt_FinalArea, "Door.Crypt.FinalArea", "Refers to Cube from final area at crypt");

    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Trap_Activating, "Trap.Activating", "Trap activating");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Trap_Deactivating, "Trap.Deactivating", "Trap deactivating");
}