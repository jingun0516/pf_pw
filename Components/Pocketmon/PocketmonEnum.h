#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPocketmonSlot
{
	E_None UMETA(Displayname = "None"),
	E_First UMETA(Displayname = "First"),
	E_Second UMETA(Displayname = "Second"),
	E_Third UMETA(Displayname = "Third"),
	E_Forth UMETA(Displayname = "Forth"),
	E_Fifth UMETA(Displayname = "Fifth"),
	E_Sixth UMETA(Displayname = "Sixth"),
	E_MAX
};

UENUM(BlueprintType)
enum class EPocketmonRating
{
	E_Normal UMETA(Displayname = "Normal"),
	E_Rare UMETA(Displayname = "Rare"),
	E_Unique UMETA(Displayname = "Unique"),
	E_Legendary UMETA(Displayname = "Legendary")
};
