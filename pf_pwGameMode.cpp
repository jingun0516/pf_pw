// Copyright Epic Games, Inc. All Rights Reserved.

#include "pf_pwGameMode.h"
#include "pf_pwCharacter.h"
#include "UObject/ConstructorHelpers.h"

Apf_pwGameMode::Apf_pwGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Template/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
