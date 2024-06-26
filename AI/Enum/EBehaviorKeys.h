// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EBehaviorKeys : uint8
{
	E_Wait UMETA(Displayname = "Wait"),
	E_Hitted UMETA(Displayname = "Hitted"),
	E_Action UMETA(Displayname = "Action"),
	E_Work UMETA(Displayname = "Work"),
	E_Track UMETA(Displayname = "Track"),
	E_Patrol UMETA(Displayname = "Patrol")
};


UENUM(BlueprintType)
enum class EActionTypeKeys : uint8
{
	E_None UMETA(Displayname = "None"),
	E_Main UMETA(Displayname = "Main"),
	E_Sub UMETA(Displayname = "Sub")
};