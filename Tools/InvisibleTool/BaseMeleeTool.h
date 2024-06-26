// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tools/BaseTool.h"
#include "BaseMeleeTool.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API ABaseMeleeTool : public ABaseTool
{
	GENERATED_BODY()

public:
	ABaseMeleeTool();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetDatas() override;
};
