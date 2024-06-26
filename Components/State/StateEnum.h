#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class E_StateType : UINT8
{
	E_Idle UMETA(Displayname = "Idle"),
	E_Attacking UMETA(Displayname = "Attack"),
	E_Hit UMETA(Displayname = "Hitted"),
	E_Build UMETA(Displayname = "Build"),
	E_Dead UMETA(Displayname = "Dead"),
	E_Main UMETA(Displayname = "Main"),
	E_Sub UMETA(Displayname = "Sub")
};
