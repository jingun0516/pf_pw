// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/Axe/BaseAxe.h"
#include "Actions/BaseAction.h"
#include "Actions/BaseSwingAction.h"
#include "Actions/ActionDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h" 
#include "Helper.h"

ABaseAxe::ABaseAxe()
{
	HandleSocketName = "AxeSocket";

	ToolType = EToolType::E_Axe;
	Actions = Cast<UActionDataAsset>(StaticLoadObject(UActionDataAsset::StaticClass(), nullptr, TEXT("/Game/Actions/DA_Axe")));
}

void ABaseAxe::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseAxe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseAxe::SetDatas()
{
	Super::SetDatas();
}
