// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/pw_GameMode.h"
#include "Helper.h"

Apw_GameMode::Apw_GameMode()
{
	TSubclassOf<APawn> PlayerPawnClass =
		Helper::GetClass<APawn>(L"/Game/Characters/Hero/BP_Hero");

	if (PlayerPawnClass != NULL)
		DefaultPawnClass = PlayerPawnClass;
}
