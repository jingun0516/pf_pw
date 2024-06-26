// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/BaseAction.h"
#include "KickAction.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API UKickAction : public UBaseAction
{
	GENERATED_BODY()

public:
	virtual void DoAction() override;
	virtual void TickAction() override;
	virtual void EndAction() override;
	virtual void BeginActionNotify() override;
	virtual void EndActionNotify() override;
};
