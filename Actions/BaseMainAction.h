// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/BaseAction.h"
#include "BaseMainAction.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API UBaseMainAction : public UBaseAction
{
	GENERATED_BODY()

	virtual void DoAction() override;
	virtual void TickAction() override;
	virtual void EndAction() override;
};
