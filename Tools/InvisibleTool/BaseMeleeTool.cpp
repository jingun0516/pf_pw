// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/InvisibleTool/BaseMeleeTool.h"
#include "Actions/ActionDataAsset.h"

ABaseMeleeTool::ABaseMeleeTool()
{
	HandleSocketName = "MeleeSocket";

	ToolType = EToolType::E_ETC;
	Actions = Cast<UActionDataAsset>(StaticLoadObject(UActionDataAsset::StaticClass(), nullptr, TEXT("/Game/Actions/DA_Melee")));
}

void ABaseMeleeTool::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseMeleeTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseMeleeTool::SetDatas()
{
	Super::SetDatas();
}
