// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include "BaseStatusWidget.generated.h"

class UPocketmonComponent;
class AHero;
/**
 * 
 */
UCLASS()
class PF_PW_API UBaseStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UImage* PrevMonSlot;
	UPROPERTY(meta = (BindWidget))
	UImage* CurMonSlot;
	UPROPERTY(meta = (BindWidget))
	UImage* NextMonSlot;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CharacterLV;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HPText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHPText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurMonName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurMonLV;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPProgressBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* EXPProgressBar;

	AHero* PlayerCharacter;
	UPocketmonComponent* PocketmonComponent;

	void SetPocketmon();
	void SetHPBar(float HP, float MaxHP);
	void SetEXPBar(int EXP, int NextEXP);
	void SetCharacterLV(int LV);
};
