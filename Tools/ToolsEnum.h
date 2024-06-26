#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EToolSlot
{
	E_None UMETA(Displayname = "None"),
	E_First UMETA(Displayname = "First"),
	E_Second UMETA(Displayname = "Second"),
	E_Third UMETA(Displayname = "Third"),
	E_Forth UMETA(Displayname = "Forth"),
	E_MAX
};

UENUM(BlueprintType)
enum class EToolType
{
	E_None UMETA(Displayname = "None"),
	E_Sword UMETA(Displayname = "Sword"),
	E_Axe UMETA(Displayname = "Axe"),
	E_Pickax UMETA(Displayname = "Pickax"),
	E_ETC UMETA(Displayname = "ETC"),
	E_MAX
};

UENUM(BlueprintType)
enum class EWeaponType
{
	E_None UMETA(Displayname = "None"),
	E_Sword UMETA(Displayname = "Sword"),
	E_Bow UMETA(Displayname = "Bow"),
	E_Gun UMETA(Displayname = "Gun"),
	E_MAX
};
