// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Monsters/BaseMonster.h"
#include "UndeadBear.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API AUndeadBear : public ABaseMonster
{
	GENERATED_BODY()

public:
	AUndeadBear();

protected:
	virtual void BeginPlay() override;
	virtual void SetCharacterMovement() override;
};
