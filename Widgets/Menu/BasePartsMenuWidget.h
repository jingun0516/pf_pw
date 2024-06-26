// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BasePartsMenuWidget.generated.h"

class AHero;
/**
 * 
 */
UCLASS()
class PF_PW_API UBasePartsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadOnly)
	AHero* OwnerHero;
};
