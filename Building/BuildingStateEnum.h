#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EBuildingState
{
	E_Idle UMETA(Displayname = "Idle"),
	E_Build UMETA(Displayname = "Build"),
	E_Work UMETA(Displayname = "Working"),
	E_WorkDone UMETA(Displayname = "WorkDone")
};

UENUM(BlueprintType)
enum class EWorkerSlot
{
	E_First UMETA(Displayname = "First"),
	E_Second UMETA(Displayname = "Second"),
	E_Third UMETA(Displayname = "Third"),
	E_Forth UMETA(Displayname = "Forth"),
	E_Fifth UMETA(Displayname = "Fifth"),
	E_None UMETA(Displayname = "None")
};